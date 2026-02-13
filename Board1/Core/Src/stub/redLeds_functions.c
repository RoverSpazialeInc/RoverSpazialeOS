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
 * @file redLeds_functions.c
 * @brief Red LED control stub functions for Board1.
 *
 * Provides on/off and periodic blinking control for the left and right
 * red LEDs using CMSIS-RTOS2 software timers.
 */

#include "redLeds_functions.h"

#include "cmsis_os2.h"          // for osTimerStart/Stop
#include "lights_init.h"        // #include "a4wd3_led.h"

extern osTimerId_t toggleLeftRedLedHandle;
extern osTimerId_t toggleRightRedLedHandle;

#define TIMER_SW_PERIOD 250U  /**< Software timer period in ms */

/* LEFT RED LED */

/**
 * @brief Turns off the left red LED.
 */
void leftRedLedOff(void) {
	A4WD3_Red_Off(&led_left);
}

/**
 * @brief Turns on the left red LED.
 */
void leftRedLedOn(void) {
	A4WD3_Red_On(&led_left);
}

/**
 * @brief Starts periodic blinking of the left red LED.
 *
 * Turns on the LED and starts the associated software timer.
 */
void startPeriodicLeftRedLed(void) {
	A4WD3_Red_On(&led_left);
	osTimerStart(toggleLeftRedLedHandle, TIMER_SW_PERIOD);

}

/**
 * @brief Stops periodic blinking of the left red LED.
 */
void stopPeriodicLeftRedLed(void) {
	osTimerStop(toggleLeftRedLedHandle);
}

/* RIGHT RED LED */

/**
 * @brief Turns off the right red LED.
 */
void rightRedLedOff(void) {
	A4WD3_Red_Off(&led_right);
}

/**
 * @brief Turns on the right red LED.
 */
void rightRedLedOn(void) {
	A4WD3_Red_On(&led_right);
}

/**
 * @brief Starts periodic blinking of the right red LED.
 *
 * Turns on the LED and starts the associated software timer.
 */
void startPeriodicRightRedLed(void) {
	A4WD3_Red_On(&led_right); // optional
	osTimerStart(toggleRightRedLedHandle, TIMER_SW_PERIOD);
}

/**
 * @brief Stops periodic blinking of the right red LED.
 */
void stopPeriodicRightRedLed(void) {
	osTimerStop(toggleRightRedLedHandle);
}
