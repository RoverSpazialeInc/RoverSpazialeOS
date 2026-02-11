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
 * @file pad_receiver.h
 * @brief Header file for Pad Receiver driver.
 */

#ifndef INC_DRIVER_PAD_RECEIVER_H_
#define INC_DRIVER_PAD_RECEIVER_H_

#include "sensors.h"

// Define per return status di PadReceiver_Request
/** @brief Error return status */
#define PAD_ERR     (-1)
/** @brief OK return status */
#define PAD_OK      (0)

/**
 * @brief Enum for asynchronous reception status.
 */
typedef enum {
    PAD_RX_NOT_RECEIVED = 0, /**< Idle */
    PAD_RX_IN_PROGRESS,      /**< Busy */
    PAD_RX_SUCCESS,          /**< Done OK */
    PAD_RX_ERROR             /**< Done Error */
} PadRxStatus_t;

/**
 * @brief Starts data reception request via Interrupt (non-blocking).
 * @return PAD_OK if started successfully, PAD_ERR if bus busy or HAL error.
 */
int8_t PadReceiver_Request(void);

/**
 * @brief Returns the current reception status.
 * @return Current PadRxStatus_t status.
 */
PadRxStatus_t PadReceiver_GetStatus(void);

/**
 * @brief Copies the last valid received data into the controller structure.
 * @param data Pointer to the destination BUS_RemoteController structure.
 */
void PadReceiver_Read(BUS_RemoteController* data);

/**
 * @brief Callback called at the end of reception (defined in pad_receiver.c).
 */
void PadReceiver_RxCpltCallback(void);

/**
 * @brief  I2C Error Callback.
 */
void PadReceiver_ErrorCallback(void);

/**
 * @brief  Aborts any ongoing I2C transfer for the Pad Receiver.
 *         Sends a STOP condition on the bus to release it.
 */
void PadReceiver_Abort(void);

#endif /* INC_DRIVER_PAD_RECEIVER_H_ */
