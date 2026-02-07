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
 * @file DWT.h
 * @brief Data Watchpoint and Trace (DWT) module for execution time measurement.
 *
 * This module uses the ARM Cortex-M core cycle counter (DWT->CYCCNT)
 * to measure execution time in terms of clock cycles.
 *
 * Advantages:
 *  - Single cycle precision
 *  - Minimal overhead
 *  - Ideal for WCET estimation and profiling
 *
 * Requirements:
 *  - Cortex-M Core with DWT (e.g., M4)
 *  - DWT_Init() must be called ONCE at startup
 */

#ifndef INC_WCET_ESTIMATION_DWT_H_
#define INC_WCET_ESTIMATION_DWT_H_

#include <stdint.h>
#include "stm32g4xx.h"        // Core Registers (DWT, CoreDebug, IRQn_Type, etc.)
#include "stm32g4xx_hal.h"    // HAL_RCC_GetHCLKFreq()

/**
 * @brief Initializes the DWT cycle counter.
 *
 * - Enables tracing in CoreDebug
 * - Resets the cycle counter
 * - Enables the cycle counter
 */
void DWT_Init(void);

/**
 * @brief Starts a time measurement.
 *
 * @return Current value of the cycle counter.
 *
 * @note The returned value should be passed to DWT_End().
 *       DSB/ISB instructions ensure that:
 *        - all previous instructions are completed
 *        - the pipeline is synchronized
 *       making the measurement more accurate.
 */
static inline uint32_t DWT_Begin(void)
{
    __DSB();   // Data Synchronization Barrier
    __ISB();   // Instruction Synchronization Barrier
    return DWT->CYCCNT;
}

/**
 * @brief Ends a time measurement.
 *
 * @param start Value returned by DWT_Begin().
 * @return Number of elapsed cycles.
 *
 * @note Subtraction handles uint32 overflow correctly.
 */
static inline uint32_t DWT_End(uint32_t start)
{
    __DSB();
    __ISB();
    return (uint32_t)(DWT->CYCCNT - start);
}

/**
 * @brief Converts CPU cycles to microseconds.
 *
 * Uses the current HCLK frequency (HAL_RCC_GetHCLKFreq()).
 * Calculation is done in integer arithmetic (no float) with rounding.
 *
 * @param cycles Number of CPU cycles.
 * @return Time in microseconds.
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles);

/**
 * @brief Prints the measurement result.
 *
 * Prints format: <tag> Cy=<cycles> (<microseconds> us)
 * Uses functions defined in print.h
 *
 * @param tag String tag to identify the measurement.
 * @param cycles Number of cycles measured.
 */
void DWT_PrintCyclesAndUs(const char *tag, uint32_t cycles);

/**
 * @brief Busy-wait delay in microseconds.
 *
 * Requires DWT_Init() to have been called at startup.
 */
void DWT_DelayUs(uint32_t us);

/*
 * ---------------------------------------------------------------------------
 * Usage Example
 * ---------------------------------------------------------------------------
 *
 * uint32_t t0 = DWT_Begin();
 * // code to measure
 * uint32_t cycles = DWT_End(t0);
 *
 * DWT_PrintCyclesAndUs("CTRL", cycles);
 */

#endif /* INC_WCET_ESTIMATION_DWT_H_ */
