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
 * @file temperature_init.h
 * @brief Header file for temperature sensor initialization.
 */

#ifndef INC_DRIVER_INIT_TEMPERATURE_INIT_H_
#define INC_DRIVER_INIT_TEMPERATURE_INIT_H_

#include "temperature_adc.h"

/**
 * @brief Internal temperature sensor instance.
 */
extern temp_internal_t temp_sensor;

/**
 * @brief Initialize the temperature sensor.
 */
void temperature_sensor_init();

#endif /* INC_DRIVER_INIT_TEMPERATURE_INIT_H_ */
