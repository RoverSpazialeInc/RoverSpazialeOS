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
 * @file temperature_init.c
 * @brief Initialization of the temperature sensor.
 *
 * This file contains the implementation for initializing the KY-028 temperature sensor,
 * setting up the ADC configuration.
 */

#include "temperature_init.h"

#include "temperature_adc.h"
#include "adc.h"

extern ADC_HandleTypeDef hadc1;

/**
 * @brief Global temperature sensor instance.
 */
temp_internal_t temp_sensor;

/**
 * @brief Initializes the temperature sensor subsystem.
 *
 * This function initializes the internal temperature sensor structure with
 * the ADC handle configured for the internal temp sensor channel.
 *
 * @retval None
 */
void temperature_sensor_init(){
	temp_internal_init(&temp_sensor, &hadc1);

}
