#include "deserialize.h"

#include <string.h>     /* memcpy */


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

static inline void unpackLedsByte(uint8_t b, BUS_Leds *l)
{
    l->white.left  = (ENUM_StatusWhiteLed)((b >> 0) & 0x01u);
    l->white.right = (ENUM_StatusWhiteLed)((b >> 1) & 0x01u);

    l->red.left    = (ENUM_StatusRedLed)((b >> 2) & 0x03u);
    l->red.right   = (ENUM_StatusRedLed)((b >> 4) & 0x03u);

    /* sanifica se arrivano valori non validi */
    if (l->red.left  > RED_ON) l->red.left  = RED_OFF;
    if (l->red.right > RED_ON) l->red.right = RED_OFF;
}

int deserializeDecision(const uint8_t *buf, size_t len, BUS_Decision *decision)
{
    if (!buf || !decision) return -1;
    if (len < DECISION_FRAME_SIZE) return -1;

    size_t i = 0;

    /* Enum: 1 byte ciascuno (ENUM_FRAME_SIZE) */
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

    /* LED: 1 byte compattato */
    unpackLedsByte(buf[i++], &decision->leds);

    return 0;
}
