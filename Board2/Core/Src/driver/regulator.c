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
 * @file regulator.c
 * @brief Implementation of PID controller/regulator.
 */

#include "regulator.h"

/**
 * @brief Initializes the PID Controller.
 * @param pid Pointer to the PIDController structure.
 * @param k_err Error gain.
 * @param k_last_err Last Error gain.
 */
void PID_Init(PIDController *pid, float k_err, float k_last_err)
{
    pid->k_err = k_err;
    pid->k_last_err = k_last_err;
    PID_Reset(pid);
}

/**
 * @brief Resets the internal state of the PID Controller.
 * @param pid Pointer to the PIDController structure.
 */
void PID_Reset(PIDController *pid)
{
    pid->last_error = 0.0f;
    pid->z = 0.0f;
}

/**
 * @brief Changes the internal context of a PID Controller to match another.
 * @param pid_1 Pointer to the PIDController to be updated.
 * @param pid_2 Pointer to the PIDController whose context will be copied.
 */
void PID_Change_Context(PIDController *pid_1, PIDController *pid_2)
{
	pid_1->last_error = pid_2->last_error;
	pid_1->z = pid_2->z;
}

/**
 * @brief Computes the control output.
 * @param pid Pointer to the PIDController structure.
 * @param error Current error (reference - measure).
 * @param min_sat Minimum saturation limit.
 * @param max_sat Maximum saturation limit.
 * @return Saturated control output.
 */
float PID_Compute(PIDController *pid, float error, float min_sat, float max_sat)
{
  // Control law: q = k_err * e + k_last_err * e_prev
  float q = pid->k_err * error + pid->k_last_err * pid->last_error;
  
  // Update: u = q + z_prev
  float u = q + pid->z;

  // Saturation
  float sat = u;
  if (sat > max_sat)
  {
      sat = max_sat;
  }
  else if (sat < min_sat)
  {
      sat = min_sat;
  }

  // Update state (anti-windup by using saturated value)
  pid->z = sat;
  pid->last_error = error;
  
  return sat;
}
