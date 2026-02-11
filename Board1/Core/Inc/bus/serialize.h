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
 * @file serialize.h
 * @brief Serialization functions for bus data structures.
 *
 * Declares functions that convert state and decision structures
 * into their byte-buffer representations for transmission.
 */

#ifndef INC_BUS_SERIALIZE_H_
#define INC_BUS_SERIALIZE_H_

#include <states.h>
#include <decision.h>
#include "frame_size.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Serialize a BUS_LocalStateB1 structure into a byte buffer.
 * @param buf Pointer to the output byte buffer.
 * @param state Pointer to the BUS_LocalStateB1 structure to serialize.
 * @return Number of bytes written to the buffer.
 */
size_t serializeLocalStateB1(uint8_t *buf, const BUS_LocalStateB1 *state);

/**
 * @brief Serialize a BUS_LocalStateB2 structure into a byte buffer.
 * @param buf Pointer to the output byte buffer.
 * @param state Pointer to the BUS_LocalStateB2 structure to serialize.
 * @return Number of bytes written to the buffer.
 */
size_t serializeLocalStateB2(uint8_t *buf, const BUS_LocalStateB2 *state);

/**
 * @brief Serialize a BUS_GlobalState structure into a byte buffer.
 * @param buf Pointer to the output byte buffer.
 * @param state Pointer to the BUS_GlobalState structure to serialize.
 * @return Number of bytes written to the buffer.
 */
size_t serializeGlobalState(uint8_t *buf, const BUS_GlobalState *state);

/**
 * @brief Serialize a BUS_Decision structure into a byte buffer.
 * @param buf Pointer to the output byte buffer.
 * @param state Pointer to the BUS_Decision structure to serialize.
 * @return Number of bytes written to the buffer.
 */
size_t serializeDecision(uint8_t *buf, const BUS_Decision *state);

#endif /* INC_BUS_SERIALIZE_H_ */
