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
 * @file sync_start.h
 * @brief Inter-board startup synchronization interface.
 *
 * Provides the API for synchronizing the startup sequence between
 * Board 1 and Board 2 using GPIO edges and CMSIS-RTOS2 event flags.
 */

#ifndef INC_SYNCHRONIZATION_SYNC_START_H_
#define INC_SYNCHRONIZATION_SYNC_START_H_

#include <stdint.h>
#include "stm32g474xx.h"
#include "cmsis_os2.h"

#include "actual_board.h"

/**
 * @brief Safety margin (in ticks) to start "shortly after".
 */
#define SYNC_K_TICKS 10u

/**
 * @brief Initialize the GPIO pins and event flags used for synchronization.
 *
 * Configures the input/output pins depending on the board role:
 * - Board 1: in = ACK_IN,  out = SYNC_OUT
 * - Board 2: in = SYNC_IN, out = ACK_OUT
 *
 * Also sets up the event flags used for the synchronization handshake.
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
               uint32_t flag_start, uint32_t flag_sync, uint32_t flag_ack);

/**
 * @brief Wait for the global start signal.
 *
 * Must be called at the beginning of every application task so that
 * all tasks start simultaneously after synchronization completes.
 */
void Sync_WaitStart(void);

/**
 * @brief ISR callback for a SYNC edge reception.
 *
 * Call this from HAL_GPIO_EXTI_Callback when the SYNC input pin triggers.
 */
void Sync_OnSyncEdgeFromISR(void);

/**
 * @brief ISR callback for an ACK edge reception.
 *
 * Call this from HAL_GPIO_EXTI_Callback when the ACK input pin triggers.
 */
void Sync_OnAckEdgeFromISR(void);

/**
 * @brief Board-aware ISR edge handler wrapper.
 *
 * On Board 1 it forwards to Sync_OnSyncEdgeFromISR();
 * on Board 2 it forwards to Sync_OnAckEdgeFromISR().
 */
static inline void Sync_OnEdgeFromISR(void)
{
#if defined(SYNC_BOARD2)
  Sync_OnAckEdgeFromISR();
#else
  Sync_OnSyncEdgeFromISR();
#endif
}

/**
 * @brief Synchronization thread entry point.
 *
 * This function implements the synchronization state machine and
 * should be created as a CMSIS-RTOS2 thread via osThreadNew().
 */
void SyncThread(void);

#endif /* INC_SYNCHRONIZATION_SYNC_START_H_ */
