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
 * @file freeRTOS_functions.c
 * @brief FreeRTOS utility functions for Board1 task and peripheral management.
 *
 * Provides helpers used by the supervisor to terminate tasks, abort UART links,
 * stop timers/ADCs, reset outputs, and transition the system into degraded,
 * emergency, or faulty operating modes.
 */

#include "freeRTOS_functions.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "adc.h"
#include "uart_functions.h"
#include "print.h"
#include "motors_init.h"

// Extern thread handles
extern osThreadId_t PIDHandle;
extern osThreadId_t SupervisorHandle;
extern osThreadId_t ReadTemperatureHandle;
extern osThreadId_t ReadBatteryHandle;
extern osThreadId_t StartSeggerHandle;
extern osThreadId_t SynchronizationHandle;

// Extern peripheral handles
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

/**
 * @brief Terminates a thread if it is alive and not the caller.
 * @param thread  Handle of the thread to terminate.
 * @param current Handle of the calling thread (will not be terminated).
 */
static inline void terminateThreadIfAlive(osThreadId_t thread,
		osThreadId_t current) {
	if ((thread != NULL) && (thread != current)) {
		(void) osThreadTerminate(thread);
	}
}

/**
 * @brief Terminates all application tasks except the caller.
 */
static inline void killTasks(void) {
	osThreadId_t current = osThreadGetId();

	terminateThreadIfAlive(PIDHandle, current);
	terminateThreadIfAlive(ReadTemperatureHandle, current);
	terminateThreadIfAlive(ReadBatteryHandle, current);
}

/**
 * @brief Aborts any ongoing UART transfers on communication and printer links.
 */
static inline void abortUartLinks(void) {
	UART_HandleTypeDef *comm_uart = getComunicationHandler();
	UART_HandleTypeDef *print_uart = getPrinterHandler();

	if (comm_uart != NULL) {
		(void) HAL_UART_Abort(comm_uart);
		(void) HAL_UART_Abort_IT(comm_uart);
	}

	if (print_uart != NULL) {
		(void) HAL_UART_Abort(print_uart);
		(void) HAL_UART_Abort_IT(print_uart);
	}
}

/**
 * @brief Stops all hardware timers and sets motor PWM to default.
 */
static inline void stopTimers(void) {
	Motors_SetDefaultCcr(757);

	(void) HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_ALL);
	(void) HAL_TIM_Base_Stop_IT(&htim2);

	(void) HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_ALL);
	(void) HAL_TIM_Base_Stop_IT(&htim3);

	(void) HAL_TIM_Encoder_Stop(&htim4, TIM_CHANNEL_ALL);
	(void) HAL_TIM_Base_Stop_IT(&htim4);

	(void) HAL_TIM_Encoder_Stop(&htim8, TIM_CHANNEL_ALL);
	(void) HAL_TIM_Base_Stop_IT(&htim8);

	(void) HAL_TIM_Base_Stop_IT(&htim7);
}

/**
 * @brief Stops ADC conversions on both ADC peripherals.
 */
static inline void stopAdcs(void) {
	(void) HAL_ADC_Stop_IT(&hadc1);
	(void) HAL_ADC_Stop_IT(&hadc2);
}

/**
 * @brief Resets all GPIO outputs (LEDs, actuator, debug) to a safe state.
 */
static inline void resetOutputs(void) {
	(void) HAL_GPIO_WritePin(WhiteLedRight_GPIO_Port, WhiteLedRight_Pin,
			GPIO_PIN_RESET);
	(void) HAL_GPIO_WritePin(RedLedRight_GPIO_Port, RedLedRight_Pin,
			GPIO_PIN_RESET);

	(void) HAL_GPIO_WritePin(WhiteLedLeft_GPIO_Port, WhiteLedLeft_Pin,
			GPIO_PIN_RESET);
	(void) HAL_GPIO_WritePin(RedLedLeft_GPIO_Port, RedLedLeft_Pin,
			GPIO_PIN_RESET);

#if LED_DEBUG
    (void)HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_RESET);
#endif

	(void) HAL_GPIO_WritePin(Actuator_GPIO_Port, Actuator_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Shuts down all peripherals (UART, timers, ADCs, GPIOs).
 */
static inline void killPeripherals(void) {
	abortUartLinks();
	stopTimers();
	stopAdcs();
	resetOutputs();
}

/**
 * @brief Enters degraded operating mode.
 *
 * Kills tasks and peripherals, then terminates the calling thread.
 */
void enterDegraded() {
	printMsg("Entering degraded mode...\n");
	killTasks();
	killPeripherals();
	(void) osThreadTerminate(osThreadGetId());

}

/**
 * @brief Enters emergency operating mode.
 *
 * Kills tasks and peripherals, then terminates the calling thread.
 */
void enterEmergency() {
	printMsg("Entering emergency mode...\n");
	killTasks();
	killPeripherals();
	(void) osThreadTerminate(osThreadGetId());
}

/**
 * @brief Enters faulty operating mode.
 *
 * Kills tasks and peripherals, then terminates the calling thread.
 */
void enterFaulty() {
	printMsg("Entering faulty mode...\n");
	killTasks();
	killPeripherals();
	(void) osThreadTerminate(osThreadGetId());
}

