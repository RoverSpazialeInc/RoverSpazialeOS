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
 * @file comparator.c
 * @brief Equality comparison functions for bus data structures.
 *
 * Implements field-by-field equality checks for sensor, state, and
 * decision structures exchanged over the communication bus.
 */

#include "bus/comparator.h"

/* sensors.h structs */

/**
 * @brief Compare two BUS_Speed structures for equality.
 * @param[in] a Pointer to the first BUS_Speed structure.
 * @param[in] b Pointer to the second BUS_Speed structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_Speed_Equals(const BUS_Speed *a, const BUS_Speed *b) {
    if (a == b) return 1;
    if (a->motor1 != b->motor1) return 0;
    if (a->motor2 != b->motor2) return 0;
    if (a->motor3 != b->motor3) return 0;
    if (a->motor4 != b->motor4) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_Sonar structures for equality.
 * @param[in] a Pointer to the first BUS_Sonar structure.
 * @param[in] b Pointer to the second BUS_Sonar structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_Sonar_Equals(const BUS_Sonar *a, const BUS_Sonar *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->front != b->front) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_RemoteController structures for equality.
 * @param[in] a Pointer to the first BUS_RemoteController structure.
 * @param[in] b Pointer to the second BUS_RemoteController structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_RemoteController_Equals(const BUS_RemoteController *a, const BUS_RemoteController *b) {
    if (a == b) return 1;
    if (a->y_lever != b->y_lever) return 0;
    if (a->x_lever != b->x_lever) return 0;
    if (a->buttons != b->buttons) return 0;
    return 1;
}

/* states.h structs */

/**
 * @brief Compare two BUS_LocalStateB1 structures for equality.
 * @param[in] a Pointer to the first BUS_LocalStateB1 structure.
 * @param[in] b Pointer to the second BUS_LocalStateB1 structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_LocalStateB1_Equals(const BUS_LocalStateB1 *a, const BUS_LocalStateB1 *b) {
    if (a == b) return 1;
    if (!BUS_Speed_Equals(&a->speed, &b->speed)) return 0;
    if (a->temperature != b->temperature) return 0;
    if (a->batteryLevel != b->batteryLevel) return 0;
    if (a->sensorReadings != b->sensorReadings) return 0;
    if (a->deadlineOccurred != b->deadlineOccurred) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_LocalStateB2 structures for equality.
 * @param[in] a Pointer to the first BUS_LocalStateB2 structure.
 * @param[in] b Pointer to the second BUS_LocalStateB2 structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_LocalStateB2_Equals(const BUS_LocalStateB2 *a, const BUS_LocalStateB2 *b) {
    if (a == b) return 1;
    if (!BUS_Sonar_Equals(&a->sonar, &b->sonar)) return 0;
    if (a->gyroscope != b->gyroscope) return 0;
    if (!BUS_RemoteController_Equals(&a->remoteController, &b->remoteController)) return 0;
    if (a->sensorReadings != b->sensorReadings) return 0;
    if (a->deadlineOccurred != b->deadlineOccurred) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_GlobalState structures for equality.
 * @param[in] a Pointer to the first BUS_GlobalState structure.
 * @param[in] b Pointer to the second BUS_GlobalState structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_GlobalState_Equals(const BUS_GlobalState *a, const BUS_GlobalState *b) {
    if (a == b) return 1;
    if (!BUS_LocalStateB1_Equals(&a->localStateB1, &b->localStateB1)) return 0;
    if (!BUS_LocalStateB2_Equals(&a->localStateB2, &b->localStateB2)) return 0;
    return 1;
}

/* decision.h structs */

/**
 * @brief Compare two BUS_SetPoint structures for equality.
 * @param[in] a Pointer to the first BUS_SetPoint structure.
 * @param[in] b Pointer to the second BUS_SetPoint structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_SetPoint_Equals(const BUS_SetPoint *a, const BUS_SetPoint *b) {
    if (a == b) return 1;
    if (a->leftAxis != b->leftAxis) return 0;
    if (a->rightAxis != b->rightAxis) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_RedLeds structures for equality.
 * @param[in] a Pointer to the first BUS_RedLeds structure.
 * @param[in] b Pointer to the second BUS_RedLeds structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_RedLeds_Equals(const BUS_RedLeds *a, const BUS_RedLeds *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_WhiteLeds structures for equality.
 * @param[in] a Pointer to the first BUS_WhiteLeds structure.
 * @param[in] b Pointer to the second BUS_WhiteLeds structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_WhiteLeds_Equals(const BUS_WhiteLeds *a, const BUS_WhiteLeds *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_Leds structures for equality.
 * @param[in] a Pointer to the first BUS_Leds structure.
 * @param[in] b Pointer to the second BUS_Leds structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_Leds_Equals(const BUS_Leds *a, const BUS_Leds *b) {
    if (a == b) return 1;
    if (!BUS_WhiteLeds_Equals(&a->white, &b->white)) return 0;
    if (!BUS_RedLeds_Equals(&a->red, &b->red)) return 0;
    return 1;
}

/**
 * @brief Compare two BUS_Decision structures for equality.
 * @param[in] a Pointer to the first BUS_Decision structure.
 * @param[in] b Pointer to the second BUS_Decision structure.
 * @return 1 if all fields are equal, 0 otherwise.
 */
uint8_t BUS_Decision_Equals(const BUS_Decision *a, const BUS_Decision *b) {
    if (a == b) return 1;
    if (a->actuator != b->actuator) return 0;
    if (a->roverState != b->roverState) return 0;
    if (a->userAction != b->userAction) return 0;
    if (a->roverAction != b->roverAction) return 0;
    if (a->safeAction != b->safeAction) return 0;
    if (!BUS_SetPoint_Equals(&a->setPoint, &b->setPoint)) return 0;
    if (!BUS_Leds_Equals(&a->leds, &b->leds)) return 0;
    return 1;
}
