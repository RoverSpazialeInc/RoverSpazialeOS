/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Motor3_Pin GPIO_PIN_2
#define Motor3_GPIO_Port GPIOC
#define Motor4_Pin GPIO_PIN_3
#define Motor4_GPIO_Port GPIOC
#define Encoder1A_Pin GPIO_PIN_0
#define Encoder1A_GPIO_Port GPIOA
#define Encoder1B_Pin GPIO_PIN_1
#define Encoder1B_GPIO_Port GPIOA
#define battery_adc_Pin GPIO_PIN_4
#define battery_adc_GPIO_Port GPIOA
#define Encoder2A_Pin GPIO_PIN_6
#define Encoder2A_GPIO_Port GPIOA
#define Encoder2B_Pin GPIO_PIN_7
#define Encoder2B_GPIO_Port GPIOA
#define WhiteLedRight_Pin GPIO_PIN_1
#define WhiteLedRight_GPIO_Port GPIOB
#define RedLedRight_Pin GPIO_PIN_2
#define RedLedRight_GPIO_Port GPIOB
#define WhiteLedLeft_Pin GPIO_PIN_14
#define WhiteLedLeft_GPIO_Port GPIOB
#define RedLedLeft_Pin GPIO_PIN_15
#define RedLedLeft_GPIO_Port GPIOB
#define Encoder4A_Pin GPIO_PIN_6
#define Encoder4A_GPIO_Port GPIOC
#define Encoder4B_Pin GPIO_PIN_7
#define Encoder4B_GPIO_Port GPIOC
#define Motor1_Pin GPIO_PIN_8
#define Motor1_GPIO_Port GPIOA
#define Motor2_Pin GPIO_PIN_9
#define Motor2_GPIO_Port GPIOA
#define Encoder3A_Pin GPIO_PIN_11
#define Encoder3A_GPIO_Port GPIOA
#define Encoder3B_Pin GPIO_PIN_12
#define Encoder3B_GPIO_Port GPIOA
#define RTR_IN_Pin GPIO_PIN_10
#define RTR_IN_GPIO_Port GPIOC
#define RTR_IN_EXTI_IRQn EXTI15_10_IRQn
#define RTR_OUT_Pin GPIO_PIN_11
#define RTR_OUT_GPIO_Port GPIOC
#define Actuator_Pin GPIO_PIN_12
#define Actuator_GPIO_Port GPIOC
#define LedDebug_Pin GPIO_PIN_7
#define LedDebug_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
