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
 * @file scheduling_constants.h
 * @brief Real-time scheduling parameters for Board2 tasks.
 *
 * Contains period and worst-case execution time (WCET) definitions for every
 * periodic task running on Board2. All @c T_* values are periods in
 * milliseconds (ms) and all @c WCET_* values are execution times in
 * microseconds (us).
 */

#ifndef INC_CONSTANTS_SCHEDULING_CONSTANTS_H_
#define INC_CONSTANTS_SCHEDULING_CONSTANTS_H_

#include <stdint.h>

/**
 * @brief Converts a time value from milliseconds to microseconds.
 * @param ms_ Time value in milliseconds.
 * @return Equivalent time value in microseconds (uint32_t).
 */
#define MS_TO_US(ms_) ((uint32_t)(ms_) * 1000u)

/* =========================
 *  Board2
 * ========================= */

/** @name Controller Task
 *  @{ */
/** @brief Period of the remote controller task (ms) – 50 Hz. */
#define T_REMOTE_CONTROLLER           20u
/** @brief WCET of the controller task (us). */
#define WCET_CONTROLLER_US           200u
/** @brief Alias for @ref WCET_CONTROLLER_US. */
#define WCET_CONTROLLER              WCET_CONTROLLER_US
/** @} */

/** @name Gyroscope Task
 *  @{ */
/** @brief Period of the gyroscope task (ms) – 25 Hz. */
#define T_GYROSCOPE                   40u
/** @brief WCET of the gyroscope task (us). */
#define WCET_GYROSCOPE_US            200u
/** @brief Alias for @ref WCET_GYROSCOPE_US. */
#define WCET_GYROSCOPE               WCET_GYROSCOPE_US
/** @} */

/** @name Supervisor Task
 *  @{ */
/** @brief Period of the supervisor task (ms) – 20 Hz. */
#define T_SUPERVISOR             	 50u
/** @brief WCET of the supervisor task (ms). */
#define WCET_SUPERVISOR_MS           15u
/** @brief WCET of the supervisor task (us). */
#define WCET_SUPERVISOR_US           MS_TO_US(WCET_SUPERVISOR_MS)
/** @brief Alias for @ref WCET_SUPERVISOR_US. */
#define WCET_SUPERVISOR              WCET_SUPERVISOR_US
/** @} */

/** @name Sonar Task
 *  @{ */
/** @brief Period of the sonar task (ms) – 10 Hz. */
#define T_SONAR          			 100u
/** @brief WCET of the sonar task (us). */
#define WCET_SONAR_US               2000u
/** @brief Alias for @ref WCET_SONAR_US. */
#define WCET_SONAR                  WCET_SONAR_US
/** @} */

/** @name Polling Server
 *  @{ */
/** @brief Period of the polling server (ms) – 100 Hz. */
#define T_POLLING_SERVER 	  		 10u
/** @brief WCET of the polling server (us). */
#define WCET_POLLING_SERVER_US      1000u
/** @brief Alias for @ref WCET_POLLING_SERVER_US. */
#define WCET_POLLING_SERVER         WCET_POLLING_SERVER_US
/** @} */

#endif /* INC_CONSTANTS_SCHEDULING_CONSTANTS_H_ */
