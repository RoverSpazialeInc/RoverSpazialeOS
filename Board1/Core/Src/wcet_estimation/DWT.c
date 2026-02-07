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
 * @brief Data Watchpoint and Trace (DWT) cycle counter implementation.
 */

#include "DWT.h"
#include "print.h"

/**
 * @brief Enables the Cortex-M core cycle counter.
 *
 * Steps:
 * 1. Enable tracing (TRCENA) in CoreDebug
 * 2. Reset the cycle counter
 * 3. Enable the cycle counter in DWT
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
 * Formula:
 *   us = cycles * 1e6 / f_cpu
 *
 * - f_cpu is the HCLK frequency in Hz
 * - Uses uint64_t to avoid overflow
 * - Adds f_cpu/2 for correct rounding
 *
 * @param cycles Number of CPU cycles.
 * @return Time in microseconds.
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles)
{
    uint32_t f_cpu = HAL_RCC_GetHCLKFreq(); // CPU Frequency (Hz)

    uint64_t num = (uint64_t)cycles * 1000000ULL + (f_cpu / 2U);
    return (uint32_t)(num / (uint64_t)f_cpu);
}

/**
 * @brief Prints the measured cycle count and equivalent time in microseconds.
 *
 * Output format:
 *   <tag> Cy=<cycles> (<microseconds> us)
 *
 * If tag is NULL or empty string, it is omitted.
 *
 * @param tag String tag to identify the measurement.
 * @param cycles Number of cycles measured.
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

void DWT_DelayUs(uint32_t us)
{
    if (us == 0u) {
        return;
    }

    const uint32_t f_cpu = HAL_RCC_GetHCLKFreq();
    const uint32_t cycles_per_us = f_cpu / 1000000u;
    if (cycles_per_us == 0u) {
        return;
    }

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
