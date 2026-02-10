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
 * @brief CMSIS-RTOS v2 / FreeRTOS event-flag bitmask definitions.
 *
 * Provides single-bit flags used for inter-task synchronisation and
 * status signalling across all Board2 periodic tasks (controller,
 * gyroscope, sonar) as well as the polling server.
 */

#ifndef INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_
#define INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_

/** @name General Synchronisation Flags
 *  @{ */
/** @brief Start flag (bit 0). */
#define FLAG_START                  (1U << 0)
/** @brief Synchronisation flag (bit 1). */
#define FLAG_SYNC                   (1U << 1)
/** @brief Acknowledge flag (bit 2). */
#define FLAG_ACK                    (1U << 2)
/** @} */

/** @name Controller / Pad Flags
 *  @{ */
/** @brief Pad data received successfully (bit 3). */
#define FLAG_PAD_OK                 (1U << 3)
/** @brief Pad communication error (bit 4). */
#define FLAG_PAD_ERROR              (1U << 4)
/** @} */

/** @name Gyroscope Flags
 *  @{ */
/** @brief Gyroscope data received successfully (bit 5). */
#define FLAG_GYRO_OK                (1U << 5)
/** @brief Gyroscope communication error (bit 6). */
#define FLAG_GYRO_ERROR             (1U << 6)
/** @} */

/** @name Sonar Left Flags
 *  @{ */
/** @brief Left sonar measurement successful (bit 7). */
#define FLAG_SONAR_LEFT_OK          (1U << 7)
/** @brief Left sonar measurement timeout (bit 8). */
#define FLAG_SONAR_LEFT_TIMEOUT     (1U << 8)
/** @} */

/** @name Sonar Front Flags
 *  @{ */
/** @brief Front sonar measurement successful (bit 9). */
#define FLAG_SONAR_FRONT_OK         (1U << 9)
/** @brief Front sonar measurement timeout (bit 10). */
#define FLAG_SONAR_FRONT_TIMEOUT    (1U << 10)
/** @} */

/** @name Sonar Right Flags
 *  @{ */
/** @brief Right sonar measurement successful (bit 11). */
#define FLAG_SONAR_RIGHT_OK         (1U << 11)
/** @brief Right sonar measurement timeout (bit 12). */
#define FLAG_SONAR_RIGHT_TIMEOUT    (1U << 12)
/** @} */

/** @name Degraded Mode Flag
 *  @{ */
/** @brief System operating in degraded mode (bit 13). */
#define FLAG_DEGRADED               (1U << 13)
/** @} */

/**
 * @brief Bitmask for all events the Polling Server waits on.
 *
 * Includes every task-completion and error flag except the general
 * synchronisation flags (START, SYNC, ACK).
 */
#define FLAGS_POLLING_SERVER_WAIT   (FLAG_PAD_OK | FLAG_PAD_ERROR | \
                                     FLAG_GYRO_OK | FLAG_GYRO_ERROR | \
                                     FLAG_SONAR_LEFT_OK | FLAG_SONAR_LEFT_TIMEOUT | \
                                     FLAG_SONAR_FRONT_OK | FLAG_SONAR_FRONT_TIMEOUT | \
                                     FLAG_SONAR_RIGHT_OK | FLAG_SONAR_RIGHT_TIMEOUT)

#endif /* INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_ */
