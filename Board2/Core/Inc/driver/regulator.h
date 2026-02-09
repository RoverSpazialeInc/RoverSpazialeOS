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
 * @file regulator.h
 * @brief PID Controller driver header file.
 */

#ifndef INC_DRIVER_REGULATOR_H_
#define INC_DRIVER_REGULATOR_H_

/**
 * @brief PID Controller structure.
 */
typedef struct {
  /* Coefficients */
  float k_err;      /**< Error gain */
  float k_last_err; /**< Last Error gain */
  
  /* State */
  float last_error; /**< Last known error */
  float z;          /**< Memory (accumulated output / integral state) */
} PIDController;

/**
 * @brief Initialize the PID Controller.
 * @param pid Pointer to the PIDController structure.
 * @param k_err Error gain.
 * @param k_last_err Last Error gain.
 */
void PID_Init(PIDController *pid, float k_err, float k_last_err);

/**
 * @brief Reset the internal state of the PID Controller.
 * @param pid Pointer to the PIDController structure.
 */
void PID_Reset(PIDController *pid);

/**
 * @brief Compute the control output.
 * @param pid Pointer to the PIDController structure.
 * @param error Current error (reference - measure).
 * @param min_sat Minimum saturation limit.
 * @param max_sat Maximum saturation limit.
 * @return Saturated control output.
 */
float PID_Compute(PIDController *pid, float error, float min_sat, float max_sat);

/**
 * @brief Change the internal context of a PID Controller to match another.
 * @param pid_1 Pointer to the PIDController to be updated.
 * @param pid_2 Pointer to the PIDController whose context will be copied.
 */
void PID_Change_Context(PIDController *pid_1, PIDController *pid_2);

#endif /* INC_DRIVER_REGULATOR_H_ */
