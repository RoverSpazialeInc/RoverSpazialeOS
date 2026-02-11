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
 * @file comparator.h
 * @brief Equality comparison functions for bus data structures.
 *
 * Declares functions to compare instances of sensor, state, and decision
 * bus structures for equality.
 */

#ifndef INC_BUS_COMPARATOR_H_
#define INC_BUS_COMPARATOR_H_

#include <stdint.h>
#include "decision.h"
#include "states.h"

/** @name Sensor structure comparators
 *  @{
 */

/**
 * @brief Compare two BUS_Speed structures for equality.
 * @param a Pointer to the first BUS_Speed structure.
 * @param b Pointer to the second BUS_Speed structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_Speed_Equals(const BUS_Speed *a, const BUS_Speed *b);

/**
 * @brief Compare two BUS_Sonar structures for equality.
 * @param a Pointer to the first BUS_Sonar structure.
 * @param b Pointer to the second BUS_Sonar structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_Sonar_Equals(const BUS_Sonar *a, const BUS_Sonar *b);

/**
 * @brief Compare two BUS_RemoteController structures for equality.
 * @param a Pointer to the first BUS_RemoteController structure.
 * @param b Pointer to the second BUS_RemoteController structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_RemoteController_Equals(const BUS_RemoteController *a, const BUS_RemoteController *b);

/** @} */

/** @name State structure comparators
 *  @{
 */

/**
 * @brief Compare two BUS_LocalStateB1 structures for equality.
 * @param a Pointer to the first BUS_LocalStateB1 structure.
 * @param b Pointer to the second BUS_LocalStateB1 structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_LocalStateB1_Equals(const BUS_LocalStateB1 *a, const BUS_LocalStateB1 *b);

/**
 * @brief Compare two BUS_LocalStateB2 structures for equality.
 * @param a Pointer to the first BUS_LocalStateB2 structure.
 * @param b Pointer to the second BUS_LocalStateB2 structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_LocalStateB2_Equals(const BUS_LocalStateB2 *a, const BUS_LocalStateB2 *b);

/**
 * @brief Compare two BUS_GlobalState structures for equality.
 * @param a Pointer to the first BUS_GlobalState structure.
 * @param b Pointer to the second BUS_GlobalState structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_GlobalState_Equals(const BUS_GlobalState *a, const BUS_GlobalState *b);

/** @} */

/** @name Decision structure comparators
 *  @{
 */

/**
 * @brief Compare two BUS_SetPoint structures for equality.
 * @param a Pointer to the first BUS_SetPoint structure.
 * @param b Pointer to the second BUS_SetPoint structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_SetPoint_Equals(const BUS_SetPoint *a, const BUS_SetPoint *b);

/**
 * @brief Compare two BUS_RedLeds structures for equality.
 * @param a Pointer to the first BUS_RedLeds structure.
 * @param b Pointer to the second BUS_RedLeds structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_RedLeds_Equals(const BUS_RedLeds *a, const BUS_RedLeds *b);

/**
 * @brief Compare two BUS_WhiteLeds structures for equality.
 * @param a Pointer to the first BUS_WhiteLeds structure.
 * @param b Pointer to the second BUS_WhiteLeds structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_WhiteLeds_Equals(const BUS_WhiteLeds *a, const BUS_WhiteLeds *b);

/**
 * @brief Compare two BUS_Leds structures for equality.
 * @param a Pointer to the first BUS_Leds structure.
 * @param b Pointer to the second BUS_Leds structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_Leds_Equals(const BUS_Leds *a, const BUS_Leds *b);

/**
 * @brief Compare two BUS_Decision structures for equality.
 * @param a Pointer to the first BUS_Decision structure.
 * @param b Pointer to the second BUS_Decision structure.
 * @return 1 if equal, 0 otherwise.
 */
uint8_t BUS_Decision_Equals(const BUS_Decision *a, const BUS_Decision *b);

/** @} */

#endif /* INC_BUS_COMPARATOR_H_ */
