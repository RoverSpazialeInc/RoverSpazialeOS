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
 * @brief Scheduling constants for Board1 RTOS task periods and worst-case execution times.
 *
 * All T_* values are task periods in milliseconds (ms).
 * All WCET_* values are worst-case execution times in microseconds (us).
 */
#ifndef INC_CONSTANTS_SCHEDULING_CONSTANTS_H_
#define INC_CONSTANTS_SCHEDULING_CONSTANTS_H_

#include <stdint.h>

/**
 * @brief Converts a time value from milliseconds to microseconds.
 * @param ms_ Time in milliseconds.
 * @return Time in microseconds as a uint32_t.
 */
#define MS_TO_US(ms_) ((uint32_t)(ms_) * 1000u)

/* =========================
 *  Board1
 * ========================= */

/** @brief PID task period in milliseconds (50 Hz). */
#define T_PID           		20u
/** @brief PID task worst-case execution time in microseconds. */
#define WCET_PID_US            1000u
/** @brief PID task WCET alias. */
#define WCET_PID               WCET_PID_US

/** @brief Supervisor task period in milliseconds (20 Hz). */
#define T_SUPERVISOR           	50u
/** @brief Supervisor task worst-case execution time in milliseconds. */
#define WCET_SUPERVISOR_MS      20u
/** @brief Supervisor task worst-case execution time in microseconds. */
#define WCET_SUPERVISOR_US      MS_TO_US(WCET_SUPERVISOR_MS)
/** @brief Supervisor task WCET alias. */
#define WCET_SUPERVISOR         WCET_SUPERVISOR_US

/** @brief Battery task period in milliseconds (5 Hz). */
#define T_BATTERY           	200u
/** @brief Battery task worst-case execution time in microseconds. */
#define WCET_BATTERY_US         1000u
/** @brief Battery task WCET alias. */
#define WCET_BATTERY            WCET_BATTERY_US

/** @brief Temperature task period in milliseconds (5 Hz). */
#define T_TEMPERATURE           200u
/** @brief Temperature task worst-case execution time in microseconds. */
#define WCET_TEMPERATURE_US     1000u
/** @brief Temperature task WCET alias. */
#define WCET_TEMPERATURE        WCET_TEMPERATURE_US


#endif /* INC_CONSTANTS_SCHEDULING_CONSTANTS_H_ */
