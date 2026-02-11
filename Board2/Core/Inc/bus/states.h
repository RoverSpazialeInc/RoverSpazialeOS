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
 * @file states.h
 * @brief Composite state structures for the rover bus.
 *
 * Defines the local state structures for Board 1 and Board 2, as well as
 * the global state that aggregates both local states.
 */

#ifndef INC_BUS_STATES_H_
#define INC_BUS_STATES_H_

#include "sensors.h"

/**
 * @brief Local state of Board 1.
 *
 * Aggregates sensor data collected by Board 1: motor speeds,
 * temperature, battery level, and diagnostic flags.
 */
typedef struct {
    BUS_Speed    speed;            /**< Motor speed readings */
    Temperature  temperature;      /**< Temperature reading */
    BatteryLevel batteryLevel;     /**< Battery charge level */

    uint8_t      sensorReadings;   /**< Number of valid sensor readings */
    uint8_t      deadlineOccurred; /**< Non-zero if a deadline was missed */
} BUS_LocalStateB1;

/**
 * @brief Local state of Board 2.
 *
 * Aggregates sensor data collected by Board 2: sonar distances,
 * gyroscope, remote controller inputs, and diagnostic flags.
 */
typedef struct {
    BUS_Sonar            sonar;            /**< Sonar distance readings */
    Gyroscope            gyroscope;        /**< Gyroscope reading */
    BUS_RemoteController remoteController; /**< Remote controller inputs */

    uint8_t              sensorReadings;   /**< Number of valid sensor readings */
    uint8_t              deadlineOccurred; /**< Non-zero if a deadline was missed */
} BUS_LocalStateB2;

/**
 * @brief Global state combining both boards.
 *
 * Holds the local states of Board 1 and Board 2 together.
 */
typedef struct {
    BUS_LocalStateB1 localStateB1; /**< Board 1 local state */
    BUS_LocalStateB2 localStateB2; /**< Board 2 local state */
} BUS_GlobalState;

#endif /* INC_BUS_STATES_H_ */
