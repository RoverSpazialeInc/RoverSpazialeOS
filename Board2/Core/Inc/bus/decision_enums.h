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
 * @file decision_enums.h
 * @brief Enumeration types used by the decision subsystem.
 *
 * Defines enumerations for actuator selection, rover status, user actions,
 * rover actions, safety actions, and LED states.
 */

#ifndef INC_BUS_DECISION_ENUMS_H_
#define INC_BUS_DECISION_ENUMS_H_

/**
 * @brief Describes which board/actuator is active.
 */
typedef enum {
    BOARD1 = 0, /**< Board 1 is active */
    BOARD2 = 1  /**< Board 2 is active */
} ENUM_Actuator;

/**
 * @brief Rover status enumeration.
 */
typedef enum {
    NORMAL = 0,               /**< No FAULT, no ERROR */

    ERROR_B1,                 /**< B1 in ERROR, B2 OK */
    ERROR_B2,                 /**< B2 in ERROR, B1 OK */
    ERROR_BOTH,               /**< Both B1 and B2 in ERROR */

    FAULTY_B1_DEGRADED_B2,    /**< B1 FAULT -> rover faulty, B2 degraded/limited */
    FAULTY_B2_DEGRADED_B1,    /**< B2 FAULT -> rover faulty, B1 degraded/limited */

    EMERGENCY                 /**< B1 FAULT, B2 FAULT */
} ENUM_StatusRover;

/**
 * @brief Action requested by the user.
 */
typedef enum {
    UA_NONE = 0,           /**< No action */
    UA_FORWARD = 1,        /**< Move forward */
    UA_ROTATE_LEFT = 2,    /**< Rotate left */
    UA_ROTATE_RIGHT = 3,   /**< Rotate right */
    UA_BACKWARD = 4,       /**< Move backward */
    UA_BRAKING_HARD = 5,   /**< Hard braking */
    UA_BRAKING_SMOOTH = 6  /**< Smooth braking */
} ENUM_UserAction;

/**
 * @brief Action performed by the rover.
 */
typedef enum {
    RA_IDLE = 0,              /**< Idle */
    RA_FORWARD = 1,           /**< Moving forward */
    RA_ROTATE_LEFT = 2,       /**< Rotating left */
    RA_ROTATE_RIGHT = 3,      /**< Rotating right */
    RA_BRAKING_SMOOTH = 4,    /**< Smooth braking */
    RA_BRAKING_MODERATE = 5,  /**< Moderate braking */
    RA_BRAKING_HARD = 6       /**< Hard braking */
} ENUM_RoverAction;

/**
 * @brief Safety action enumeration.
 */
typedef enum {
    SA_NONE = 0,           /**< No safety action */
    SA_SWERVE_LEFT = 1,    /**< Swerve left */
    SA_SWERVE_RIGHT = 2,   /**< Swerve right */
    SA_BRAKING_HARD = 3,   /**< Hard braking */
    SA_BRAKING_SMOOTH = 4  /**< Smooth braking */
} ENUM_SafeAction;

/**
 * @brief Red LED status enumeration.
 */
typedef enum {
    RED_OFF = 0,      /**< Red LED off */
    RED_BLINKING = 1, /**< Red LED blinking */
    RED_ON = 2        /**< Red LED on */
} ENUM_StatusRedLed;

/**
 * @brief White LED status enumeration.
 */
typedef enum {
    WHITE_OFF = 0, /**< White LED off */
    WHITE_ON = 1   /**< White LED on */
} ENUM_StatusWhiteLed;

#endif /* INC_BUS_DECISION_ENUMS_H_ */
