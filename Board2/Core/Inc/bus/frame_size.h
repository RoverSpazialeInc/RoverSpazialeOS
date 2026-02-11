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
 * @file frame_size.h
 * @brief Serialization frame size definitions for bus data structures.
 *
 * Defines compile-time constants for the byte sizes of each field and
 * structure when serialized into a communication frame.
 */

#ifndef INC_BUS_FRAME_SIZE_H_
#define INC_BUS_FRAME_SIZE_H_

/** @name Elementary type sizes
 *  @{
 */
#define FLOAT_FRAME_SIZE                (4) /**< Size of a float in bytes */
#define ENUM_FRAME_SIZE                 (1) /**< Size of an enum in bytes */
#define SENSOR_READINGS_FRAME_SIZE      (1) /**< Size of the sensor readings flag in bytes */
#define DEADLINE_OCCURRED_FRAME_SIZE    (1) /**< Size of the deadline occurred flag in bytes */
/** @} */

/*
 * For other types, only integers with a specified byte count are used
 * (never bare int), so these two sizes should suffice.
 */

/** @name Sensor base type sizes
 *  @{
 */
#define SPEED_FRAME_SIZE             (FLOAT_FRAME_SIZE)              /**< Single speed value size */
#define BUS_SPEED_FRAME_SIZE         (SPEED_FRAME_SIZE * 4)          /**< BUS_Speed frame size (16 bytes) */

#define TEMPERATURE_FRAME_SIZE       (FLOAT_FRAME_SIZE)              /**< Temperature value size (4 bytes) */

#define BATTERY_LEVEL_FRAME_SIZE     (1)                             /**< Battery level size (uint8) */

#define SONAR_FRAME_SIZE             (2)                             /**< Single sonar value size (uint16) */
#define BUS_SONAR_FRAME_SIZE         (SONAR_FRAME_SIZE * 3)          /**< BUS_Sonar frame size (6 bytes) */

#define GYROSCOPE_FRAME_SIZE         (2)                             /**< Gyroscope value size (uint16) */

#define REMOTE_CONTROLLER_FRAME_SIZE (2 * 3)                         /**< Remote controller frame size (2 int16 + uint16 = 6 bytes) */
/** @} */

/** @name State frame sizes
 *  @{
 */
#define LOCAL_STATE_B1_FRAME_SIZE ( \
    BUS_SPEED_FRAME_SIZE + TEMPERATURE_FRAME_SIZE + \
    BATTERY_LEVEL_FRAME_SIZE + SENSOR_READINGS_FRAME_SIZE + \
    DEADLINE_OCCURRED_FRAME_SIZE)                /**< LocalStateB1 frame size (23 bytes) */

#define LOCAL_STATE_B2_FRAME_SIZE ( \
    BUS_SONAR_FRAME_SIZE + GYROSCOPE_FRAME_SIZE + \
    REMOTE_CONTROLLER_FRAME_SIZE + SENSOR_READINGS_FRAME_SIZE + \
    DEADLINE_OCCURRED_FRAME_SIZE)                /**< LocalStateB2 frame size (16 bytes) */

#define GLOBAL_STATE_FRAME_SIZE (LOCAL_STATE_B1_FRAME_SIZE + \
    LOCAL_STATE_B2_FRAME_SIZE)                   /**< GlobalState frame size (39 bytes) */
/** @} */

/** @name Decision / Control frame sizes
 *  @{
 */
#define SET_POINT_FRAME_SIZE             (FLOAT_FRAME_SIZE)           /**< Single setpoint value size */
#define BUS_SET_POINT_FRAME_SIZE         (SET_POINT_FRAME_SIZE * 2)   /**< BUS_SetPoint frame size (8 bytes) */

#define DECISION_FRAME_SIZE              ((5 * ENUM_FRAME_SIZE) + \
                                         BUS_SET_POINT_FRAME_SIZE + 1) /**< Decision frame size (14 bytes) */
/** @} */

#endif /* INC_BUS_FRAME_SIZE_H_ */
    