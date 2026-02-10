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
 * @brief System phase definitions for inter-board synchronization.
 *
 * Enumerates the high-level operating phases of the system: a
 * synchronization phase during which the boards align their clocks,
 * followed by the normal working phase.
 *
 */

#ifndef INC_SYNCHRONIZATION_PHASE_H_
#define INC_SYNCHRONIZATION_PHASE_H_

/**
 * @brief Enumeration of the system operating phases.
 */
typedef enum {
    SYNCHRONIZATION_PHASE = 0, /**< @brief Boards are synchronizing their clocks. */
    WORKING_PHASE              /**< @brief Normal operation after synchronization. */
} system_phase_t;

#endif /* INC_SYNCHRONIZATION_PHASE_H_ */
