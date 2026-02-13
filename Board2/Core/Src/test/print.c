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
 * @file print.c
 * @brief Implementation of serial printing utilities and debug helpers.
 */

#include "print.h"

/* -------------------------------------------------- */
/* Current UART                                       */
/* -------------------------------------------------- */
static UART_HandleTypeDef *current_printer;

/**
 * @brief Sets the UART handler for the printer.
 * @param huart Pointer to the UART handle.
 */
void setPrinterHandler(UART_HandleTypeDef *huart)
{
    if (huart != NULL) {
        current_printer = huart;
    }
}

/**
 * @brief Gets the current UART handler used by the printer.
 * @return Pointer to the UART handle.
 */
UART_HandleTypeDef* getPrinterHandler(void) {
    return current_printer; // Or the name of the static variable used in setPrinter
}

/**
 * @brief Internal utility: transmits a ready-made string.
 * @param s String to transmit.
 */
static void prv_tx_str(const char *s)
{
    if (s == NULL) return;
    if (current_printer == NULL) return;

    HAL_UART_Transmit(current_printer, (uint8_t*)s, (uint16_t)strlen(s), HAL_MAX_DELAY);
}

/**
 * @brief Internal utility: transmits a raw buffer.
 * @param buf Pointer to the buffer.
 * @param len Length of the buffer.
 */
static void prv_tx_buf(const uint8_t *buf, uint32_t len)
{
    if (buf == NULL || len == 0) return;
    if (current_printer == NULL) return;

    HAL_UART_Transmit(current_printer, (uint8_t*)buf, (uint16_t)len, HAL_MAX_DELAY);
}

/* -------------------------------------------------- */
/* Base / low-level                                   */
/* -------------------------------------------------- */

/**
 * @brief Alias for printing a string over UART.
 * @param msg Message string.
 */
void uartPrint(const char *msg)
{
    prv_tx_str(msg);
}

/**
 * @brief Implementation of message printing.
 * @param pData Message string.
 */
void printMsg_impl(const char *pData)
{
    prv_tx_str(pData);
}

/**
 * @brief Clears the screen using ANSI escape codes.
 */
void clearScreen(void)
{
    printMsg(CLRSCR);
}

/* -------------------------------------------------- */
/* Primitives (testable prints)                        */
/* -------------------------------------------------- */

/**
 * @brief Prints a signed integer.
 * @param v Integer value.
 */
void printInt(int32_t v)
{
    char msg[24];
    snprintf(msg, sizeof(msg), "%ld", (long)v);
    prv_tx_str(msg);
}

/**
 * @brief Prints a float value with a specified number of decimals.
 * @param v Float value.
 * @param decimals Number of decimal digits.
 */
void printFloat(float v, uint8_t decimals)
{
    /* decimals clamp (avoid absurd formats) */
    if (decimals > 6) decimals = 6;

    char fmt[8];
    char msg[32];

    /* fmt type: "%.2f" */
    snprintf(fmt, sizeof(fmt), "%%.%uf", (unsigned)decimals);
    snprintf(msg, sizeof(msg), fmt, (double)v);

    prv_tx_str(msg);
}

/* -------------------------------------------------- */
/* Debug frame sizes                                  */
/* -------------------------------------------------- */

/**
 * @brief Prints the sizes of various data frames/structures.
 */
