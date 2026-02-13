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
 * @file uart_functions.c
 * @brief UART communication stub functions for Board2.
 *
 * Implements interrupt-driven UART transmit/receive, RTR handshake,
 * and ACK/NACK protocol helpers used by the inter-board communication link.
 */

#include "uart_functions.h"
#include "main.h" // for GPIO pins

volatile uint8_t flagRTR = 0; 					    /**< RTR flag */

volatile uint8_t receivedFlag = 0;  				/**< Frame reception completed flag */
volatile uint8_t errorReceiveFlag = 0;  		 /**< Reception error flag */
volatile uint8_t trasmissionStatus;

static const uint8_t ack =  0x00;					/**< ACK byte value */
static const uint8_t nack = 0xFF; 					/**< NACK byte value */

static uint8_t received_ack; 		  			/**< ACK reception variable */

static UART_HandleTypeDef *current_handler; 	/**< Communication handler */

/* Handler */

/**
 * @brief Sets the UART handler used for communication.
 * @param uart_handler Pointer to the UART handle.
 */
void setComunicationHandler(UART_HandleTypeDef *uart_handler) {
	current_handler = uart_handler;
}

/**
 * @brief Gets the current UART communication handler.
 * @return Pointer to the active UART handle.
 */
UART_HandleTypeDef* getComunicationHandler() {
	return current_handler;
}

/* Transmission */

/**
 * @brief Checks and consumes the RTR flag.
 * @return 1 if RTR was set (now cleared), 0 otherwise.
 */
uint8_t checkRTR(void) {
	// if RTR is 1, return 1 but first reset the flag to 0
	if (flagRTR == 1) {
		flagRTR = 0;
		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief Transmits data via UART in interrupt mode.
 * @param pData Pointer to the data buffer to transmit.
 * @param size  Number of bytes to transmit.
 */
void TransmitIT(uint8_t *pData, size_t size) {

	/* Test CRC, si cambia o un byte del CRC oppure del buffer*/
//	static uint8_t jitter;
//
//	enum { ROMPO_QUI = 3 };
//	uint8_t ind = 3;
//
//	static uint8_t cont = 0;
//	cont++;
//
//	switch (cont) {
//	case ROMPO_QUI:
//		jitter = pData[ind];
//		pData[ind] = 0x22;
//		break;
//
//	case (ROMPO_QUI + 1):
//		pData[ind] = jitter;
//		break;
//
//	default:
//		break;
//	}
	//HAL_UART_Transmit(&current_handler, pData, size, HAL_MAX_DELAY);
	HAL_UART_Transmit_IT(current_handler, pData, size);
}

/* Reception */

/**
 * @brief Asserts the RTR (Ready To Receive) output pin.
 */
void setRTR(void) {
	HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_SET);
}

/**
 * @brief De-asserts the RTR (Ready To Receive) output pin.
 */
void resetRTR() {
	HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Starts UART reception in interrupt mode.
 * @param pData Pointer to the receive buffer.
 * @param size  Number of bytes to receive.
 * @return 1 on success, 0 on error.
 */
uint8_t ReceiveIT(uint8_t *pData, size_t size) {
	// clear flags
	receivedFlag = 0;
	errorReceiveFlag = 0;


	HAL_StatusTypeDef status_receive = HAL_UART_Receive_IT(current_handler,
			pData, size);
	if (status_receive != HAL_OK) {
		HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_SET);
		return 0; // errore
	}
	return 1; // ok
}

/**
 * @brief Checks whether a frame has been received.
 * @return 1 if a frame was received, 0 otherwise.
 */
uint8_t hasReceived(void) {
	return receivedFlag;
}

/**
 * @brief Checks whether a reception error occurred (set in error callback).
 * @return 1 if an error occurred, 0 otherwise.
 */
uint8_t errorReceived(void) {
	// Test function

	// Upon receiving data, alternate between ack and nack
//	static uint32_t count = 0;
//
//	if (receivedFlag == 1) {
//		count++; // Increase count on each successful reception
//
//		if (count % 2 == 0) {
//			return 1;
//		} else {
//			return 0;
//		}
//	} else {
//		return 0;
//	}

	// Real function
	return errorReceiveFlag;
}

/**
 * @brief Starts interrupt-driven reception of an ACK/NACK byte.
 */
void ReceiveAckIT(void) {
	received_ack = 0; 							// Clear
	ReceiveIT(&received_ack, 1);
}

/**
 * @brief Checks the received ACK/NACK value.
 * @return 1 if ACK received, 0 if NACK or unknown.
 */

uint8_t CheckAck(void) {
	if (received_ack == ack) {
		return 1;
	} else if (received_ack == nack) {
		return 0;
	} else {
		return 0;
	}
}

//void SendAckIT(void) {
//	static uint32_t count_ack = 0;
//	// se count ack è pari manda l'ack altirmenti manda il nack
//
//	if (count_ack % 2 == 0){
//		TransmitIT((uint8_t*) &nack, 1);
//	} else {
//		TransmitIT((uint8_t*) &ack, 1);
//	}
//	count_ack++;
//}

/**
 * @brief Sends an ACK byte via UART in interrupt mode.
 */
void SendAckIT(void) {
	TransmitIT((uint8_t*) &ack, 1);
}

/**
 * @brief Sends a NACK byte via UART in interrupt mode.
 */
void SendNackIT(void) {
	TransmitIT((uint8_t*) &nack, 1);
}

