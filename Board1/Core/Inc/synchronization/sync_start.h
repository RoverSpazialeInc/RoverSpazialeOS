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
 * Provides the API for synchronizing the start-up of Board 1 and Board 2
 * using GPIO edges and CMSIS-RTOS2 event flags. The module handles both
 * the SYNC and ACK handshake so that every application task begins its
 * work at the same logical tick across the two boards.
 *
 */

#ifndef INC_SYNCHRONIZATION_SYNC_START_H_
#define INC_SYNCHRONIZATION_SYNC_START_H_

#include <stdint.h>
#include "stm32g474xx.h"
#include "cmsis_os2.h"

#include "actual_board.h"

/** @brief Safety margin (in RTOS ticks) used to schedule an imminent start. */
#define SYNC_K_TICKS 10u

/**
 * @brief Initialize the synchronization module.
 *
 * Configures the GPIO pins used for the sync handshake:
 * - Board 1: input = ACK_IN,  output = SYNC_OUT
 * - Board 2: input = SYNC_IN, output = ACK_OUT
 *
 * Also stores the event-flag handle and the individual flag masks used
 * for start, sync, and acknowledge signalling.
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
               uint32_t flag_start, uint32_t flag_sync, uint32_t flag_ack);

/**
 * @brief Block the calling task until synchronization is complete.
 *
 * Must be called at the beginning of every application task so that all
 * tasks start executing their work at the same logical instant.
 */
void Sync_WaitStart(void);

/**
 * @brief Handle a SYNC edge from within an ISR context.
 *
 * Should be called from @c HAL_GPIO_EXTI_Callback when the SYNC input
 * pin triggers an interrupt.
 */
void Sync_OnSyncEdgeFromISR(void);

/**
 * @brief Handle an ACK edge from within an ISR context.
 *
 * Should be called from @c HAL_GPIO_EXTI_Callback when the ACK input
 * pin triggers an interrupt.
 */
void Sync_OnAckEdgeFromISR(void);

/**
 * @brief Board-agnostic ISR edge handler.
 *
 * Convenience wrapper that dispatches to @ref Sync_OnAckEdgeFromISR on
 * Board 2 and to @ref Sync_OnSyncEdgeFromISR on Board 1.
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
 * Implements the full SYNC/ACK handshake state machine. Create this
 * thread with @c osThreadNew during system initialization.
 */
void SyncThread(void);

#endif /* INC_SYNCHRONIZATION_SYNC_START_H_ */