void UART_PrintFrameSizes(void)
{
    char buf[64];
    int len;

#define PRINT_SIZE(name, value)                                  \
    do {                                                         \
        len = snprintf(buf, sizeof(buf),                         \
                       "%-30s : %lu\r\n",                        \
                       name, (unsigned long)(value));            \
        if (len > 0) {                                           \
            prv_tx_buf((const uint8_t*)buf, (uint32_t)len);       \
        }                                                        \
    } while (0)

    /* --- Sensors --- */
    PRINT_SIZE("SPEED_FRAME_SIZE", SPEED_FRAME_SIZE);
    PRINT_SIZE("TEMPERATURE_FRAME_SIZE", TEMPERATURE_FRAME_SIZE);
    PRINT_SIZE("BATTERY_LEVEL_FRAME_SIZE", BATTERY_LEVEL_FRAME_SIZE);
    PRINT_SIZE("SONAR_FRAME_SIZE", SONAR_FRAME_SIZE);
    PRINT_SIZE("GYROSCOPE_FRAME_SIZE", GYROSCOPE_FRAME_SIZE);
    PRINT_SIZE("REMOTE_CONTROLLER_FRAME_SIZE", REMOTE_CONTROLLER_FRAME_SIZE);

    /* --- States --- */
    PRINT_SIZE("LOCAL_STATE_B1_FRAME_SIZE", LOCAL_STATE_B1_FRAME_SIZE);
    PRINT_SIZE("LOCAL_STATE_B2_FRAME_SIZE", LOCAL_STATE_B2_FRAME_SIZE);
    PRINT_SIZE("GLOBAL_STATE_FRAME_SIZE", GLOBAL_STATE_FRAME_SIZE);

    /* --- Decision / Control --- */
    PRINT_SIZE("SET_POINT_FRAME_SIZE", SET_POINT_FRAME_SIZE);
    PRINT_SIZE("DECISION_FRAME_SIZE", DECISION_FRAME_SIZE);

#undef PRINT_SIZE
}

/* -------------------------------------------------- */
/* Debug print full buffer in HEX                     */
/* -------------------------------------------------- */

/**
 * @brief Prints a buffer content in hexadecimal format.
 * @param tag String tag to identify the buffer.
 * @param buf Pointer to the buffer.
 * @param len Length of the buffer.
 */
void uartPrintBuffHex(const char *tag, const uint8_t *buf, uint32_t len)
{
    char msg[80];

    snprintf(msg, sizeof(msg), "%s (%lu): ", tag, (unsigned long)len);
    prv_tx_str(msg);

    for (uint32_t i = 0; i < len; i++) {
        snprintf(msg, sizeof(msg), "%02X ", buf[i]);
        prv_tx_str(msg);
    }
    prv_tx_str("\r\n");
}

/* -------------------------------------------------- */
/* Complex structures (built with elementary ones)     */
/* -------------------------------------------------- */

/**
 * @brief Prints a section header.
 * @param title Title of the section.
 */
void printHeader(const char *title)
{
    printMsg(title);
    printMsg("\r\n");
}

/**
 * @brief Prints a label for a value.
 * @param label The label string.
 */
void printLabel(const char *label)
{
    printMsg("  ");
    printMsg(label);
    printMsg(": ");
}

/**
 * @brief Prints a newline.
 */
void printNewLine(void)
{
    printMsg("\r\n");
}

/* ---- LocalStateB1 ---- */

/**
 * @brief Prints motor speed values.
 * @param sp Pointer to the speed structure.
 */
void printMotorSpeeds(const BUS_Speed *sp)
{
    char msg[128];
    snprintf(msg, sizeof(msg),
             "  Speed: %.2f %.2f %.2f %.2f\r\n",
             sp->motor1, sp->motor2, sp->motor3, sp->motor4);
    uartPrint(msg);
}

/**
 * @brief Prints temperature value.
 * @param t Temperature value.
 */
void printTemperature(float t)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "  Temperature: %.2f C\r\n", (double)t);
    uartPrint(msg);
}

/**
 * @brief Prints battery level.
 * @param b Battery level.
 */
void printBattery(uint8_t b)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "  Battery: %u %%\r\n", (unsigned int)b);
    uartPrint(msg);
}

void printSensorReadings(uint8_t readings)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "  SensorReadings: 0x%02X\r\n", readings);
    uartPrint(msg);
}

/**
 * @brief Prints deadline occurred flag.
 * @param deadlineOccurred Non-zero if a deadline was missed.
 */
void printDeadlineOccurred(uint8_t deadlineOccurred)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "  DeadlineOccurred: %u\r\n", (unsigned int)deadlineOccurred);
    uartPrint(msg);
}


