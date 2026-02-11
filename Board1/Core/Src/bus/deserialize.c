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
 * @file deserialize.c
 * @brief Deserialization functions for bus data structures.
 *
 * Implements deserialization of raw byte buffers into typed bus structures
 * such as local board states, global state, and decision frames.
 */

#include "deserialize.h"

#include <string.h>     /* memcpy */


/**
 * @brief Deserialize a byte buffer into a BUS_LocalStateB1 structure.
 *
 * @param[in]  buf   Pointer to the source byte buffer.
 * @param[in]  len   Length of the buffer in bytes.
 * @param[out] state Pointer to the destination structure.
 * @return 0 on success, -1 on invalid arguments or insufficient length.
 */
int deserializeLocalStateB1(const uint8_t *buf, size_t len, BUS_LocalStateB1 *state)
{
    if (!buf || !state) return -1;
    if (len < LOCAL_STATE_B1_FRAME_SIZE) return -1;

    size_t i = 0;

    /* speed */
    memcpy(&state->speed, &buf[i], BUS_SPEED_FRAME_SIZE);
    i += BUS_SPEED_FRAME_SIZE;

    /* temperature */
    memcpy(&state->temperature, &buf[i], TEMPERATURE_FRAME_SIZE);
    i += TEMPERATURE_FRAME_SIZE;

    /* batteryLevel */
    memcpy(&state->batteryLevel, &buf[i], BATTERY_LEVEL_FRAME_SIZE);
    i += BATTERY_LEVEL_FRAME_SIZE;

    /*sensorReadings*/
    memcpy(&state->sensorReadings, &buf[i], SENSOR_READINGS_FRAME_SIZE);
    i += SENSOR_READINGS_FRAME_SIZE;

    /*deadlineOccurred*/
    memcpy(&state->deadlineOccurred, &buf[i], DEADLINE_OCCURRED_FRAME_SIZE);
    i += DEADLINE_OCCURRED_FRAME_SIZE;

    return 0;
}

/**
 * @brief Deserialize a byte buffer into a BUS_LocalStateB2 structure.
 *
 * @param[in]  buf   Pointer to the source byte buffer.
 * @param[in]  len   Length of the buffer in bytes.
 * @param[out] state Pointer to the destination structure.
 * @return 0 on success, -1 on invalid arguments or insufficient length.
 */
int deserializeLocalStateB2(const uint8_t *buf, size_t len, BUS_LocalStateB2 *state)
{
    if (!buf || !state) return -1;
    if (len < LOCAL_STATE_B2_FRAME_SIZE) return -1;

    size_t i = 0;

    /* sonar */
    memcpy(&state->sonar, &buf[i], BUS_SONAR_FRAME_SIZE);
    i += BUS_SONAR_FRAME_SIZE;

    /* gyroscope */
    memcpy(&state->gyroscope, &buf[i], GYROSCOPE_FRAME_SIZE);
    i += GYROSCOPE_FRAME_SIZE;

    /* remoteController */
    memcpy(&state->remoteController, &buf[i], REMOTE_CONTROLLER_FRAME_SIZE);
    i += REMOTE_CONTROLLER_FRAME_SIZE;

    /*sensorReadings*/
    memcpy(&state->sensorReadings, &buf[i], SENSOR_READINGS_FRAME_SIZE);
    i += SENSOR_READINGS_FRAME_SIZE;

    /*deadlineOccurred*/
    memcpy(&state->deadlineOccurred, &buf[i], DEADLINE_OCCURRED_FRAME_SIZE);
    i += DEADLINE_OCCURRED_FRAME_SIZE;

    return 0;
}

/**
 * @brief Deserialize a byte buffer into a BUS_GlobalState structure.
 *
 * Sequentially deserializes BUS_LocalStateB1 and BUS_LocalStateB2 from
 * the buffer into the corresponding fields of the global state.
 *
 * @param[in]  buf   Pointer to the source byte buffer.
 * @param[in]  len   Length of the buffer in bytes.
 * @param[out] state Pointer to the destination structure.
 * @return 0 on success, -1 on invalid arguments or insufficient length.
 */
int deserializeGlobalState(const uint8_t *buf, size_t len, BUS_GlobalState *state)
{
    if (!buf || !state) return -1;
    if (len < GLOBAL_STATE_FRAME_SIZE) return -1;

    size_t i = 0;

    if (deserializeLocalStateB1(&buf[i], LOCAL_STATE_B1_FRAME_SIZE, &state->localStateB1) != 0)
        return -1;
    i += LOCAL_STATE_B1_FRAME_SIZE;

    if (deserializeLocalStateB2(&buf[i], LOCAL_STATE_B2_FRAME_SIZE, &state->localStateB2) != 0)
        return -1;

    return 0;
}

/**
 * @brief Unpack a single byte into a BUS_Leds structure.
 *
 * Extracts white and red LED states from the individual bits of the
 * packed byte. Sanitizes invalid red LED values to RED_OFF.
 *
 * @param[in]  b Packed LED byte.
 * @param[out] l Pointer to the destination BUS_Leds structure.
 */
static inline void unpackLedsByte(uint8_t b, BUS_Leds *l)
{
    l->white.left  = (ENUM_StatusWhiteLed)((b >> 0) & 0x01u);
    l->white.right = (ENUM_StatusWhiteLed)((b >> 1) & 0x01u);

    l->red.left    = (ENUM_StatusRedLed)((b >> 2) & 0x03u);
    l->red.right   = (ENUM_StatusRedLed)((b >> 4) & 0x03u);

    /* sanitize invalid values */
    if (l->red.left  > RED_ON) l->red.left  = RED_OFF;
    if (l->red.right > RED_ON) l->red.right = RED_OFF;
}

/**
 * @brief Deserialize a byte buffer into a BUS_Decision structure.
 *
 * Extracts enum fields, the set-point, and the packed LED byte from
 * the source buffer into the decision structure.
 *
 * @param[in]  buf      Pointer to the source byte buffer.
 * @param[in]  len      Length of the buffer in bytes.
 * @param[out] decision Pointer to the destination structure.
 * @return 0 on success, -1 on invalid arguments or insufficient length.
 */
int deserializeDecision(const uint8_t *buf, size_t len, BUS_Decision *decision)
{
    if (!buf || !decision) return -1;
    if (len < DECISION_FRAME_SIZE) return -1;

    size_t i = 0;

    /* Enum: 1 byte each (ENUM_FRAME_SIZE) */
    uint8_t tmp;

    tmp = buf[i]; i += ENUM_FRAME_SIZE;
    decision->actuator = (ENUM_Actuator)tmp;

    tmp = buf[i]; i += SENSOR_READINGS_FRAME_SIZE;
    decision->roverState = (ENUM_StatusRover)tmp;

    tmp = buf[i]; i += ENUM_FRAME_SIZE;
    decision->userAction = (ENUM_UserAction)tmp;

    tmp = buf[i]; i += ENUM_FRAME_SIZE;
    decision->roverAction = (ENUM_RoverAction)tmp;

    tmp = buf[i]; i += ENUM_FRAME_SIZE;
    decision->safeAction = (ENUM_SafeAction)tmp;

    /* SetPoint: 2 float => BUS_SETPOINT_FRAME_SIZE */
    memcpy(&decision->setPoint, &buf[i], BUS_SET_POINT_FRAME_SIZE);
    i += BUS_SET_POINT_FRAME_SIZE;

    /* LED: 1 packed byte */
    unpackLedsByte(buf[i++], &decision->leds);

    return 0;
}
