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
 * @file temperature_adc.h
 * @brief Header file for Temperature ADC driver using the STM32 internal temperature sensor.
 *
 * This file contains the definitions and function prototypes for reading
 * temperature from the MCU internal temperature sensor via ADC.
 */

#ifndef INC_TEMPERATURE_ADC_H_
#define INC_TEMPERATURE_ADC_H_

#include "stm32g4xx_hal.h"

// Temperature Range
#define MIN_TEMPERATURE        (-55.0f)    /**< Minimum supported temperature */
#define MAX_TEMPERATURE        (125.0f)    /**< Maximum supported temperature */

#define TEMP_DRIVER_OK          0
#define TEMP_DRIVER_FAIL       -1

/**
 * @brief Structure to hold internal temperature sensor configuration and state.
 */
typedef struct {
    ADC_HandleTypeDef* hadc;    /**< Pointer to ADC handle (configured for internal temp sensor) */
    uint32_t adc_resolution;    /**< 4095 for 12-bit, 1023 for 10-bit */
} temp_internal_t;

// Initialization functions

/**
 * @brief Initialize the internal temperature sensor structure.
 *
 * @param temp Pointer to the sensor structure.
 * @param hadc Pointer to the ADC handle (configured for internal temp sensor channel).
 */
void temp_internal_init(temp_internal_t* temp, ADC_HandleTypeDef* hadc);

// Reading functions

/**
 * @brief Read the temperature from the internal sensor.
 *
 * @param temp Pointer to the sensor structure.
 * @param temperature Pointer to float where the temperature will be stored.
 * @return int8_t 0 on success, error code otherwise.
 */
int8_t temp_internal_read_temperature(temp_internal_t* temp, float* temperature);

/**
 * @brief Read the temperature from the internal sensor with averaging.
 *
 * @param temp Pointer to the sensor structure.
 * @param samples Number of samples to average.
 * @param temperature Pointer to float where the temperature will be stored.
 * @return int8_t 0 on success, error code otherwise.
 */
int8_t temp_internal_read_temperature_avg(temp_internal_t* temp, uint8_t samples, float* temperature);

#endif /* INC_TEMPERATURE_ADC_H_ */
