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
 * @file sensors.h
 * @brief Sensor data type definitions for the rover bus.
 *
 * Defines structures and typedefs representing sensor readings such as
 * motor speed, temperature, battery level, sonar distances, gyroscope,
 * and remote controller inputs.
 */

#ifndef INC_BUS_SENSORS_H_
#define INC_BUS_SENSORS_H_

#include <stdint.h>

/**
 * @brief Motor speed readings for all four motors.
 */
typedef struct {
    float motor1; /**< Speed of motor 1 */
    float motor2; /**< Speed of motor 2 */
    float motor3; /**< Speed of motor 3 */
    float motor4; /**< Speed of motor 4 */
} BUS_Speed;

/**
 * @brief Temperature reading.
 */
typedef float Temperature;

/**
 * @brief Battery charge level (0-255).
 */
typedef uint8_t BatteryLevel;

/**
 * @brief Sonar distance readings for three directions.
 */
typedef struct {
    uint16_t left;  /**< Left sonar distance */
    uint16_t front; /**< Front sonar distance */
    uint16_t right; /**< Right sonar distance */
} BUS_Sonar;

/**
 * @brief Gyroscope reading.
 */
typedef uint16_t Gyroscope;

/**
 * @brief Remote controller input values.
 */
typedef struct {
    int16_t  y_lever; /**< Y-axis lever position */
    int16_t  x_lever; /**< X-axis lever position */

    uint16_t buttons; /**< Button bitmask */
} BUS_RemoteController;

#endif /* INC_BUS_SENSORS_H_ */
