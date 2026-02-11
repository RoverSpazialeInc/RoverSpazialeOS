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
 * @file deserialize.h
 * @brief Deserialization functions for bus data structures.
 *
 * Declares functions that reconstruct state and decision structures
 * from their serialized byte-buffer representations.
 */

#ifndef INC_BUS_DESERIALIZE_H_
#define INC_BUS_DESERIALIZE_H_

#include <states.h>
#include <decision.h>
#include "frame_size.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Deserialize a BUS_LocalStateB1 structure from a byte buffer.
 * @param buf Pointer to the input byte buffer.
 * @param len Length of the input buffer in bytes.
 * @param state Pointer to the output BUS_LocalStateB1 structure.
 * @return 0 on success, negative value on error.
 */
int deserializeLocalStateB1(const uint8_t *buf, size_t len, BUS_LocalStateB1 *state);

/**
 * @brief Deserialize a BUS_LocalStateB2 structure from a byte buffer.
 * @param buf Pointer to the input byte buffer.
 * @param len Length of the input buffer in bytes.
 * @param state Pointer to the output BUS_LocalStateB2 structure.
 * @return 0 on success, negative value on error.
 */
int deserializeLocalStateB2(const uint8_t *buf, size_t len, BUS_LocalStateB2 *state);

/**
 * @brief Deserialize a BUS_GlobalState structure from a byte buffer.
 * @param buf Pointer to the input byte buffer.
 * @param len Length of the input buffer in bytes.
 * @param state Pointer to the output BUS_GlobalState structure.
 * @return 0 on success, negative value on error.
 */
int deserializeGlobalState(const uint8_t *buf, size_t len, BUS_GlobalState *state);

/**
 * @brief Deserialize a BUS_Decision structure from a byte buffer.
 * @param buf Pointer to the input byte buffer.
 * @param len Length of the input buffer in bytes.
 * @param state Pointer to the output BUS_Decision structure.
 * @return 0 on success, negative value on error.
 */
int deserializeDecision(const uint8_t *buf, size_t len, BUS_Decision *state);

#endif /* INC_BUS_DESERIALIZE_H_ */