void printLocalStateB1(const BUS_LocalStateB1 *s)
{
    if (s == NULL) return;

    printHeader("LocalStateB1");
    printMotorSpeeds(&s->speed);
    printTemperature(s->temperature);
    printBattery(s->batteryLevel);
    printSensorReadings(s->sensorReadings);
    printDeadlineOccurred(s->deadlineOccurred);
}

/* ---- LocalStateB2 ---- */

/**
 * @brief Prints sonar readings.
 * @param sn Pointer to sonar structure.
 */
void printSonar(const BUS_Sonar *sn)
{
    char msg[96];
    snprintf(msg, sizeof(msg), "  Sonar: L=%d F=%d R=%d\r\n",
             sn->left, sn->front, sn->right);
    uartPrint(msg);
}

/**
 * @brief Prints gyroscope value.
 * @param g Gyroscope value.
 */
void printGyroscope(uint16_t g)
{
    char msg[64];
    snprintf(msg, sizeof(msg), "  Gyroscope: %u\r\n", (unsigned int)g);
    uartPrint(msg);
}

/**
 * @brief Prints remote controller state.
 * @param rc Pointer to remote controller structure.
 */
void printRemoteController(const BUS_RemoteController *rc)
{
    char msg[128];
    snprintf(msg, sizeof(msg),
             "  RemoteController: x_lever=%d y_lever=%d buttons=%d\r\n",
             rc->x_lever, rc->y_lever, rc->buttons);
    uartPrint(msg);
}

/**
 * @brief Prints the local state of Board 2.
 * @param s Pointer to LocalStateB2 structure.
 */
void printLocalStateB2(const BUS_LocalStateB2 *s)
{
    if (s == NULL) return;

    printHeader("LocalStateB2");
    printSonar(&s->sonar);
    printGyroscope(s->gyroscope);
    printRemoteController(&s->remoteController);
    printSensorReadings(s->sensorReadings);
    printDeadlineOccurred(s->deadlineOccurred);
}

/* ---- GlobalState ---- */

/**
 * @brief Prints the global state.
 * @param g Pointer to GlobalState structure.
 */
void printGlobalState(const BUS_GlobalState *g)
{
    if (g == NULL) return;

    printHeader("GlobalState");
    printLocalStateB1(&g->localStateB1);
    printLocalStateB2(&g->localStateB2);
}

/* ---- Decision ---- */

/**
 * @brief Prints a line with a label and an integer value (usually for enums).
 * @param label Label string.
 * @param v Integer value.
 */
void printEnumLine(const char *label, int v)
{
    printLabel(label);
    printInt(v);
    printNewLine();
}

/**
 * @brief Prints set point values.
 * @param sp Pointer to set point structure.
 */
void printSetPoint(const BUS_SetPoint *sp)
{
    char msg[96];
    snprintf(msg, sizeof(msg), "  setPoint(Left)=%.3f\r\n", (double)sp->leftAxis);
    uartPrint(msg);
    snprintf(msg, sizeof(msg), "  setPoint(Right)=%.3f\r\n", (double)sp->rightAxis);
    uartPrint(msg);
}

/**
 * @brief Gets the name of the White LED status.
 * @param v White LED status enum.
 * @return String representation of the status.
 */
