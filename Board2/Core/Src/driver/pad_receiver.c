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
 * @file pad_receiver.c
 * @brief Implementation of the Pad Receiver driver
 * 
 * This file handles the communication with the remote controller pad via I2C,
 * managing data reception and status updates.
 */

#include "pad_receiver.h"
#include "i2c.h"

#define PAD_I2C_ADDRESS (0x60)

static BUS_RemoteController rx_buffer;   // Reception buffer
static BUS_RemoteController valid_data;  // Last valid data
static volatile PadRxStatus_t rx_status = PAD_RX_NOT_RECEIVED;

/**
 * @brief  Starts the pad data request via I2C interrupt.
 * @return PAD_OK if the request started successfully, PAD_ERR otherwise
 */
int8_t PadReceiver_Request(void) {
    if (HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY) {
        rx_status = PAD_RX_IN_PROGRESS; // Reset flag: operation start
        
        // Start interrupt reception (Shifted Address)
        if (HAL_I2C_Master_Receive_IT(&hi2c1, PAD_I2C_ADDRESS, (uint8_t*) &rx_buffer, sizeof(BUS_RemoteController)) != HAL_OK) {
            rx_status = PAD_RX_NOT_RECEIVED; // Start error
            return PAD_ERR;    // Failed to start
        }
        return PAD_OK; // Successfully started
    } else {
        return PAD_ERR; // Busy
    }
}

/**
 * @brief  Gets the current status of the pad receiver.
 * @return Current status of the receiver
 */
PadRxStatus_t PadReceiver_GetStatus(void) {
    return rx_status;
}

/**
 * @brief  Copies the last valid data received into the controller structure.
 * @param  bus_rc Pointer to the controller structure where data will be copied
 */
void PadReceiver_Read(BUS_RemoteController* bus_rc) {
    bus_rc->x_lever = valid_data.x_lever;
    bus_rc->y_lever = valid_data.y_lever;
    bus_rc->buttons = valid_data.buttons;
}

/**
 * @brief  I2C Receive Complete Callback.
 *         Updates the valid data with the received buffer content.
 */
void PadReceiver_RxCpltCallback(void) {
    valid_data = rx_buffer;      // Update valid data
    rx_status = PAD_RX_SUCCESS;  // Signal success
}

/**
 * @brief  I2C Error Callback.
 */
void PadReceiver_ErrorCallback(void) {
    rx_status = PAD_RX_ERROR;    // Signal error
}

/**
 * @brief  Aborts any ongoing I2C transfer for the Pad Receiver.
 *         Sends a STOP condition on the bus to release it.
 * @note   Should be called from the I2C error callback to recover
 *         from bus errors (NACK, arbitration lost, etc.).
 */
void PadReceiver_Abort(void) {
    HAL_I2C_Master_Abort_IT(&hi2c1, PAD_I2C_ADDRESS);
}
