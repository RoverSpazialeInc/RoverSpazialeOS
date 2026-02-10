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
 * @file motor_constants.h
 * @brief Definition of constants, macros, and operating modes for the motor control system.
 *
 * This file contains constants and macros used for controller management,
 * speed regulation, duty cycle configuration, and saturation limits.
 */
#ifndef INC_CONSTANTS_MOTOR_CONSTANTS_H_
#define INC_CONSTANTS_MOTOR_CONSTANTS_H_

/* -------------------------------------------------------------------------- */
/*                               TUNING OPTIONS                               */
/* -------------------------------------------------------------------------- */

/** @brief Sampling rate (Hz). */
static const float SAMPLING_RATE = 50.0f;


/* -------------------------------------------------------------------------- */
/*                               NON-TUNING AREA                              */
/* -------------------------------------------------------------------------- */

/** @brief Total encoder tick count per motor revolution, accounting for gear ratio and signals. */
static const float COUNTS = (51.0f * 12.0f * 2.0f * 2.0f);  // 2448

/** @brief Sampling period (s). */
static const float TS = 1.0f / SAMPLING_RATE;

/** @brief Maximum allowed velocity (rpm). */
static const float MAX_VELOCITY = 200.0f;

/** @brief Maximum expected ticks within one sampling period. */
static const float MAX_TICKS = (1.0f / SAMPLING_RATE) *
                               ((MAX_VELOCITY / 60.0f) * COUNTS);


/* -------------------------------------------------------------------------- */
/*                             DUTY CYCLE LIMITS                              */
/* -------------------------------------------------------------------------- */

/** @brief Minimum normalized input value. */
static const float IN_MIN = -100.0f;
/** @brief Maximum normalized input value. */
static const float IN_MAX = 100.0f;

/** @brief Minimum duty cycle converted to equivalent voltage. */
static const float OUT_MIN = 56.8f;
/** @brief Maximum duty cycle converted to equivalent voltage. */
static const float OUT_MAX = 94.6f;


/* -------------------------------------------------------------------------- */
/*                                 SATURATION                                 */
/* -------------------------------------------------------------------------- */

/** @brief Maximum applicable voltage. */
static const float MAX_VOLT = 12.0f;

/** @brief Minimum applicable voltage. */
static const float MIN_VOLT = -12.0f;

/* -------------------------------------------------------------------------- */
/*                            OPEN LOOP DC GAINS                              */
/* -------------------------------------------------------------------------- */

/** @brief Static gain (RPM/V) - Motor 1 (Front Left). */
static const float DC_GAIN_MOT1 = 14.480f;

/** @brief Static gain (RPM/V) - Motor 2 (Front Right). */
static const float DC_GAIN_MOT2 = 14.200f;

/** @brief Static gain (RPM/V) - Motor 3 (Rear Right). */
static const float DC_GAIN_MOT3 = 14.210f;

/** @brief Static gain (RPM/V) - Motor 4 (Rear Left). */
static const float DC_GAIN_MOT4 = 14.510f;


/* -------------------------------------------------------------------------- */
/*                    MOTOR CONTROLLER GAINS (PER-MOTOR)                     */
/* -------------------------------------------------------------------------- */

/**
 * @defgroup fast_gains Fast Mode Controller Gains
 * @brief PID error and last-error gains for fast operating mode.
 * @{
 */

/* --------------------------- FAST MODE GAINS ------------------------------ */

/** @brief Front Left (Motor 1) - Fast mode current error gain. */
#define FAST_MOT1_K_ERR        (0.053587f)
/** @brief Front Left (Motor 1) - Fast mode previous error gain. */
#define FAST_MOT1_K_LAST_ERR  (-0.017211f)

/** @brief Front Right (Motor 2) - Fast mode current error gain. */
#define FAST_MOT2_K_ERR        (0.053133f)
/** @brief Front Right (Motor 2) - Fast mode previous error gain. */
#define FAST_MOT2_K_LAST_ERR  (-0.014643f)

/** @brief Rear Right (Motor 3) - Fast mode current error gain. */
#define FAST_MOT3_K_ERR        (0.062751f)
/** @brief Rear Right (Motor 3) - Fast mode previous error gain. */
#define FAST_MOT3_K_LAST_ERR  (-0.023033f)

/** @brief Rear Left (Motor 4) - Fast mode current error gain. */
#define FAST_MOT4_K_ERR        (0.05454171f)
/** @brief Rear Left (Motor 4) - Fast mode previous error gain. */
#define FAST_MOT4_K_LAST_ERR  (-0.01553629f)

/** @} */ /* end of fast_gains */

/**
 * @defgroup medium_gains Medium Mode Controller Gains
 * @brief PID error and last-error gains for medium operating mode.
 * @{
 */

/* --------------------------- MEDIUM MODE GAINS ------------------------------ */

/** @brief Front Left (Motor 1) - Medium mode current error gain. */
#define MEDIUM_MOT1_K_ERR        (0.00322340f)
/** @brief Front Left (Motor 1) - Medium mode previous error gain. */
#define MEDIUM_MOT1_K_LAST_ERR  (0.00322340f)

/** @brief Front Right (Motor 2) - Medium mode current error gain. */
#define MEDIUM_MOT2_K_ERR        (0.0032856f)
/** @brief Front Right (Motor 2) - Medium mode previous error gain. */
#define MEDIUM_MOT2_K_LAST_ERR  (0.0032856f)

/** @brief Rear Right (Motor 3) - Medium mode current error gain. */
#define MEDIUM_MOT3_K_ERR        (0.0032532f)
/** @brief Rear Right (Motor 3) - Medium mode previous error gain. */
#define MEDIUM_MOT3_K_LAST_ERR  (0.0032532f)

/** @brief Rear Left (Motor 4) - Medium mode current error gain. */
#define MEDIUM_MOT4_K_ERR        (0.0032173f)
/** @brief Rear Left (Motor 4) - Medium mode previous error gain. */
#define MEDIUM_MOT4_K_LAST_ERR  (0.0032173f)

/** @} */ /* end of medium_gains */

/**
 * @defgroup slow_gains Slow Mode Controller Gains
 * @brief PID error and last-error gains for slow operating mode.
 * @{
 */

/* --------------------------- SLOW MODE GAINS ------------------------------ */

/** @brief Front Left (Motor 1) - Slow mode current error gain. */
#define SLOW_MOT1_K_ERR        (0.0008642f)
/** @brief Front Left (Motor 1) - Slow mode previous error gain. */
#define SLOW_MOT1_K_LAST_ERR  (0.0008642f)

/** @brief Front Right (Motor 2) - Slow mode current error gain. */
#define SLOW_MOT2_K_ERR        (0.0008812f)
/** @brief Front Right (Motor 2) - Slow mode previous error gain. */
#define SLOW_MOT2_K_LAST_ERR  (0.0008812f)

/** @brief Rear Right (Motor 3) - Slow mode current error gain. */
#define SLOW_MOT3_K_ERR        (0.0008812f)
/** @brief Rear Right (Motor 3) - Slow mode previous error gain. */
#define SLOW_MOT3_K_LAST_ERR  (0.0008812f)

/** @brief Rear Left (Motor 4) - Slow mode current error gain. */
#define SLOW_MOT4_K_ERR        (0.0008642f)
/** @brief Rear Left (Motor 4) - Slow mode previous error gain. */
#define SLOW_MOT4_K_LAST_ERR  (0.0008642f)

/** @} */ /* end of slow_gains */

#endif /* INC_CONSTANTS_MOTOR_CONSTANTS_H_ */
