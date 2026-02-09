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
 * @file motor_control.c
 * @brief Driver implementation for motor control logic.
 */

#include "motor_control.h"
#include <math.h>  // roundf


/**
 * @brief Generic linear mapping function (Arduino style 'map').
 *
 * Maps the value x from range [in_min, in_max] to range [out_min, out_max].
 * Formula: out = out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min)
 *
 * @param x Input value.
 * @param in_min Minimum value of input range.
 * @param in_max Maximum value of input range.
 * @param out_min Minimum value of output range.
 * @param out_max Maximum value of output range.
 * @return Mapped value.
 */
static inline float map_linear(float x, float in_min, float in_max, float out_min, float out_max)
{
  return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

/**
 * @brief Converts voltage to duty cycle percentage based on motor configuration.
 * @param m Pointer to MotorControl structure.
 * @param volt Voltage to convert.
 * @return Duty cycle percentage.
 */
static inline float volt_to_duty_percent(const MotorControl *m, float volt)
{
  // 1. Normalizza volt in un valore "grezzo" percentuale (0-100 basato su 12V)
  // Nota: Questo passaggio dipende dalla tua logica specifica dove 12V = 100%
  float duty_raw = (volt * 100.0f) / 12.0f;

  // 2. Mappa il range di input (es. -100 a +100) al range di output configurato (es. 56.8 a 94.6)
  return map_linear(duty_raw, m->in_min, m->in_max, m->out_min, m->out_max);
}

/**
 * @brief Converts duty cycle percentage to pulse width (CCR value).
 * @param m Pointer to MotorControl structure.
 * @param duty_percent Duty cycle percentage.
 * @return Pulse width value for CCR.
 */
static inline int duty_percent_to_pulse(const MotorControl *m, float duty_percent)
{
  float pulse_f = (duty_percent / 100.0f) * (float)m->arr_pwm_plus_one;
  return (int)roundf(pulse_f);
}

/**
 * @brief Initializes the Motor Control structure.
 * @param mc Pointer to the MotorControl structure.
 * @param htim_pwm PWM timer handle.
 * @param pwm_channel PWM channel.
 * @param Ts Sampling time.
 * @param min_volt Minimum voltage.
 * @param max_volt Maximum voltage.
 * @param in_min Input range minimum (for map).
 * @param in_max Input range maximum (for map).
 * @param out_min Output range minimum (for map).
 * @param out_max Output range maximum (for map).
 * @param dc_gain Motor DC gain.
 * @param default_regulator Default PID regulator.
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
)
{
  mc->htim_pwm = htim_pwm;
  mc->pwm_channel = pwm_channel;
  mc->Ts = Ts;

  mc->min_volt = min_volt;
  mc->max_volt = max_volt;
  mc->in_min = in_min;
  mc->in_max = in_max;
  mc->out_min = out_min;
  mc->out_max = out_max;
  
  mc->dc_gain = dc_gain; 
  
  mc->current_regulator = default_regulator;

  mc->reference_rpm = 0.0f;

  mc->arr_pwm_plus_one = (uint64_t)__HAL_TIM_GET_AUTORELOAD(htim_pwm) + 1ULL;

  mc->last_u = 0.0f;
  mc->last_pulse = 0;
}

/**
 * @brief Sets the reference RPM for the motor.
 * @param mc Pointer to the MotorControl structure.
 * @param ref_rpm Reference Speed in RPM.
 */
void MotorControl_SetReferenceRPM(MotorControl *mc, float ref_rpm)
{
  mc->reference_rpm = ref_rpm;
}

/**
 * @brief Switches the active PID regulator.
 * @param mc Pointer to the MotorControl structure.
 * @param reg Pointer to the new PIDController.
 */
void MotorControl_SetRegulator(MotorControl *mc, PIDController *reg)
{
    if (reg != NULL)
    {
    	PID_Change_Context(reg, mc->current_regulator);
        mc->current_regulator = reg;
    }
}

/**
 * @brief Computes the control signal (Voltage) based on current speed.
 * @param mc Pointer to the MotorControl structure.
 * @param speed_rpm Current motor speed in RPM.
 * @return Control signal (Voltage).
 */
float MotorControl_ComputeU(MotorControl *mc, float speed_rpm)
{
  float e = mc->reference_rpm - speed_rpm;

  float u_sat = PID_Compute(mc->current_regulator, e, mc->min_volt, mc->max_volt);

  mc->last_u = u_sat;

  return u_sat;
}

/**
 * @brief Actuates the motor with the given voltage.
 * @param mc Pointer to the MotorControl structure.
 * @param u_volt Control voltage.
 * @return The PWM pulse value applied.
 */
int MotorControl_Actuate(MotorControl *mc, float u_volt)
{
  float duty = volt_to_duty_percent(mc, u_volt);
  int pulse = duty_percent_to_pulse(mc, duty);

  // (opzionale ma utile) clamp CCR in [0, ARR]
  if (pulse < 0) pulse = 0;
  if ((uint64_t)pulse > (mc->arr_pwm_plus_one - 1ULL)) pulse = (int)(mc->arr_pwm_plus_one - 1ULL);

  __HAL_TIM_SET_COMPARE(mc->htim_pwm, mc->pwm_channel, (uint32_t)pulse);

  mc->last_pulse = pulse;
  return pulse;
}

/**
 * @brief Updates the motor control loop.
 * @param mc Pointer to the MotorControl structure.
 * @param speed_rpm Current speed in RPM.
 * @return The PWM pulse value applied.
 */
int MotorControl_ClosedLoop(MotorControl *mc, float speed_rpm)
{
  float u = MotorControl_ComputeU(mc, speed_rpm);
  return MotorControl_Actuate(mc, u);
}

/**
 * @brief Provides open-loop actuation based on reference RPM and DC gain.
 * @param mc Pointer to the MotorControl structure.
 */
void MotorControl_OpenLoopActuate(MotorControl *mc){
    // Usa il guadagno specifico del motore salvato nella struct
    // u_volt = ref_rpm / k_gain
    if (mc->dc_gain > 0.001f) { // Evita divisione per zero
        float u_volt = mc->reference_rpm / mc->dc_gain;
        MotorControl_Actuate(mc, u_volt);
    } else {
        MotorControl_Actuate(mc, 0.0f);
    }
}

