/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32g4xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hcsr04.h"
#include "pad_receiver.h"
#include "mpu6050.h"

#include "uart_functions.h"

#include "print.h"
#include "debug.h"

#include "sync_start.h"
#include "phase.h"

#include "cmsis_os2.h"
#include "event_flags_constant.h"

#include "SEGGER_SYSVIEW.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* --- CONFIGURAZIONE DEBUG --- */

#if VERBOSE_DEBUG_IT == 1
#define PRINT_DBG(msg) printMsg(msg)
#else
#define PRINT_DBG(msg) ((void)0)
#endif
/* ---------------------------- */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

extern osEventFlagsId_t flagsOSHandle;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

static inline void Sonar_SetEventFlag(const hcsr04_t *sensor);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef hlpuart1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim6;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
	while (1) {
	}
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
    #if SEGGER_BUILD
    SEGGER_SYSVIEW_RecordEnterISR();
    #endif
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
    #if SEGGER_BUILD
    if (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk) {
        SEGGER_SYSVIEW_RecordExitISRToScheduler();
    } else {
        SEGGER_SYSVIEW_RecordExitISR();
    }
    #endif
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles I2C1 event interrupt / I2C1 wake-up interrupt through EXTI line 23.
  */
void I2C1_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_EV_IRQn 0 */
    #if SEGGER_BUILD
    SEGGER_SYSVIEW_RecordEnterISR();
    #endif
  /* USER CODE END I2C1_EV_IRQn 0 */
  HAL_I2C_EV_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_EV_IRQn 1 */
    #if SEGGER_BUILD
    if (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk) {
        SEGGER_SYSVIEW_RecordExitISRToScheduler();
    } else {
        SEGGER_SYSVIEW_RecordExitISR();
    }
    #endif
  /* USER CODE END I2C1_EV_IRQn 1 */
}

/**
  * @brief This function handles I2C1 error interrupt.
  */
void I2C1_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_ER_IRQn 0 */
    #if SEGGER_BUILD
    SEGGER_SYSVIEW_RecordEnterISR();
    #endif
  /* USER CODE END I2C1_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_ER_IRQn 1 */
    #if SEGGER_BUILD
    if (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk) {
        SEGGER_SYSVIEW_RecordExitISRToScheduler();
    } else {
        SEGGER_SYSVIEW_RecordExitISR();
    }
    #endif
  /* USER CODE END I2C1_ER_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(RTR_IN_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC3 channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt, DAC2 and DAC4 channel underrun error interrupts.
  */
void TIM7_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_DAC_IRQn 0 */

  /* USER CODE END TIM7_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_DAC_IRQn 1 */

  /* USER CODE END TIM7_DAC_IRQn 1 */
}

/**
  * @brief This function handles LPUART1 global interrupt.
  */
void LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN LPUART1_IRQn 0 */

  /* USER CODE END LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&hlpuart1);
  /* USER CODE BEGIN LPUART1_IRQn 1 */

  /* USER CODE END LPUART1_IRQn 1 */
}

/**
  * @brief This function handles I2C3 event interrupt / I2C3 wake-up interrupt through EXTI line 27.
  */
void I2C3_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C3_EV_IRQn 0 */
    #if SEGGER_BUILD
    SEGGER_SYSVIEW_RecordEnterISR();
    #endif
  /* USER CODE END I2C3_EV_IRQn 0 */
  HAL_I2C_EV_IRQHandler(&hi2c3);
  /* USER CODE BEGIN I2C3_EV_IRQn 1 */
    #if SEGGER_BUILD
    if (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk) {
        SEGGER_SYSVIEW_RecordExitISRToScheduler();
    } else {
        SEGGER_SYSVIEW_RecordExitISR();
    }
    #endif
  /* USER CODE END I2C3_EV_IRQn 1 */
}

/**
  * @brief This function handles I2C3 error interrupt.
  */
void I2C3_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C3_ER_IRQn 0 */
    #if SEGGER_BUILD
    SEGGER_SYSVIEW_RecordEnterISR();
    #endif
  /* USER CODE END I2C3_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c3);
  /* USER CODE BEGIN I2C3_ER_IRQn 1 */
    #if SEGGER_BUILD
    if (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk) {
        SEGGER_SYSVIEW_RecordExitISRToScheduler();
    } else {
        SEGGER_SYSVIEW_RecordExitISR();
    }
    #endif
  /* USER CODE END I2C3_ER_IRQn 1 */
}

/* USER CODE BEGIN 1 */

extern volatile uint8_t flagRTR;

extern volatile system_phase_t system_phase;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == RTR_IN_Pin)
    {
    	switch (system_phase)
    	{

    		case SYNCHRONIZATION_START:
        			Sync_OnEdgeFromISR();
				break;

			case SYNCHRONIZATION_SUPERVISOR:
		            osEventFlagsSet(flagsOSHandle, FLAGS_SUPERVISOR_WAIT);
		        break;

			case WORKING_PHASE:
		            flagRTR = 1;
		        break;

			default:
				PRINT_DBG("RTR IRQ in UNKNOWN PHASE\n\r");
				break;
    	}
    }
}



/* SONAR */

