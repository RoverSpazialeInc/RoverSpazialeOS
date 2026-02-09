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
 * @file motors_init.h
 * @brief Header file for motor initialization and configuration.
 */

#ifndef INC_DRIVER_INIT_MOTORS_INIT_H_
#define INC_DRIVER_INIT_MOTORS_INIT_H_

#include <stdint.h>

#include "motor_control.h"
#include "motor_constants.h"
#include "regulator.h"


/**
 * @brief Enum identifying each motor on the rover.
 */
typedef enum {
    MOTOR_FRONT_LEFT = 0, /**< Front Left Motor */
    MOTOR_FRONT_RIGHT,    /**< Front Right Motor */
    MOTOR_REAR_RIGHT,     /**< Rear Right Motor */
    MOTOR_REAR_LEFT,      /**< Rear Left Motor */
    N_MOTORS              /**< Number of motors */
} MotorId;

/** @brief Array of MotorControl structures */
extern MotorControl motors[N_MOTORS];

/** @brief Array of fast PID controllers */
extern PIDController pid_fast[N_MOTORS];

/** @brief Array of medium PID controllers */
extern PIDController pid_medium[N_MOTORS];

/** @brief Array of slow PID controllers */
extern PIDController pid_slow[N_MOTORS];


/**
 * @brief Initialize all motor control structures and PIDs.
 */
void Motors_InitAll(void);

/**
 * @brief Start PWM generation for all motors.
 */
void Motors_StartAllPwm(void);

/**
 * @brief Set the default CCR value for all motors.
 * @param ccr The Capture Compare Register value to set.
 */
void Motors_SetDefaultCcr(uint32_t ccr);

#endif /* INC_DRIVER_INIT_MOTORS_INIT_H_ */
