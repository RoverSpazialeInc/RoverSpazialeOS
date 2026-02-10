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
 * @file timer.c
 * @brief Hardware timer driver implementation.
 *
 * Provides an abstraction layer over the STM32 HAL timer peripheral,
 * supporting initialization, start/stop control, period configuration,
 * and elapsed-time detection via interrupt callbacks.
 */

#include <stdint.h>
#include "tim.h"
#include "timer.h"

/**
 * @brief Initialize a timer instance.
 *
 * Binds the timer structure to a HAL timer handle and stores the input
 * clock frequency. The timer is initialized in a stopped, non-elapsed state.
 *
 * @param[in,out] timer     Pointer to the timer structure to initialize.
 * @param[in]     handler   Pointer to the HAL timer handle.
 * @param[in]     frequency Input clock frequency in Hz.
 * @return TIMER_OK on success, TIMER_ERR if any pointer is NULL.
 */
int8_t timer_init(timer_t* timer, TIM_HandleTypeDef* handler, uint32_t frequency)
{
	int8_t res = TIMER_ERR;
	if(timer && handler)
	{
		timer->htim = handler;
		timer->running = 0;
		timer->elapsed = 0;
		timer->in_frequency = frequency;
		res = TIMER_OK;
	}
	return res;

}

/**
 * @brief Start the timer in interrupt mode.
 *
 * Resets the elapsed flag, marks the timer as running, and starts the
 * underlying HAL timer with interrupt generation enabled.
 *
 * @param[in,out] timer Pointer to the timer structure.
 * @return TIMER_OK on success, TIMER_ERR if the pointer is NULL.
 */
int8_t timer_start(timer_t* timer)
{
	int8_t res = TIMER_ERR;
	if(timer)
	{
		timer->running = 1;
		timer->elapsed = 0;
		HAL_TIM_Base_Start_IT(timer->htim);
		res = TIMER_OK;
	}
	return res;
}

/**
 * @brief Stop the timer.
 *
 * Clears the running and elapsed flags and stops the underlying HAL
 * timer interrupt.
 *
 * @param[in,out] timer Pointer to the timer structure.
 * @return TIMER_OK on success, TIMER_ERR if the pointer is NULL.
 */
int8_t timer_stop(timer_t* timer)
{
	int8_t res = TIMER_ERR;
	if(timer)
	{
		timer->running = 0;
		timer->elapsed = 0;
		HAL_TIM_Base_Stop_IT(timer->htim);
		res = TIMER_OK;
	}
	return res;
}

/**
 * @brief Reset the timer.
 *
 * Stops the timer, clears all status flags, and resets the hardware
 * counter register back to zero.
 *
 * @param[in,out] timer Pointer to the timer structure.
 * @return TIMER_OK on success, TIMER_ERR if the pointer is NULL.
 */
int8_t timer_reset(timer_t* timer)
{
	int8_t res = TIMER_ERR;
	if(timer)
	{
		timer->running = 0;
		timer->elapsed = 0;
		HAL_TIM_Base_Stop_IT(timer->htim);
		__HAL_TIM_SET_COUNTER(timer->htim, 0);
		res = TIMER_OK;
	}
	return res;
}

/**
 * @brief Check whether the timer is currently running.
 *
 * @param[in] timer Pointer to the timer structure.
 * @return Non-zero if the timer is running, 0 otherwise.
 */
int8_t timer_is_running(timer_t* timer)
{
	int8_t res = 0;
	if(timer)
	{
		res = timer->running;
	}
	return res;
}

/**
 * @brief Check whether the timer period has elapsed.
 *
 * @param[in] timer Pointer to the timer structure.
 * @return Non-zero if the timer has elapsed, 0 otherwise.
 */
int8_t timer_is_elapsed(timer_t* timer)
{
	int8_t res = 0;

	if(timer)
	{
		res = timer->elapsed;
	}
	return res;
}

/**
 * @brief Check whether a HAL timer handle belongs to this timer instance.
 *
 * Compares the TIM peripheral instance of the given handler against the
 * one stored in the timer structure.
 *
 * @param[in] timer   Pointer to the timer structure.
 * @param[in] handler Pointer to the HAL timer handle to check.
 * @return TIMER_OK if the handler matches, TIMER_ERR otherwise.
 */
int8_t timer_is_myhandler(timer_t* timer, TIM_HandleTypeDef* handler)
{
	int8_t res = TIMER_ERR;
	if(timer && handler)
	{
		TIM_HandleTypeDef* inhandler = (TIM_HandleTypeDef*)handler;
		if(inhandler->Instance == timer->htim->Instance)
		{
			res = TIMER_OK;
		}
	}
	return res;
}

/**
 * @brief Set the timer period in milliseconds.
 *
 * Computes the auto-reload register (ARR) value from the desired period,
 * the input clock frequency, and the current prescaler, then applies it
 * to the hardware timer.
 *
 * @param[in,out] timer  Pointer to the timer structure.
 * @param[in]     period Desired period in milliseconds.
 * @return TIMER_OK on success, TIMER_ERR if the pointer is NULL.
 */
int8_t timer_set_period(timer_t* timer, uint16_t period)
{
	int8_t res = TIMER_ERR;
	uint32_t arr = -1;
	uint32_t prescaler = -1;

	if(timer)
	{
		prescaler = timer->htim->Instance->PSC;
		arr = ((uint64_t)period * timer->in_frequency) / (1000 * (prescaler + 1)) - 1;
		__HAL_TIM_SET_AUTORELOAD(timer->htim, arr);
		res = TIMER_OK;
	}

	return res;
}

/**
 * @brief Handle the timer period elapsed interrupt callback.
 *
 * Should be called from the HAL timer period elapsed callback. If the
 * given handler matches this timer instance, the timer is marked as
 * stopped and the elapsed flag is set.
 *
 * @param[in,out] timer   Pointer to the timer structure.
 * @param[in]     handler Pointer to the HAL timer handle that triggered the interrupt.
 * @return TIMER_OK if the handler matched and the state was updated, TIMER_ERR otherwise.
 */
int8_t timer_period_elapsed(timer_t* timer, TIM_HandleTypeDef* handler)
{
	int8_t res = TIMER_ERR;

	if(timer_is_myhandler(timer, handler) == TIMER_OK)
	{
		timer->running = 0;
		timer->elapsed = 1;
		res = TIMER_OK;
	}

	return res;
}


