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
 * @file serialize.c
 * @brief Serialization functions for bus data structures.
 *
 * Implements serialization of typed bus structures into raw byte buffers
 * for transmission over the communication bus.
 */

#include "serialize.h"

#include <string.h>      /* memcpy */

/**
 * @brief Serialize a BUS_LocalStateB1 structure into a byte buffer.
 *
 * @param[out] buf   Pointer to the destination byte buffer.
 * @param[in]  state Pointer to the source structure.
 * @return Number of bytes written (LOCAL_STATE_B1_FRAME_SIZE), or 0 on error.
 */
size_t serializeLocalStateB1(uint8_t *buf, const BUS_LocalStateB1 *state)
{
    if (!buf || !state) return 0;

    size_t i = 0;

    /* speed */
    memcpy(&buf[i], &state->speed, BUS_SPEED_FRAME_SIZE);
    i += BUS_SPEED_FRAME_SIZE;

    /* temperature */
    memcpy(&buf[i], &state->temperature, TEMPERATURE_FRAME_SIZE);
    i += TEMPERATURE_FRAME_SIZE;

    /* batteryLevel */
    memcpy(&buf[i], &state->batteryLevel, BATTERY_LEVEL_FRAME_SIZE);
    i += BATTERY_LEVEL_FRAME_SIZE;

    /*sensorReadings*/
    memcpy(&buf[i], &state->sensorReadings, SENSOR_READINGS_FRAME_SIZE);
    i += SENSOR_READINGS_FRAME_SIZE;

    /*deadlineOccurred*/
    memcpy(&buf[i], &state->deadlineOccurred, DEADLINE_OCCURRED_FRAME_SIZE);
    i += DEADLINE_OCCURRED_FRAME_SIZE;

    return i; /* = LOCAL_STATE_B1_FRAME_SIZE */
}

/**
 * @brief Serialize a BUS_LocalStateB2 structure into a byte buffer.
 *
 * @param[out] buf   Pointer to the destination byte buffer.
 * @param[in]  state Pointer to the source structure.
 * @return Number of bytes written (LOCAL_STATE_B2_FRAME_SIZE), or 0 on error.
 */
size_t serializeLocalStateB2(uint8_t *buf, const BUS_LocalStateB2 *state)
{
    if (!buf || !state) return 0;

    size_t i = 0;

    /* sonar */
    memcpy(&buf[i], &state->sonar, BUS_SONAR_FRAME_SIZE);
    i += BUS_SONAR_FRAME_SIZE;

    /* gyroscope */
    memcpy(&buf[i], &state->gyroscope, GYROSCOPE_FRAME_SIZE);
    i += GYROSCOPE_FRAME_SIZE;

    /* remoteController */
    memcpy(&buf[i], &state->remoteController, REMOTE_CONTROLLER_FRAME_SIZE);
    i += REMOTE_CONTROLLER_FRAME_SIZE;

    /*sensorReadings*/
    memcpy(&buf[i], &state->sensorReadings, SENSOR_READINGS_FRAME_SIZE);
    i += SENSOR_READINGS_FRAME_SIZE;

    /*deadlineOccurred*/
    memcpy(&buf[i], &state->deadlineOccurred, DEADLINE_OCCURRED_FRAME_SIZE);
    i += DEADLINE_OCCURRED_FRAME_SIZE;

    return i; /* = LOCAL_STATE_B2_FRAME_SIZE */
}

/**
 * @brief Serialize a BUS_GlobalState structure into a byte buffer.
 *
 * Sequentially serializes BUS_LocalStateB1 and BUS_LocalStateB2 into
 * the buffer.
 *
 * @param[out] buf   Pointer to the destination byte buffer.
 * @param[in]  state Pointer to the source structure.
 * @return Number of bytes written (GLOBAL_STATE_FRAME_SIZE), or 0 on error.
 */
size_t serializeGlobalState(uint8_t *buf, const BUS_GlobalState *state)
{
    if (!buf || !state) return 0;

    size_t i = 0;

    i += serializeLocalStateB1(&buf[i], &state->localStateB1);
    i += serializeLocalStateB2(&buf[i], &state->localStateB2);

    return i; /* = GLOBAL_STATE_FRAME_SIZE */
}

/**
 * @brief Pack a BUS_Leds structure into a single byte.
 *
 * Encodes white and red LED states into individual bits of a byte.
 *
 * @param[in] l Pointer to the BUS_Leds structure.
 * @return Packed LED byte (bits 6..7 unused).
 */
static inline uint8_t packLedsByte(const BUS_Leds *l)
{
    uint8_t b = 0;

    /* white: 1 bit */
    b |= ((uint8_t)(l->white.left  & 0x01u)) << 0;
    b |= ((uint8_t)(l->white.right & 0x01u)) << 1;

    /* red: 2 bit */
    b |= ((uint8_t)(l->red.left  & 0x03u)) << 2;
    b |= ((uint8_t)(l->red.right & 0x03u)) << 4;

    return b; /* bits 6..7 unused */
}


/**
 * @brief Serialize a BUS_Decision structure into a byte buffer.
 *
 * Writes enum fields, the set-point, and the packed LED byte into
 * the destination buffer.
 *
 * @param[out] buf      Pointer to the destination byte buffer.
 * @param[in]  decision Pointer to the source structure.
 * @return Number of bytes written (DECISION_FRAME_SIZE), or 0 on error.
 */
size_t serializeDecision(uint8_t *buf, const BUS_Decision *decision)
{
    if (!buf || !decision) return 0;

    size_t i = 0;

    /* Enum: 1 byte each (ENUM_FRAME_SIZE) */
    buf[i] = (uint8_t)decision->actuator;    i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->roverState;  i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->userAction;  i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->roverAction; i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->safeAction;  i += ENUM_FRAME_SIZE;

    /* SetPoint: 2 float => BUS_SETPOINT_FRAME_SIZE */
    memcpy(&buf[i], &decision->setPoint, BUS_SET_POINT_FRAME_SIZE);
    i += BUS_SET_POINT_FRAME_SIZE;

    /* LED: 1 packed byte */
    buf[i++] = packLedsByte(&decision->leds);

    return i; /* = DECISION_FRAME_SIZE */
}
