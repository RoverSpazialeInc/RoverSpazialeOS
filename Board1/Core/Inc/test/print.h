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
 * @file print.h
 * @brief Serial printing utilities and debug helper functions.
 *
 * This file provides functions for printing various data structures and
 * debugging information over UART. It includes helpers for primitive types,
 * specific bus structures (states, decision), and ANSI escape codes.
 */

#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "frame_size.h"  // usually included in serialize/deserialize
#include "decision.h"    // #include "enums.h"
#include "states.h"      // #include "sensors.h"

/** @brief ANSI Escape code to clear screen. */
#define CLRSCR "\033[2J\033[H"

/* -------------------------------------------------- */
/* Printer configuration                              */
/* -------------------------------------------------- */
#include "usart.h"

/**
 * @brief Sets the UART handler for the printer.
 * @param huart Pointer to the UART handle.
 */
void setPrinterHandler(UART_HandleTypeDef *huart);

/**
 * @brief Gets the current UART handler used by the printer.
 * @return Pointer to the UART handle.
 */
UART_HandleTypeDef* getPrinterHandler(void);

/* -------------------------------------------------- */
/* Base / low-level functions                         */
/* -------------------------------------------------- */

/**
 * @brief Clears the terminal screen using ANSI codes.
 */
void clearScreen(void);

/**
 * @brief Convenient alias to print a null-terminated string.
 * @param msg String to print.
 */
void uartPrint(const char *msg);

/* -------------------------------------------------- */
/* Primitives (testable prints)                       */
/* -------------------------------------------------- */

/**
 * @brief Implementation of message printing.
 * @param pData Message string to print.
 */
void printMsg_impl(const char *pData);

/**
 * @brief Prints a signed integer.
 * @param v Integer value.
 */
void printInt(int32_t v);

/**
 * @brief Prints a float value with specified decimal places.
 * @param v Float value.
 * @param decimals Number of decimal digits to print.
 */
void printFloat(float v, uint8_t decimals);

/** @brief Required macro: printMsg(...) */
#define printMsg(msg)   printMsg_impl((msg))

/* -------------------------------------------------- */
/* Debug functions                                    */
/* -------------------------------------------------- */

/**
 * @brief Prints the frame sizes of various structures.
 */
void UART_PrintFrameSizes(void);

/**
 * @brief Prints a buffer in hexadecimal format.
 * @param tag String tag for identifying the buffer.
 * @param buf Pointer to the data buffer.
 * @param len Length of the buffer.
 */
void uartPrintBuffHex(const char *tag, const uint8_t *buf, uint32_t len);

/* -------------------------------------------------- */
/* Elementary functions on structure fields/parts     */
/* -------------------------------------------------- */

/**
 * @brief Prints a header formatted with the given title.
 * @param title Title string.
 */
void printHeader(const char *title);

/**
 * @brief Prints a label string.
 * @param label Label string.
 */
void printLabel(const char *label);

/**
 * @brief Prints a new line character.
 */
void printNewLine(void);

/* Elementary used in LocalStateB1 */

/**
 * @brief Prints motor speeds.
 * @param sp Pointer to the speed structure.
 */
void printMotorSpeeds(const BUS_Speed *sp);

/**
 * @brief Prints temperature value.
 * @param t Temperature in Celsius.
 */
void printTemperature(float t);

/**
 * @brief Prints battery level.
 * @param b Battery level (percentage or voltage representation).
 */
void printBattery(uint8_t b);

/**
 * @brief Prints sensor readings.
 * @param readings Sensor readings bitmask.
 */
void printSensorReadings(uint8_t readings);

/**
 * @brief Prints deadline occurred flag.
 * @param deadlineOccurred Non-zero if a deadline was missed.
 */
void printDeadlineOccurred(uint8_t deadlineOccurred);

/* Elementary used in LocalStateB2 */

/**
 * @brief Prints sonar readings.
 * @param sn Pointer to the sonar structure.
 */
void printSonar(const BUS_Sonar *sn);

/**
 * @brief Prints gyroscope data.
 * @param g Gyroscope primitive value.
 */
void printGyroscope(uint16_t g);

/**
 * @brief Prints remote controller state.
 * @param rc Pointer to the remote controller structure.
 */
void printRemoteController(const BUS_RemoteController *rc);

/* Elementary used in Decision */

/**
 * @brief Prints an enumeration line.
 * @param label Label for the enum.
 * @param v Enum integer value.
 */
void printEnumLine(const char *label, int v);

/**
 * @brief Prints a setpoint.
 * @param sp Pointer to the setpoint structure.
 */
void printSetPoint(const BUS_SetPoint *sp);

/**
 * @brief Prints LEDs state.
 * @param leds Pointer to the LEDs structure.
 */
void printLeds(const BUS_Leds *leds);

/* -------------------------------------------------- */
/* Complex structures                                 */
/* -------------------------------------------------- */

/**
 * @brief Prints the local state of Board 1.
 * @param s Pointer to the LocalStateB1 structure.
 */
void printLocalStateB1(const BUS_LocalStateB1 *s);

/**
 * @brief Prints the local state of Board 2.
 * @param s Pointer to the LocalStateB2 structure.
 */
void printLocalStateB2(const BUS_LocalStateB2 *s);

/**
 * @brief Prints the global state.
 * @param g Pointer to the GlobalState structure.
 */
void printGlobalState(const BUS_GlobalState *g);

/**
 * @brief Prints the decision structure.
 * @param d Pointer to the Decision structure.
 */
void printDecision(const BUS_Decision *d);

#endif /* INC_PRINT_H_ */
