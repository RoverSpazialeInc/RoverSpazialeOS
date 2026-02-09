#include "bus/comparator.h"

/* sensors.h structs */

uint8_t BUS_Speed_Equals(const BUS_Speed *a, const BUS_Speed *b) {
    if (a == b) return 1;
    if (a->motor1 != b->motor1) return 0;
    if (a->motor2 != b->motor2) return 0;
    if (a->motor3 != b->motor3) return 0;
    if (a->motor4 != b->motor4) return 0;
    return 1;
}

uint8_t BUS_Sonar_Equals(const BUS_Sonar *a, const BUS_Sonar *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->front != b->front) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

uint8_t BUS_RemoteController_Equals(const BUS_RemoteController *a, const BUS_RemoteController *b) {
    if (a == b) return 1;
    if (a->y_lever != b->y_lever) return 0;
    if (a->x_lever != b->x_lever) return 0;
    if (a->buttons != b->buttons) return 0;
    return 1;
}

/* states.h structs */

uint8_t BUS_LocalStateB1_Equals(const BUS_LocalStateB1 *a, const BUS_LocalStateB1 *b) {
    if (a == b) return 1;
    if (!BUS_Speed_Equals(&a->speed, &b->speed)) return 0;
    if (a->temperature != b->temperature) return 0;
    if (a->batteryLevel != b->batteryLevel) return 0;
    if (a->sensorReadings != b->sensorReadings) return 0;
    if (a->deadlineOccurred != b->deadlineOccurred) return 0;
    return 1;
}

uint8_t BUS_LocalStateB2_Equals(const BUS_LocalStateB2 *a, const BUS_LocalStateB2 *b) {
    if (a == b) return 1;
    if (!BUS_Sonar_Equals(&a->sonar, &b->sonar)) return 0;
    if (a->gyroscope != b->gyroscope) return 0;
    if (!BUS_RemoteController_Equals(&a->remoteController, &b->remoteController)) return 0;
    if (a->sensorReadings != b->sensorReadings) return 0;
    if (a->deadlineOccurred != b->deadlineOccurred) return 0;
    return 1;
}

uint8_t BUS_GlobalState_Equals(const BUS_GlobalState *a, const BUS_GlobalState *b) {
    if (a == b) return 1;
    if (!BUS_LocalStateB1_Equals(&a->localStateB1, &b->localStateB1)) return 0;
    if (!BUS_LocalStateB2_Equals(&a->localStateB2, &b->localStateB2)) return 0;
    return 1;
}

/* decision.h structs */

uint8_t BUS_SetPoint_Equals(const BUS_SetPoint *a, const BUS_SetPoint *b) {
    if (a == b) return 1;
    if (a->leftAxis != b->leftAxis) return 0;
    if (a->rightAxis != b->rightAxis) return 0;
    return 1;
}

uint8_t BUS_RedLeds_Equals(const BUS_RedLeds *a, const BUS_RedLeds *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

uint8_t BUS_WhiteLeds_Equals(const BUS_WhiteLeds *a, const BUS_WhiteLeds *b) {
    if (a == b) return 1;
    if (a->left != b->left) return 0;
    if (a->right != b->right) return 0;
    return 1;
}

uint8_t BUS_Leds_Equals(const BUS_Leds *a, const BUS_Leds *b) {
    if (a == b) return 1;
    if (!BUS_WhiteLeds_Equals(&a->white, &b->white)) return 0;
    if (!BUS_RedLeds_Equals(&a->red, &b->red)) return 0;
    return 1;
}

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
