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
 * @file crc_functions.h
 * @brief CRC computation and verification function declarations.
 *
 * Provides stub declarations for computing a CRC over a byte buffer
 * and comparing an appended CRC against a freshly computed value.
 */

#ifndef INC_STUB_CRCFUNCTIONS_H_
#define INC_STUB_CRCFUNCTIONS_H_

#include <stdint.h>

/** @brief Size in bytes of the CRC field. */
#define CRC_SIZE (4)

/**
 * @brief Compute the CRC of a buffer and append it at the end.
 *
 * Calculates a CRC-32 over the first @p bufferLength bytes of @p buffer
 * and writes the result into the bytes immediately following the payload.
 *
 * @param[in,out] buffer       Pointer to the data buffer (must have room
 *                             for CRC_SIZE extra bytes after the payload).
 * @param[in]     bufferLength Length of the payload in bytes.
 */
void computeCRC(uint8_t* buffer, uint32_t bufferLength);

/**
 * @brief Compare the CRC appended to a buffer with a freshly computed value.
 *
 * Recomputes the CRC over the first @p bufferLength bytes of @p buffer and
 * compares it with the CRC stored in the trailing CRC_SIZE bytes.
 *
 * @param[in] buffer       Pointer to the data buffer including the CRC tail.
 * @param[in] bufferLength Length of the payload (excluding the CRC) in bytes.
 * @return 1 if the CRCs match, 0 otherwise.
 */
uint8_t compareCRC(uint8_t* buffer, uint32_t bufferLength);

#endif /* INC_STUB_CRCFUNCTIONS_H_ */