extern hcsr04_t sonarLeft;
extern hcsr04_t sonarFront;
extern hcsr04_t sonarRight;

/* Set the appropriate OS flag based on the sonar instance */
static inline void Sonar_SetEventFlag(const hcsr04_t *sensor) {
	if (sensor == &sonarLeft) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_LEFT_OK);
	} else if (sensor == &sonarFront) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_FRONT_OK);
	} else if (sensor == &sonarRight) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_RIGHT_OK);
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance != TIM2)
		return;

	hcsr04_t *sensor = NULL;

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
		sensor = &sonarLeft;

	} else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
		sensor = &sonarFront;

	} else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
		sensor = &sonarRight;
	}

	if (sensor != NULL) {
		if (sensor->current_polarity == TIM_INPUTCHANNELPOLARITY_RISING) {
			// First edge: rising
			hcsr04_capture_rising_edge(sensor);
		} else {
			// Second edge: falling
			hcsr04_capture_falling_edge(sensor);
			// this one sets rx_done = 1, optional since PollingServer uses OS flags
			Sonar_SetEventFlag(sensor);
		}
	}
}

/* UART */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	UART_HandleTypeDef *h = getComunicationHandler();
	if (h != NULL && huart->Instance == h->Instance) {
		if (receivedFlag == 0) {
			receivedFlag = 1;
		}
		return;
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {

	UART_HandleTypeDef *h = getComunicationHandler();

	if (h != NULL && huart->Instance == h->Instance) {

		// Update model flag
		errorReceiveFlag = 1;

		// --- recovery ---
		__HAL_UART_CLEAR_OREFLAG(huart);
		__HAL_UART_CLEAR_FEFLAG(huart);
		__HAL_UART_CLEAR_NEFLAG(huart);
		__HAL_UART_CLEAR_PEFLAG(huart);


#if LED_DEBUG
		HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_RESET);
#endif

#if VERBOSE_DEBUG_IT

		uint32_t err = huart->ErrorCode;

		PRINT_DBG("UART ERROR: ");

		if (err & HAL_UART_ERROR_ORE) {
			PRINT_DBG("Overrun Error (buffer pieno) ");
		}
		if (err & HAL_UART_ERROR_FE) {
			PRINT_DBG("Framing Error (stop bit errato)	 ");
		}
		if (err & HAL_UART_ERROR_NE) {
			PRINT_DBG("Noise Error (rumore sul segnale) ");
		}
		if (err & HAL_UART_ERROR_PE) {
			PRINT_DBG("Parity Error	 ");
		}

		PRINT_DBG("\r\n");

#endif

	}
}


/* I2C */

/* MASTER RX COMPLETE CALLBACK I2C, PadReceiver */

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c->Instance == I2C1) {
		PadReceiver_RxCpltCallback();  // Optional, PollingServer uses OS flags
		osEventFlagsSet(flagsOSHandle, FLAG_PAD_OK);
	}
}

/* RX MEMORY COMPLETE CALLBACK I2C, Gyroscope */

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c->Instance == I2C3) {
		MPU6050_RxCpltCallback();  // Optional, PollingServer uses OS flags
		osEventFlagsSet(flagsOSHandle, FLAG_GYRO_OK);
	}
}

/* ERROR CALLBACK I2C, Gyroscope and PadReceiver*/

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {

    switch ((uint32_t) hi2c->Instance) {

    case (uint32_t) I2C1:
        PRINT_DBG("PadReceiver I2C ERROR: ");
        PadReceiver_ErrorCallback();
        osEventFlagsSet(flagsOSHandle, FLAG_PAD_ERROR);
        /* Abort ongoing transfer via driver API */
        PadReceiver_Abort();
        break;

    case (uint32_t) I2C3:
        PRINT_DBG("MPU6050 I2C ERROR: ");
        MPU6050_Error_Callback();
        osEventFlagsSet(flagsOSHandle, FLAG_GYRO_ERROR);
        /* Abort ongoing transfer via driver API */
        MPU6050_Abort(&hi2c3);
        break;

    default:
        PRINT_DBG("Unknown I2C instance ERROR\r\n");
        break;
    }

#if VERBOSE_DEBUG_IT


	if (hi2c->ErrorCode & HAL_I2C_ERROR_BERR) {
		PRINT_DBG("BERR (Bus Error) ");
	}
	if (hi2c->ErrorCode & HAL_I2C_ERROR_ARLO) {
		PRINT_DBG("ARLO (Arbitration Lost) ");
	}
	if (hi2c->ErrorCode & HAL_I2C_ERROR_AF) {
		PRINT_DBG("AF (Acknowledge Failure) ");
	}
	if (hi2c->ErrorCode & HAL_I2C_ERROR_OVR) {
		PRINT_DBG("OVR (Overrun/Underrun) ");
	}
	if (hi2c->ErrorCode & HAL_I2C_ERROR_DMA) {
		PRINT_DBG("DMA Error ");
	}
	if (hi2c->ErrorCode & HAL_I2C_ERROR_TIMEOUT) {
		PRINT_DBG("TIMEOUT ");
	}
	PRINT_DBG("\r\n");

#endif
}
/* USER CODE END 1 */
