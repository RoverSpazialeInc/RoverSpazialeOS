#include "uart_functions.h"
#include "main.h" // per i pin

volatile uint8_t flagRTR = 0; 					    // Flag RTR

volatile uint8_t receivedFlag = 0;  				// Avvenuta ricezione frame
volatile uint8_t errorReceiveFlag = 0;  		 // Avvenuto errore di ricezione
volatile uint8_t trasmissionStatus;

static const uint8_t ack =  0x00;					// Ack
static const uint8_t nack = 0xFF; 					// Nack

static uint8_t received_ack; 	  			// variabile di ricezione per l'ack

static UART_HandleTypeDef *current_handler; 	// Handler comunicazione

/* Handler */
void setComunicationHandler(UART_HandleTypeDef *uart_handler) {
	current_handler = uart_handler;
}

UART_HandleTypeDef* getComunicationHandler() {
	return current_handler;
}

/* Trasmissione */

uint8_t checkRTR(void) {
	// se rtr è 1 torna 1 ma prima metti flag a 0
	if (flagRTR == 1) {
		flagRTR = 0;
		return 1;
	} else {
		return 0;
	}
}

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

/* Ricezione */

void setRTR(void) {
	HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_SET);
}

void resetRTR() {
	HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_RESET);
}

uint8_t ReceiveIT(uint8_t *pData, size_t size) {
	//pulisco i falg
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

uint8_t hasReceived(void) {
	return receivedFlag;
}

// Ritorna se c'è stato un errore di ricezione, abilitato nella callback di errore
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

void ReceiveAckIT(void) {
	received_ack = 0; 							// Pulizia
	ReceiveIT(&received_ack, 1);
}

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

void SendAckIT(void) {
	TransmitIT((uint8_t*) &ack, 1);
}

void SendNackIT(void) {
	TransmitIT((uint8_t*) &nack, 1);
}