static const char* getStatusWhiteLedName(ENUM_StatusWhiteLed v) {
    switch (v) {
        case WHITE_OFF: return "WHITE_OFF";
        case WHITE_ON: return "WHITE_ON";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Gets the name of the Red LED status.
 * @param v Red LED status enum.
 * @return String representation of the status.
 */
static const char* getStatusRedLedName(ENUM_StatusRedLed v) {
    switch (v) {
        case RED_OFF: return "RED_OFF";
        case RED_BLINKING: return "RED_BLINKING";
        case RED_ON: return "RED_ON";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Prints LED states.
 * @param leds Pointer to LED structure.
 */
void printLeds(const BUS_Leds *leds)
{
    char msg[256];
    snprintf(msg, sizeof(msg),
             "  Leds: White[L=%s R=%s] Red[L=%s R=%s]\r\n",
             getStatusWhiteLedName(leds->white.left),
             getStatusWhiteLedName(leds->white.right),
             getStatusRedLedName(leds->red.left),
             getStatusRedLedName(leds->red.right));
    uartPrint(msg);
}

/**
 * @brief Gets the name of the actuator.
 * @param v Actuator enum.
 * @return String representation of the actuator.
 */
static const char* getActuatorName(ENUM_Actuator v) {
    switch (v) {
        case BOARD1: return "BOARD1";
        case BOARD2: return "BOARD2";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Gets the name of the user action.
 * @param v User action enum.
 * @return String representation of the user action.
 */
static const char* getUserActionName(ENUM_UserAction v) {
    switch (v) {
        case UA_NONE: return "UA_NONE";
        case UA_FORWARD: return "UA_FORWARD";
        case UA_ROTATE_LEFT: return "UA_ROTATE_LEFT";
        case UA_ROTATE_RIGHT: return "UA_ROTATE_RIGHT";
        case UA_BACKWARD: return "UA_BACKWARD";
        case UA_BRAKING_HARD: return "UA_BRAKING_HARD";
        case UA_BRAKING_SMOOTH: return "UA_BRAKING_SMOOTH";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Gets the name of the rover action.
 * @param v Rover action enum.
 * @return String representation of the rover action.
 */
static const char* getRoverActionName(ENUM_RoverAction v) {
    switch (v) {
        case RA_IDLE: return "RA_IDLE";
        case RA_FORWARD: return "RA_FORWARD";
        case RA_ROTATE_LEFT: return "RA_ROTATE_LEFT";
        case RA_ROTATE_RIGHT: return "RA_ROTATE_RIGHT";
        case RA_BRAKING_HARD: return "RA_BRAKING_HARD";
        case RA_BRAKING_MODERATE: return "RA_BRAKING_MODERATE";
        case RA_BRAKING_SMOOTH: return "RA_BRAKING_SMOOTH";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Gets the name of the safe action.
 * @param v Safe action enum.
 * @return String representation of the safe action.
 */
static const char* getSafeActionName(ENUM_SafeAction v) {
    switch (v) {
        case SA_NONE: return "SA_NONE";
        case SA_SWERVE_LEFT: return "SA_SWERVE_LEFT";
        case SA_SWERVE_RIGHT: return "SA_SWERVE_RIGHT";
        case SA_BRAKING_HARD: return "SA_BRAKING_HARD";
        case SA_BRAKING_SMOOTH: return "SA_BRAKING_SMOOTH";
        default: return "UNKNOWN";
    }
}

static const char* getRoverStatusName(ENUM_StatusRover v) {
    switch (v) {
        case NORMAL: return "NORMAL";
        case ERROR_B1: return "ERROR_B1";
        case ERROR_B2: return "ERROR_B2";
        case ERROR_BOTH: return "ERROR_BOTH";
        case FAULTY_B1_DEGRADED_B2: return "FAULTY_B1_DEGRADED_B2";
        case FAULTY_B2_DEGRADED_B1: return "FAULTY_B2_DEGRADED_B1";
        case EMERGENCY: return "EMERGENCY";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Prints a line with a label and a string value.
 * @param label Label string.
 * @param v String value.
 */
static void printEnumLineStr(const char *label, const char *v)
{
    printLabel(label);
    uartPrint(v);
    printNewLine();
}

/**
 * @brief Prints the decision logic state.
 * @param d Pointer to Decision structure.
 */
void printDecision(const BUS_Decision *d)
{
    if (d == NULL) return;

    printHeader("Decision");

    printEnumLineStr("actuator",    getActuatorName(d->actuator));
    printEnumLineStr("roverState",  getRoverStatusName(d->roverState));
    printEnumLineStr("userAction",  getUserActionName(d->userAction));
    printEnumLineStr("roverAction", getRoverActionName(d->roverAction));
    printEnumLineStr("safeAction",  getSafeActionName(d->safeAction));

    printSetPoint(&d->setPoint);
    printLeds(&d->leds);
}
