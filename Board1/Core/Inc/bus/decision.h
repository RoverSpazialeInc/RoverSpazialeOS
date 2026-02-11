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
 * @file decision.h
 * @brief Data structures for the rover decision subsystem.
 *
 * Defines structures for setpoints, LED states, and the main decision
 * output produced by the control logic.
 */

#ifndef INC_BUS_DECISION_H_
#define INC_BUS_DECISION_H_

#include "decision_enums.h"

/**
 * @brief Setpoint for the left and right axes.
 */
typedef struct {
    float leftAxis;  /**< Left axis setpoint */
    float rightAxis; /**< Right axis setpoint */
} BUS_SetPoint;

/**
 * @brief Red LEDs status.
 */
typedef struct {
    ENUM_StatusRedLed left;  /**< Left red LED status */
    ENUM_StatusRedLed right; /**< Right red LED status */
} BUS_RedLeds;

/**
 * @brief White LEDs status.
 */
typedef struct {
    ENUM_StatusWhiteLed left;  /**< Left white LED status */
    ENUM_StatusWhiteLed right; /**< Right white LED status */
} BUS_WhiteLeds;

/**
 * @brief Overall LEDs status.
 */
typedef struct {
    BUS_WhiteLeds white; /**< White LEDs state */
    BUS_RedLeds   red;   /**< Red LEDs state */
} BUS_Leds;

/**
 * @brief Main decision structure.
 *
 * Contains the full decision output including actuator selection,
 * rover status, requested/performed/safety actions, setpoints, and LED states.
 */
typedef struct {
    ENUM_Actuator     actuator;    /**< Active actuator/board */
    ENUM_StatusRover  roverState;  /**< Current rover status */

    ENUM_UserAction   userAction;  /**< Action requested by the user */
    ENUM_RoverAction  roverAction; /**< Action performed by the rover */
    ENUM_SafeAction   safeAction;  /**< Safety action */

    BUS_SetPoint      setPoint;    /**< Motor setpoints */
    BUS_Leds          leds;        /**< LED outputs */
} BUS_Decision;

#endif /* INC_BUS_DECISION_H_ */
