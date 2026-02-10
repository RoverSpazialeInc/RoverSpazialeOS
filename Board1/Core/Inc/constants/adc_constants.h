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
 * @file adc_constants.h
 * @brief ADC-related constants for voltage measurement and resistor divider configuration.
 *
 * This file defines the ADC reference voltage and the resistor divider
 * values used for battery voltage measurement.
 */
#ifndef INC_CONSTANTS_ADC_CONSTANTS_H_
#define INC_CONSTANTS_ADC_CONSTANTS_H_

/** @brief ADC reference voltage (V). */
#define ADC_VREF (3.3f)

/** @brief Upper resistor in the voltage divider (connected to Vbat), in ohms. */
#define R1 (10000.0f)
/** @brief Lower resistor in the voltage divider (connected to GND), in ohms. */
#define R2 (2000.0f)


#endif /* INC_CONSTANTS_ADC_CONSTANTS_H_ */
