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
 * @file temperature_adc.c
 * @brief Implementation of the Temperature ADC driver using the STM32 internal temperature sensor.
 *
 * This file contains the implementation of functions to initialize and read
 * temperature from the MCU internal temperature sensor connected via ADC.
 */

#include "driver/temperature_adc.h"

/**
 * @brief Initialize the internal temperature sensor structure.
 *
 * Sets up the ADC handle for reading the internal temperature sensor.
 *
 * @param temp Pointer to the sensor structure.
 * @param hadc Pointer to the ADC handle (must be configured for the internal temp sensor channel).
 */
void temp_internal_init(temp_internal_t* temp, ADC_HandleTypeDef* hadc, float vdd_mv) {
    temp->hadc = hadc;
    temp->vdd_mv = vdd_mv;
}

/**
 * @brief Read temperature from the internal temperature sensor.
 *
 * Starts the ADC conversion, waits for completion, reads the raw value,
 * and converts it to temperature in Celsius using a linear approximation.
 *
 * @param temp Pointer to the sensor structure.
 * @param temperature Pointer to float where the temperature will be stored.
 * @return int8_t 0 on success, -1 on error.
 */
int8_t temp_internal_read_temperature(temp_internal_t* temp, float* temperature) {
    if (temp->hadc == NULL) {
        return TEMP_DRIVER_FAIL;
    }

    // Perform ADC calibration before conversion
    HAL_ADCEx_Calibration_Start(temp->hadc, ADC_SINGLE_ENDED);

    // Start ADC conversion for internal temperature sensor
    HAL_ADC_Start(temp->hadc);

    // Wait for conversion to complete
    if (HAL_ADC_PollForConversion(temp->hadc, 1) != HAL_OK) {
        HAL_ADC_Stop(temp->hadc);
        return TEMP_DRIVER_FAIL;
    }

    // Read the converted value
    uint32_t adc_value = HAL_ADC_GetValue(temp->hadc);

    HAL_ADC_Stop(temp->hadc);

    // Read factory calibration values
    int32_t ts_cal1 = (int32_t)(*TS_CAL1_ADDR);
    int32_t ts_cal2 = (int32_t)(*TS_CAL2_ADDR);

    // Compensate for VDD voltage difference
    // Factory calibration was done at 3.0V; normalize the raw reading to 3.0V
    float ts_data_normalized = (float)adc_value * (temp->vdd_mv / VREFINT_CAL_VREF);

    // Calculate temperature using linear interpolation (RM0440 Section 21.4.31)
    float slope = (TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP) / (float)(ts_cal2 - ts_cal1);
    float temp_c = slope * (ts_data_normalized - (float)ts_cal1) + TEMPSENSOR_CAL1_TEMP;

    // Limit value to supported range
    if (temp_c < MIN_TEMPERATURE) {
        temp_c = MIN_TEMPERATURE;
    }
    if (temp_c > MAX_TEMPERATURE) {
        temp_c = MAX_TEMPERATURE;
    }

    *temperature = temp_c;
    return TEMP_DRIVER_OK;
}

/**
 * @brief Read the temperature from the internal sensor with averaging.
 *
 * Takes multiple samples, ignores outliers/invalid readings, and averages the result.
 *
 * @param temp Pointer to the sensor structure.
 * @param samples Number of samples to average.
 * @param temperature Pointer to float where the temperature will be stored.
 * @return int8_t 0 on success, -1 if no valid samples were obtained.
 */
int8_t temp_internal_read_temperature_avg(temp_internal_t* temp, uint8_t samples, float* temperature) {
    float sum = 0;
    uint8_t valid_samples = 0;

    if (samples == 0) {
        samples = 1;
    }

    for (uint8_t i = 0; i < samples; i++) {
        float temp_val = 0;
        if (temp_internal_read_temperature(temp, &temp_val) == TEMP_DRIVER_OK) {
            if (temp_val > -200.0f && temp_val < 200.0f) {
                sum += temp_val;
                valid_samples++;
            }
        }

        HAL_Delay(1);
    }

    if (valid_samples == 0) {
        return TEMP_DRIVER_FAIL;
    }

    *temperature = sum / valid_samples;
    return TEMP_DRIVER_OK;
}
