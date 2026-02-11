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
 * @file redLeds_functions.h
 * @brief Red LED control function declarations.
 *
 * Declares stub functions for turning the left and right red LEDs on/off
 * and for starting/stopping their periodic blinking modes.
 */

#ifndef INC_STUB_REDLEDSFUNCTIONS_H_
#define INC_STUB_REDLEDSFUNCTIONS_H_

/** @defgroup LeftRedLed Left Red LED Control
 *  @{
 */

/** @brief Turn off the left red LED. */
void leftRedLedOff(void);

/** @brief Turn on the left red LED. */
void leftRedLedOn(void);

/** @brief Start periodic blinking of the left red LED. */
void startPeriodicLeftRedLed(void);

/** @brief Stop periodic blinking of the left red LED. */
void stopPeriodicLeftRedLed(void);

/** @} */ /* end of LeftRedLed */

/** @defgroup RightRedLed Right Red LED Control
 *  @{
 */

/** @brief Turn off the right red LED. */
void rightRedLedOff(void);

/** @brief Turn on the right red LED. */
void rightRedLedOn(void);

/** @brief Start periodic blinking of the right red LED. */
void startPeriodicRightRedLed(void);

/** @brief Stop periodic blinking of the right red LED. */
void stopPeriodicRightRedLed(void);

/** @} */ /* end of RightRedLed */

#endif /* INC_STUB_REDLEDSFUNCTIONS_H_ */
