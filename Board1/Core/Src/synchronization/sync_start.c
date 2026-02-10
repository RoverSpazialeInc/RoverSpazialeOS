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
 * Implements the SYNC / ACK handshake between Board 1 and Board 2 using
 * GPIO edges and CMSIS-RTOS2 event flags, so that every application task
 * begins execution at the same logical tick on both boards.
 */

#include "sync_start.h"

#include "gpio.h"  /* For write pin functions */

/** @brief GPIO port of the input pin (configured at runtime). */
static GPIO_TypeDef *g_in_port  = NULL;
/** @brief GPIO pin number of the input pin (configured at runtime). */
static uint16_t      g_in_pin   = 0;

/** @brief GPIO port of the output pin (configured at runtime). */
static GPIO_TypeDef *g_out_port = NULL;
/** @brief GPIO pin number of the output pin (configured at runtime). */
static uint16_t      g_out_pin  = 0;

/** @brief Event-flag bitmask for the start condition (configured at runtime). */
static uint32_t      g_flag_start = 0;
/** @brief Event-flag bitmask for the SYNC signal (configured at runtime). */
static uint32_t      g_flag_sync  = 0;
/** @brief Event-flag bitmask for the ACK signal (configured at runtime). */
static uint32_t      g_flag_ack   = 0;

/** @brief CMSIS-RTOS2 event-flags handle used for synchronization. */
static osEventFlagsId_t g_flagsSync = NULL;

/**
 * @brief Initialize the synchronization module.
 *
 * Stores the GPIO configuration and event-flag identifiers used for the
 * inter-board handshake.  The output pin is driven low as a safety
 * precaution.
 *
 * @param[in] flagsSync  CMSIS-RTOS2 event-flags handle for synchronization.
 * @param[in] in_port    GPIO port of the input pin.
 * @param[in] in_pin     GPIO pin number of the input pin.
 * @param[in] out_port   GPIO port of the output pin.
 * @param[in] out_pin    GPIO pin number of the output pin.
 * @param[in] flag_start Event-flag bit that signals the start condition.
 * @param[in] flag_sync  Event-flag bit used for the SYNC signal.
 * @param[in] flag_ack   Event-flag bit used for the ACK signal.
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

  /* Drive output low as a safety precaution */
  if (g_out_port != NULL) {
    HAL_GPIO_WritePin(g_out_port, g_out_pin, GPIO_PIN_RESET);
  }
}

/**
 * @brief Block the calling task until the start flag is set.
 *
 * Waits indefinitely on the event-flags object for @c flag_start.
 * If the wait returns an error or the expected flag is not set the
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
 * @brief Set the SYNC event flag from an ISR context.
 *
 * Called from the GPIO EXTI callback when a rising edge is detected on
 * the SYNC input pin.  This function is ISR-safe.
 */
void Sync_OnSyncEdgeFromISR(void)
{
  if (g_flagsSync != NULL) {
    (void)osEventFlagsSet(g_flagsSync, g_flag_sync);
  }
}

/**
 * @brief Set the ACK event flag from an ISR context.
 *
 * Called from the GPIO EXTI callback when a rising edge is detected on
 * the ACK input pin.  This function is ISR-safe.
 */
void Sync_OnAckEdgeFromISR(void)
{
  if (g_flagsSync != NULL) {
    (void)osEventFlagsSet(g_flagsSync, g_flag_ack);
  }
}

/**
 * @brief Execute the inter-board synchronization handshake.
 *
 * Depending on the compile-time board selection the function behaves as
 * either master (Board 1, @c SYNC_BOARD2 defined) or slave (Board 2):
 *
 * **Master (Board 1)**:
 *  1. Assert SYNC_OUT high.
 *  2. Wait for the ACK flag (set by EXTI ISR).
 *  3. Schedule a delayed start using @c SYNC_K_TICKS.
 *  4. Set the START flag so that all tasks may begin.
 *
 * **Slave (Board 2)**:
 *  1. Wait for the SYNC flag (set by EXTI ISR).
 *  2. Assert ACK_OUT high.
 *  3. Schedule a delayed start using @c SYNC_K_TICKS.
 *  4. Set the START flag so that all tasks may begin.
 *
 * If any required handle or port is NULL the calling thread is terminated.
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
     5) Set START
  */
  (void)osEventFlagsWait(g_flagsSync, g_flag_sync,
                         osFlagsWaitAll, osWaitForever);

  HAL_GPIO_WritePin(g_out_port, g_out_pin, GPIO_PIN_SET);

  uint32_t t0 = osKernelGetTickCount() + SYNC_K_TICKS;
  (void)osDelayUntil(t0);


  (void)osEventFlagsSet(g_flagsSync, g_flag_start);
#endif

}
