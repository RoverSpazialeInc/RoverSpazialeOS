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
 * @file event_flags_constant.h
 * @brief Bitmask definitions for CMSIS-RTOS v2 / FreeRTOS event flags.
 *
 * This file defines the event flag bitmasks used for inter-task
 * synchronization and signaling.
 */
#ifndef INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_
#define INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_

/** @brief Event flag indicating a start request (bit 0). */
#define FLAG_START   (1U << 0)

/** @brief Event flag used for task synchronization (bit 1). */
#define FLAG_SYNC    (1U << 1)

/** @brief Event flag used for acknowledgment signaling (bit 2). */
#define FLAG_ACK     (1U << 2)


#endif /* INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_ */
