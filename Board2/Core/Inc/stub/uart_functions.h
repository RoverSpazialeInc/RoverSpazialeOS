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
 * @file uart_functions.h
 * @brief UART communication function declarations.
 *
 * Declares stub functions for configuring and operating UART communication,
 * including handler management, interrupt-driven transmission and reception,
 * and ACK/NACK handshaking.
 */

#ifndef INC_STUB_UARTFUNCTIONS_H_
#define INC_STUB_UARTFUNCTIONS_H_

#include <stdint.h>
#include <stddef.h>
#include "stm32g4xx_hal.h"

/** @brief Flag set when data has been successfully received. */
extern volatile uint8_t receivedFlag;

/** @brief Flag set when a receive error occurs. */
extern volatile uint8_t errorReceiveFlag;

/** @defgroup UartHandler UART Handler Management
 *  @{
 */

/**
 * @brief Set the UART peripheral handle used for communication.
 * @param[in] uart_handler Pointer to the HAL UART handle.
 */
void setComunicationHandler(UART_HandleTypeDef* uart_handler);

/**
 * @brief Get the UART peripheral handle used for communication.
 * @return Pointer to the current HAL UART handle.
 */
UART_HandleTypeDef * getComunicationHandler();

/**
 * @brief Abort any ongoing UART receive operation.
 */
void abortReceive();

/**
 * @brief Abort any ongoing UART transmit operation.
 */
void abortTransmit();

/**
 * @brief Abort both ongoing UART transmit and receive operations.
 */
void abortTransmitAndReceive();

/** @} */ /* end of UartHandler */

/** @defgroup UartTransmission UART Transmission
 *  @{
 */

/**
 * @brief Check the Ready-To-Receive flag.
 * @return 1 if the remote end is ready to receive, 0 otherwise.
 */
uint8_t checkRTR(void);

/**
 * @brief Start an interrupt-driven UART transmission.
 * @param[in] pData Pointer to the data buffer to transmit.
 * @param[in] size  Number of bytes to transmit.
 */
void TransmitIT(uint8_t *pData, size_t size);

/**
 * @brief Start an interrupt-driven reception of an acknowledgment byte.
 */
void ReceiveAckIT(void);

/**
 * @brief Check whether a valid acknowledgment has been received.
 * @return 1 if ACK received, 0 otherwise.
 */
uint8_t CheckAck(void);

/** @} */ /* end of UartTransmission */

/** @defgroup UartReception UART Reception
 *  @{
 */

/**
 * @brief Set the Ready-To-Receive flag.
 */
void setRTR();

/**
 * @brief Reset the Ready-To-Receive flag.
 */
void resetRTR();

/**
 * @brief Start an interrupt-driven UART reception.
 * @param[out] pData Pointer to the buffer where received data is stored.
 * @param[in]  size  Number of bytes to receive.
 * @return 1 on success, 0 on failure.
 */
uint8_t ReceiveIT(uint8_t *pData, size_t size);

/**
 * @brief Check whether data has been fully received.
 * @return 1 if reception is complete, 0 otherwise.
 */
uint8_t hasReceived();

/**
 * @brief Check whether a receive error has occurred.
 * @return 1 if an error was detected, 0 otherwise.
 */
uint8_t errorReceived(void);

/**
 * @brief Send an ACK response via interrupt-driven UART transmission.
 */
void SendAckIT(void);

/**
 * @brief Send a NACK response via interrupt-driven UART transmission.
 */
void SendNackIT(void);

/** @} */ /* end of UartReception */

#endif /* INC_STUB_UARTFUNCTIONS_H_ */
