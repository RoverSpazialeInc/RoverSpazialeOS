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
 * @file DWT.c
 * @brief DWT (Data Watchpoint and Trace) cycle counter utilities for Board2.
 *
 * Provides initialization, cycle-to-microsecond conversion, measurement
 * printing, and busy-wait delay functions using the ARM Cortex-M DWT
 * cycle counter for WCET estimation and profiling.
 */

#include "DWT.h"
#include "print.h"

/**
 * @brief Initializes the DWT cycle counter.
 *
 * Enables the Cortex-M core cycle counter by:
 * 1. Enabling tracing (TRCENA) in CoreDebug
 * 2. Resetting the cycle counter to zero
 * 3. Enabling the cycle counter in DWT
 *
 * This function must be called once at system startup.
 */
void DWT_Init(void)
{
    /* Enable access to DWT and ITM */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* Reset cycle counter */
    DWT->CYCCNT = 0;

    /* Enable cycle counter */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief Converts CPU cycles to microseconds.
 *
 * Formula: us = cycles * 1e6 / f_cpu
 *
 * Uses uint64_t arithmetic to avoid overflow and adds f_cpu/2 for
 * correct rounding.
 *
 * @param cycles Number of CPU cycles to convert.
 * @return Equivalent time in microseconds.
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles)
{
    uint32_t f_cpu = HAL_RCC_GetHCLKFreq(); // CPU frequency (Hz)

    uint64_t num = (uint64_t)cycles * 1000000ULL + (f_cpu / 2U);
    return (uint32_t)(num / (uint64_t)f_cpu);
}

/**
 * @brief Prints the measured cycle count and equivalent time in microseconds.
 *
 * Output format: <tag> Cy=<cycles> (<microseconds> us)
 * If tag is NULL or empty, it is omitted.
 *
 * @param tag   Optional label printed before the measurement.
 * @param cycles Number of CPU cycles measured.
 */
void DWT_PrintCyclesAndUs(const char *tag, uint32_t cycles)
{
    uint32_t us = DWT_CyclesToUs_u32(cycles);

    if (tag && tag[0] != '\0')
    {
        printLabel(tag);
        printMsg(" ");
    }

    printMsg("Cy=");
    printInt((int32_t)cycles);
    printMsg(" (");
    printInt((int32_t)us);
    printMsg(" us)");
    printNewLine();
}

/**
 * @brief Busy-wait delay in microseconds using the DWT cycle counter.
 *
 * Requires DWT_Init() to have been called at startup.
 * Handles large delays through chunking to avoid 32-bit overflow.
 *
 * @param us Delay duration in microseconds.
 */
void DWT_DelayUs(uint32_t us)
{
    if (us == 0u) {
        return;
    }

    const uint32_t f_cpu = HAL_RCC_GetHCLKFreq();
    const uint32_t cycles_per_us = f_cpu / 1000000u;

    /* If f_cpu < 1MHz, precise us-level delay is not feasible */
    if (cycles_per_us == 0u) {
        return;
    }

    /* Chunking to avoid overflow in cycle count */
    const uint32_t max_cycles = 0x7FFFFFFFu;
    const uint32_t max_us_chunk = max_cycles / cycles_per_us;

    while (us > 0u) {
        uint32_t chunk_us = us;
        if (chunk_us > max_us_chunk) {
            chunk_us = max_us_chunk;
        }

        const uint32_t start = DWT->CYCCNT;
        const uint32_t target_cycles = chunk_us * cycles_per_us;

        while ((uint32_t)(DWT->CYCCNT - start) < target_cycles) {
            __NOP();
        }

        us -= chunk_us;
    }
}
