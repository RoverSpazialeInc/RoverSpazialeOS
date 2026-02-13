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
 * @brief DWT (Data Watchpoint and Trace) cycle counter interface.
 *
 * This module uses the ARM Cortex-M DWT cycle counter (DWT->CYCCNT) to
 * measure code execution time in clock cycles. Provides single-cycle
 * precision with minimal overhead, ideal for WCET estimation and profiling.
 *
 * @note Requires a Cortex-M core with DWT support (e.g. M4).
 * @note DWT_Init() must be called once at startup.
 */

#ifndef INC_WCET_ESTIMATION_DWT_H_
#define INC_WCET_ESTIMATION_DWT_H_

#include <stdint.h>
#include "stm32g4xx.h"        // Core registers (DWT, CoreDebug, IRQn_Type, etc.)
#include "stm32g4xx_hal.h"    // HAL_RCC_GetHCLKFreq()

/**
 * @brief Initializes the DWT cycle counter.
 *
 * Enables tracing in CoreDebug, resets the cycle counter, and enables it.
 */
void DWT_Init(void);

/**
 * @brief Begins a time measurement.
 *
 * Returns the current cycle counter value. The DSB/ISB barriers ensure
 * that all preceding instructions are completed and the pipeline is
 * synchronized for accurate measurement.
 *
 * @return Current DWT cycle count to be passed to DWT_End().
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
 * Subtraction is correct even on 32-bit overflow.
 *
 * @param start Value returned by DWT_Begin().
 * @return Number of elapsed CPU cycles.
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
 * Uses the current HCLK frequency (HAL_RCC_GetHCLKFreq()) with
 * integer arithmetic and rounding (no floating point).
 *
 * @param cycles Number of CPU cycles to convert.
 * @return Equivalent time in microseconds.
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles);

/**
 * @brief Prints a measurement result.
 *
 * Output format: <tag> Cy=<cycles> (<microseconds> us)
 * Uses the functions defined in print.h.
 *
 * @param tag    Optional label (NULL or empty to omit).
 * @param cycles Measured cycle count.
 */
void DWT_PrintCyclesAndUs(const char *tag, uint32_t cycles);

/**
 * @brief Busy-wait delay in microseconds.
 *
 * Requires DWT_Init() to have been called at startup.
 *
 * @param us Delay duration in microseconds.
 */
void DWT_DelayUs(uint32_t us);

/**
 * @example
 * @code
 * uint32_t t0 = DWT_Begin();
 * // code to measure
 * uint32_t cycles = DWT_End(t0);
 *
 * DWT_PrintCyclesAndUs("CTRL", cycles);
 * @endcode
 */

#endif /* INC_WCET_ESTIMATION_DWT_H_ */
