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
 * @file timer.h
 * @brief Hardware timer driver interface.
 *
 * Provides initialization, start, stop, reset, and period management
 * functions for hardware timers using the STM32 HAL TIM peripheral.
 *
 * @date Mar 26, 2023
 * @author vincarlet
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32g4xx_hal.h"

/** @brief Return code indicating success. */
#define TIMER_OK	(0)
/** @brief Return code indicating an error. */
#define TIMER_ERR	(-1)

/**
 * @brief Timer instance structure.
 *
 * Holds the state and configuration for a single hardware timer.
 */
struct timer_s
{
	TIM_HandleTypeDef* htim;  /**< @brief Pointer to the HAL timer handle. */
	uint8_t running;          /**< @brief Flag indicating whether the timer is running. */
	uint16_t elapsed;         /**< @brief Flag indicating whether the timer period has elapsed. */
	uint32_t in_frequency;    /**< @brief Input clock frequency of the timer in Hz. */
};

/** @brief Typedef for the timer instance structure. */
typedef struct timer_s timer_t;

/**
 * @brief Initialize a timer instance.
 *
 * Configures the timer structure with the given HAL handle and input
 * clock frequency.
 *
 * @param[in,out] timer     Pointer to the timer instance to initialize.
 * @param[in]     handler   Pointer to the HAL TIM handle.
 * @param[in]     frequency Input clock frequency of the timer in Hz.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_init(timer_t* timer, TIM_HandleTypeDef* handler, uint32_t frequency);

/**
 * @brief Start the timer.
 *
 * Begins counting on the specified timer instance.
 *
 * @param[in,out] timer Pointer to the timer instance to start.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_start(timer_t* timer);

/**
 * @brief Stop the timer.
 *
 * Suspends counting on the specified timer instance without resetting
 * the counter.
 *
 * @param[in,out] timer Pointer to the timer instance to stop.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_stop(timer_t* timer);

/**
 * @brief Reset the timer.
 *
 * Stops the timer and resets the counter value to zero.
 *
 * @param[in,out] timer Pointer to the timer instance to reset.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_reset(timer_t* timer);

/**
 * @brief Check if the timer is currently running.
 *
 * @param[in] timer Pointer to the timer instance to query.
 * @return 1 if the timer is running, 0 otherwise.
 */
int8_t timer_is_running(timer_t* timer);

/**
 * @brief Check if the timer period has elapsed.
 *
 * @param[in] timer Pointer to the timer instance to query.
 * @return 1 if the period has elapsed, 0 otherwise.
 */
int8_t timer_is_elapsed(timer_t* timer);

/**
 * @brief Check whether a HAL timer handle belongs to this timer instance.
 *
 * Compares the given HAL handle with the one stored in the timer
 * structure.
 *
 * @param[in] timer   Pointer to the timer instance.
 * @param[in] handler Pointer to the HAL TIM handle to compare.
 * @return 1 if the handle matches, 0 otherwise.
 */
int8_t timer_is_myhandler(timer_t* timer, TIM_HandleTypeDef* handler);

/**
 * @brief Set the timer period in milliseconds.
 *
 * Configures the auto-reload value so that an update event is generated
 * after the specified number of milliseconds.
 *
 * @param[in,out] timer  Pointer to the timer instance.
 * @param[in]     period Desired period in milliseconds.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_set_period(timer_t* timer, uint16_t period);

/**
 * @brief Handle the timer period-elapsed interrupt callback.
 *
 * Should be called from the HAL timer period-elapsed interrupt callback
 * to update the internal elapsed state of the timer.
 *
 * @param[in,out] timer   Pointer to the timer instance.
 * @param[in]     handler Pointer to the HAL TIM handle that triggered the interrupt.
 * @return TIMER_OK on success, TIMER_ERR on failure.
 */
int8_t timer_period_elapsed(timer_t* timer, TIM_HandleTypeDef* handler);

#endif /* INC_TIMER_H_ */
