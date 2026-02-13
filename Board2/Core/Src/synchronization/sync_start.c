/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file sync_start.c
 * @brief Inter-board startup synchronization implementation.
 *
 * Implements the GPIO-based handshake and CMSIS-RTOS2 event-flag
 * mechanism used to synchronize the startup sequence between
 * Board 1 (master) and Board 2 (slave).
 */

#include "sync_start.h"

#include "gpio.h"  /**< For GPIO write pin functions */

/** @name GPIO pins configured at runtime
 *  @{
 */
static GPIO_TypeDef *g_in_port  = NULL;  /**< Input GPIO port  */
static uint16_t      g_in_pin   = 0;     /**< Input GPIO pin   */

static GPIO_TypeDef *g_out_port = NULL;  /**< Output GPIO port */
static uint16_t      g_out_pin  = 0;     /**< Output GPIO pin  */
/** @} */

/** @name Event flag bitmasks configured at runtime
 *  @{
 */
static uint32_t      g_flag_start = 0;   /**< Start flag bitmask */
static uint32_t      g_flag_sync  = 0;   /**< Sync flag bitmask  */
static uint32_t      g_flag_ack   = 0;   /**< Ack flag bitmask   */
/** @} */

/** @brief CMSIS-RTOS2 event flags object used for synchronization. */
static osEventFlagsId_t g_flagsSync = NULL;

/**
 * @brief Initialize the GPIO pins and event flags used for synchronization.
 *
 * Stores the supplied GPIO port/pin pairs and event-flag bitmasks in
 * module-level variables, then resets the output pin as a safety measure.
 *
 * @param[in] flagsSync  CMSIS-RTOS2 event flags handle for synchronization.
 * @param[in] in_port    GPIO port of the input pin.
 * @param[in] in_pin     GPIO pin number of the input pin.
 * @param[in] out_port   GPIO port of the output pin.
 * @param[in] out_pin    GPIO pin number of the output pin.
 * @param[in] flag_start Event flag bit indicating start.
 * @param[in] flag_sync  Event flag bit indicating sync edge received.
 * @param[in] flag_ack   Event flag bit indicating acknowledge edge received.
 */
void Sync_Init(osEventFlagsId_t flagsSync,
               GPIO_TypeDef *in_port, uint16_t in_pin,
               GPIO_TypeDef *out_port, uint16_t out_pin,
               uint32_t flag_start, uint32_t flag_sync, uint32_t flag_ack)
{
  g_in_port  = in_port;
  g_in_pin   = in_pin;
  g_out_port = out_port;
  g_out_pin  = out_pin;
  
  g_flag_start = flag_start;
  g_flag_sync  = flag_sync;
  g_flag_ack   = flag_ack;
  
  g_flagsSync  = flagsSync;

  /* Reset output to 0 as a safety measure */
  if (g_out_port != NULL) {
    HAL_GPIO_WritePin(g_out_port, g_out_pin, GPIO_PIN_RESET);
  }
}

/**
 * @brief Wait for the global start signal.
 *
 * Blocks the calling thread until the start event flag is set.
 * Must be called at the beginning of every application task so that
 * all tasks start simultaneously after synchronization completes.
 * If an error occurs or the expected flag is not received, the
 * calling thread is terminated.
 */
void Sync_WaitStart(void)
{
  if (g_flagsSync == NULL) {
    return;
  }
  uint32_t flags = osEventFlagsWait(g_flagsSync,
                                    g_flag_start,
                                    osFlagsWaitAny | osFlagsNoClear,
                                    osWaitForever);

  if ((int32_t)flags < 0) {
    osThreadTerminate(osThreadGetId());
    return;
  }

  if ((flags & g_flag_start) == 0U) {
    osThreadTerminate(osThreadGetId());
    return;
  }
}

/**
 * @brief ISR callback for a SYNC edge reception.
 *
 * Sets the sync event flag from interrupt context.
 * Call this from @c HAL_GPIO_EXTI_Callback when the SYNC input pin triggers.
 *
 * @note This function is ISR-safe.
 */
void Sync_OnSyncEdgeFromISR(void)
{
  if (g_flagsSync != NULL) {
    (void)osEventFlagsSet(g_flagsSync, g_flag_sync);
  }
}

/**
 * @brief ISR callback for an ACK edge reception.
 *
 * Sets the acknowledge event flag from interrupt context.
 * Call this from @c HAL_GPIO_EXTI_Callback when the ACK input pin triggers.
 *
 * @note This function is ISR-safe.
 */
void Sync_OnAckEdgeFromISR(void)
{
  if (g_flagsSync != NULL) {
    (void)osEventFlagsSet(g_flagsSync, g_flag_ack);
  }
}

/**
 * @brief Synchronization thread entry point.
 *
 * Implements the synchronization state machine and should be created
 * as a CMSIS-RTOS2 thread via @c osThreadNew().
 *
 * Behaviour depends on the board role selected at compile time:
 * - **SYNC_BOARD2 defined (Master / Board 1):**
 *   1. Assert SYNC_OUT high.
 *   2. Wait for ACK edge (EXTI &rarr; FLAG_ACK).
 *   3. Delay until @c t0 and set the START flag.
 * - **Otherwise (Slave / Board 2):**
 *   1. Wait for SYNC edge (EXTI &rarr; FLAG_SYNC).
 *   2. Assert ACK_OUT high (pulse or level).
 *   3. Delay until @c t0 and set the START flag.
 *
 * If any required resource is NULL the thread terminates immediately.
 */
void SyncThread(void)
{
  
  if ((g_flagsSync == NULL) || (g_in_port == NULL) || (g_out_port == NULL)) {
    osThreadTerminate(osThreadGetId());
    return;
  }

#if defined(SYNC_BOARD2)
  /* MASTER:
     1) SYNC_OUT = 1
     2) Wait for ACK (EXTI -> FLAG_ACK)
     3) SYNC_OUT = 0
     4) delayUntil(t0) and set START
  */
  HAL_GPIO_WritePin(g_out_port, g_out_pin, GPIO_PIN_SET);

  (void)osEventFlagsWait(g_flagsSync, g_flag_ack,
                         osFlagsWaitAll, osWaitForever);


  uint32_t t0 = osKernelGetTickCount() + SYNC_K_TICKS;
  (void)osDelayUntil(t0);

  (void)osEventFlagsSet(g_flagsSync, g_flag_start);

#else /* BOARD2 */
  /* SLAVE:
     1) Wait for SYNC (EXTI -> FLAG_SYNC)
     2) ACK_OUT = 1 (pulse or level)
     3) delayUntil(t0)
     4) ACK_OUT = 0 (if pulse is desired)
     5) set START
  */
  (void)osEventFlagsWait(g_flagsSync, g_flag_sync,
                         osFlagsWaitAll, osWaitForever);

  HAL_GPIO_WritePin(g_out_port, g_out_pin, GPIO_PIN_SET);

  uint32_t t0 = osKernelGetTickCount() + SYNC_K_TICKS;
  (void)osDelayUntil(t0);


  (void)osEventFlagsSet(g_flagsSync, g_flag_start);
#endif

}
