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
 * @file crc_functions.c
 * @brief CRC computation and comparison stub functions for Board2.
 *
 * Uses the STM32 hardware CRC peripheral (configured with byte-level input)
 * to compute and verify CRC checksums appended to communication buffers.
 */

#include "crc_functions.h"

#include "string.h"  // for memcpy

#include "crc.h"
extern CRC_HandleTypeDef hcrc;

/**
 * @brief Computes the CRC of a buffer and appends it.
 *
 * @note The CRC peripheral is configured with Input Data Format = BYTES
 *       (CRC_INPUTDATA_FORMAT_BYTES). Although HAL_CRC_Calculate() expects
 *       a uint32_t* pointer, internally the HAL processes data byte-by-byte
 *       (see CRC_Handle_8() in stm32g4xx_hal_crc.c), so no 32-bit alignment
 *       is required. The cast to uint32_t* only matches the HAL API signature.
 *
 * @param buffer       Pointer to the data buffer.
 * @param bufferLength Length of the payload in bytes (CRC is appended after).
 */
void computeCRC(uint8_t* buffer, uint32_t bufferLength){
    uint32_t crc;
    crc = HAL_CRC_Calculate(&hcrc, (uint32_t*) buffer, bufferLength);
    memcpy(&(buffer[bufferLength]), &crc, CRC_SIZE);
}

/**
 * @brief Compares the CRC appended to a buffer with a freshly computed CRC.
 *
 * @param buffer       Pointer to the data buffer (payload + appended CRC).
 * @param bufferLength Length of the payload in bytes (excluding the CRC).
 * @return 1 if the CRC matches, 0 otherwise.
 */
uint8_t compareCRC(uint8_t* buffer, uint32_t bufferLength){
    uint32_t crc_received;
    memcpy(&crc_received, &(buffer[bufferLength]), CRC_SIZE);

    uint32_t crc_computed;
    crc_computed = HAL_CRC_Calculate(&hcrc, (uint32_t*) buffer, bufferLength);

    if (crc_computed == crc_received){
        return 1;
    } else {
    	return 0;
    }
}
