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
 * @brief Constants, macros and operating-mode parameters for the motor control system.
 *
 * This file contains constants and macros used for regulator management,
 * velocity conversion, duty-cycle mapping and saturation limits, as well as
 * per-motor controller gains for every speed mode (fast, medium, slow).
 */
#ifndef INC_CONSTANTS_MOTOR_CONSTANTS_H_
#define INC_CONSTANTS_MOTOR_CONSTANTS_H_

/* -------------------------------------------------------------------------- */
/*                               TUNING OPTIONS                               */
/* -------------------------------------------------------------------------- */

/** @brief Sampling rate in Hz. */
static const float SAMPLING_RATE = 50.0f;


/* -------------------------------------------------------------------------- */
/*                               NON-TUNING AREA                              */
/* -------------------------------------------------------------------------- */

/** @brief Total encoder tick count per motor revolution (includes gear ratio and signal edges). */
static const float COUNTS = (51.0f * 12.0f * 2.0f * 2.0f);  /* 2448 */

/** @brief Sampling period in seconds. */
static const float TS = 1.0f / SAMPLING_RATE;

/** @brief Maximum allowed velocity (rpm). */
static const float MAX_VELOCITY = 200.0f;

/** @brief Maximum expected ticks within one sampling period. */
static const float MAX_TICKS = (1.0f / SAMPLING_RATE) *
                               ((MAX_VELOCITY / 60.0f) * COUNTS);


/* -------------------------------------------------------------------------- */
/*                             DUTY CYCLE LIMITS                              */
/* -------------------------------------------------------------------------- */

/** @brief Minimum normalised input value. */
static const float IN_MIN = -100.0f;
/** @brief Maximum normalised input value. */
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

/** @brief DC gain (RPM/V) – Motor 1 (Front Left). */
static const float DC_GAIN_MOT1 = 14.480f;

/** @brief DC gain (RPM/V) – Motor 2 (Front Right). */
static const float DC_GAIN_MOT2 = 14.200f;

/** @brief DC gain (RPM/V) – Motor 3 (Rear Right). */
static const float DC_GAIN_MOT3 = 14.210f;

/** @brief DC gain (RPM/V) – Motor 4 (Rear Left). */
static const float DC_GAIN_MOT4 = 14.510f;




/* -------------------------------------------------------------------------- */
/*                    MOTOR CONTROLLER GAINS (PER-MOTOR)                     */
/* -------------------------------------------------------------------------- */


/* --------------------------- FAST MODE GAINS ------------------------------ */

/** @name Fast Mode – Motor 1 (Front Left)
 *  @{ */
#define FAST_MOT1_K_ERR        (0.053587f)   /**< @brief Proportional error gain. */
#define FAST_MOT1_K_LAST_ERR  (-0.017211f)   /**< @brief Previous-error gain. */
/** @} */

/** @name Fast Mode – Motor 2 (Front Right)
 *  @{ */
#define FAST_MOT2_K_ERR        (0.053133f)   /**< @brief Proportional error gain. */
#define FAST_MOT2_K_LAST_ERR  (-0.014643f)   /**< @brief Previous-error gain. */
/** @} */

/** @name Fast Mode – Motor 3 (Rear Right)
 *  @{ */
#define FAST_MOT3_K_ERR        (0.062751f)   /**< @brief Proportional error gain. */
#define FAST_MOT3_K_LAST_ERR  (-0.023033f)   /**< @brief Previous-error gain. */
/** @} */

/** @name Fast Mode – Motor 4 (Rear Left)
 *  @{ */
#define FAST_MOT4_K_ERR        (0.05454171f) /**< @brief Proportional error gain. */
#define FAST_MOT4_K_LAST_ERR  (-0.01553629f) /**< @brief Previous-error gain. */
/** @} */


/* --------------------------- MEDIUM MODE GAINS ------------------------------ */

/** @name Medium Mode – Motor 1 (Front Left)
 *  @{ */
#define MEDIUM_MOT1_K_ERR        (0.00322340f) /**< @brief Proportional error gain. */
#define MEDIUM_MOT1_K_LAST_ERR  (0.00322340f)  /**< @brief Previous-error gain. */
/** @} */

/** @name Medium Mode – Motor 2 (Front Right)
 *  @{ */
#define MEDIUM_MOT2_K_ERR        (0.0032856f)  /**< @brief Proportional error gain. */
#define MEDIUM_MOT2_K_LAST_ERR  (0.0032856f)   /**< @brief Previous-error gain. */
/** @} */

/** @name Medium Mode – Motor 3 (Rear Right)
 *  @{ */
#define MEDIUM_MOT3_K_ERR        (0.0032532f)  /**< @brief Proportional error gain. */
#define MEDIUM_MOT3_K_LAST_ERR  (0.0032532f)   /**< @brief Previous-error gain. */
/** @} */

/** @name Medium Mode – Motor 4 (Rear Left)
 *  @{ */
#define MEDIUM_MOT4_K_ERR        (0.0032173f)  /**< @brief Proportional error gain. */
#define MEDIUM_MOT4_K_LAST_ERR  (0.0032173f)   /**< @brief Previous-error gain. */
/** @} */


/* --------------------------- SLOW MODE GAINS ------------------------------ */

/** @name Slow Mode – Motor 1 (Front Left)
 *  @{ */
#define SLOW_MOT1_K_ERR        (0.0008642f) /**< @brief Proportional error gain. */
#define SLOW_MOT1_K_LAST_ERR  (0.0008642f)  /**< @brief Previous-error gain. */
/** @} */

/** @name Slow Mode – Motor 2 (Front Right)
 *  @{ */
#define SLOW_MOT2_K_ERR        (0.0008812f) /**< @brief Proportional error gain. */
#define SLOW_MOT2_K_LAST_ERR  (0.0008812f)  /**< @brief Previous-error gain. */
/** @} */

/** @name Slow Mode – Motor 3 (Rear Right)
 *  @{ */
#define SLOW_MOT3_K_ERR        (0.0008812f) /**< @brief Proportional error gain. */
#define SLOW_MOT3_K_LAST_ERR  (0.0008812f)  /**< @brief Previous-error gain. */
/** @} */

/** @name Slow Mode – Motor 4 (Rear Left)
 *  @{ */
#define SLOW_MOT4_K_ERR        (0.0008642f) /**< @brief Proportional error gain. */
#define SLOW_MOT4_K_LAST_ERR  (0.0008642f)  /**< @brief Previous-error gain. */
/** @} */


#endif /* INC_CONSTANTS_MOTOR_CONSTANTS_H_ */
