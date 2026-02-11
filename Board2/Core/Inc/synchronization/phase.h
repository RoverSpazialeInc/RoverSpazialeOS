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
 * @file phase.h
 * @brief System phase enumeration.
 *
 * Defines the possible operational phases of the system,
 * distinguishing between the initial synchronization phase
 * and the normal working phase.
 */

#ifndef INC_SYNCHRONIZATION_PHASE_H_
#define INC_SYNCHRONIZATION_PHASE_H_

/**
 * @brief Enumerates the operational phases of the system.
 */
typedef enum {
    SYNCHRONIZATION_START = 0, /**< Initial inter-board synchronization phase. */
	SYNCHRONIZATION_SUPERVISOR, /**< Synchronization completed, but not yet in working phase. */
    WORKING_PHASE              /**< Normal working phase after synchronization. */
} system_phase_t;

#endif /* INC_SYNCHRONIZATION_PHASE_H_ */
