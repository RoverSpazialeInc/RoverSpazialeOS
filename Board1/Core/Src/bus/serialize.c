#include "serialize.h"

#include <string.h>      /* memcpy */

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

size_t serializeGlobalState(uint8_t *buf, const BUS_GlobalState *state)
{
    if (!buf || !state) return 0;

    size_t i = 0;

    i += serializeLocalStateB1(&buf[i], &state->localStateB1);
    i += serializeLocalStateB2(&buf[i], &state->localStateB2);

    return i; /* = GLOBAL_STATE_FRAME_SIZE */
}

static inline uint8_t packLedsByte(const BUS_Leds *l)
{
    uint8_t b = 0;

    /* white: 1 bit */
    b |= ((uint8_t)(l->white.left  & 0x01u)) << 0;
    b |= ((uint8_t)(l->white.right & 0x01u)) << 1;

    /* red: 2 bit */
    b |= ((uint8_t)(l->red.left  & 0x03u)) << 2;
    b |= ((uint8_t)(l->red.right & 0x03u)) << 4;

    return b; /* bit6..7 liberi */
}


size_t serializeDecision(uint8_t *buf, const BUS_Decision *decision)
{
    if (!buf || !decision) return 0;

    size_t i = 0;

    /* Enum: 1 byte ciascuno (ENUM_FRAME_SIZE) */
    buf[i] = (uint8_t)decision->actuator;    i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->roverState;  i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->userAction;  i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->roverAction; i += ENUM_FRAME_SIZE;
    buf[i] = (uint8_t)decision->safeAction;  i += ENUM_FRAME_SIZE;

    /* SetPoint: 2 float => BUS_SETPOINT_FRAME_SIZE */
    memcpy(&buf[i], &decision->setPoint, BUS_SET_POINT_FRAME_SIZE);
    i += BUS_SET_POINT_FRAME_SIZE;

    /* LED: 1 byte compattato */
    buf[i++] = packLedsByte(&decision->leds);

    return i; /* = DECISION_FRAME_SIZE */
}
