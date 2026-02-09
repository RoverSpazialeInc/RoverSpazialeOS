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
 * @file motor_control.h
 * @brief Header file for the Motor Control driver.
 */

#ifndef INC_DRIVER_MOTOR_CONTROL_H_
#define INC_DRIVER_MOTOR_CONTROL_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include "regulator.h"

/**
 * @brief Motor Control structure definition.
 */
typedef struct {
  /* --- PWM HW --- */
  TIM_HandleTypeDef *htim_pwm;  /**< Handle to the PWM Timer */
  uint64_t arr_pwm_plus_one;    /**< (ARR + 1) cached value for duty cycle calculation */
  uint32_t pwm_channel;         /**< TIM Channel used for PWM generation */

  /* --- Parametri --- */
  float Ts;                     /**< Control loop period [s] */

  /* --- Limiti e mapping Volt -> Duty --- */
  float min_volt;               /**< Minimum output voltage magnitude */
  float max_volt;               /**< Maximum output voltage magnitude */
  float in_min;                 /**< Input mapping range start */
  float in_max;                 /**< Input mapping range end */
  float out_min;                /**< Output mapping range start */
  float out_max;                /**< Output mapping range end */

  /* --- Parametri Open Loop --- */
  float dc_gain;                /**< Motor static gain (RPM/V) for open loop control */

  /* --- Regolatore --- */
  PIDController *current_regulator; /**< Pointer to the active PID controller instance */

  /* --- Stato controllore --- */
  float reference_rpm;          /**< Target speed reference in RPM */

  /* --- Debug opzionale --- */
  float last_u;                 /**< Last computed control signal (Voltage) */
  int last_pulse;               /**< Last applied PWM pulse value */
} MotorControl;

/**
 * @brief Initialize the MotorControl structure with hardware and control parameters.
 * 
 * @param mc Pointer to the MotorControl structure.
 * @param htim_pwm Pointer to the TIM handle for PWM.
 * @param pwm_channel TIM channel for PWM.
 * @param Ts Control sampling period in seconds.
 * @param min_volt Minimum voltage.
 * @param max_volt Maximum voltage.
 * @param in_min Input mapping minimum.
 * @param in_max Input mapping maximum.
 * @param out_min Output mapping minimum.
 * @param out_max Output mapping maximum.
 * @param dc_gain Motor static gain (DC gain).
 * @param default_regulator Pointer to the initial PID regulator.
 */
void MotorControl_Init(
  MotorControl *mc,
  TIM_HandleTypeDef *htim_pwm,
  uint32_t pwm_channel,
  float Ts,
  float min_volt, float max_volt,
  float in_min, float in_max, float out_min, float out_max,
  float dc_gain, 
  PIDController *default_regulator
);

/**
 * @brief Set the target reference speed in RPM.
 * @param mc Pointer to the MotorControl structure.
 * @param ref_rpm Desired speed in RPM.
 */
void MotorControl_SetReferenceRPM(MotorControl *mc, float ref_rpm);

/**
 * @brief Assign a new PID regulator to the motor controller.
 * @param mc Pointer to the MotorControl structure.
 * @param reg Pointer to the new PIDController.
 */
void MotorControl_SetRegulator(MotorControl *mc, PIDController *reg);

/**
 * @brief Compute the control signal (Voltage) based on the measured speed.
 * 
 * Delegates the calculation to the current PID regulator and saturates the result.
 * 
 * @param mc Pointer to the MotorControl structure.
 * @param speed_rpm Current measured speed in RPM.
 * @return float Calculated control output in Volts.
 */
float MotorControl_ComputeU(MotorControl *mc, float speed_rpm);

/**
 * @brief Apply the control signal (Voltage) to the motor via PWM.
 * 
 * Maps the voltage to a PWM pulse width and updates the CCR register.
 * 
 * @param mc Pointer to the MotorControl structure.
 * @param u_volt Control signal in Volts.
 * @return int The pulse value written to the CCR register.
 */
int MotorControl_Actuate(MotorControl *mc, float u_volt);

/**
 * @brief High-level update function: Compute and Actuate.
 * 
 * @param mc Pointer to the MotorControl structure.
 * @param speed_rpm Current measured speed in RPM.
 * @return int The pulse value written to the CCR register.
 */
int MotorControl_ClosedLoop(MotorControl *mc, float speed_rpm);

/**
 * @brief Drive the motor in Open Loop configurations using the DC gain.
 * 
 * Calculates voltage based on reference RPM and DC gain, then actuates.
 * 
 * @param mc Pointer to the MotorControl structure.
 */
void MotorControl_OpenLoopActuate(MotorControl *mc);

#endif /* INC_DRIVER_MOTOR_CONTROL_H_ */
