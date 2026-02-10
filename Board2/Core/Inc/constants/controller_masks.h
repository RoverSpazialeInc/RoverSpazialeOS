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
 * @file controller_masks.h
 * @brief Bitmask definitions for remote-controller button combinations.
 *
 * Maps individual bits of the controller data word to specific rover
 * functions such as direction, braking, LED control and sonar enable/disable.
 */

#ifndef CONTROLLER_MASKS_H
#define CONTROLLER_MASKS_H

/** @brief Bitmask for the backward-drive button combination. */
#define BACKWARD_COMBO             256u

/** @brief Bitmask for the smooth braking command. */
#define BRAKING_SMOOTH_MASK         16u

/** @brief Bitmask for the hard braking command. */
#define BRAKING_HARD_MASK           32u

/** @brief Bitmask to toggle the left white LED. */
#define WHITE_LEFT_LED_MASK         64u

/** @brief Bitmask to toggle the right white LED. */
#define WHITE_RIGHT_LED_MASK       128u

/** @brief Bitmask to disable the left sonar sensor. */
#define DISABLE_LEFT_SONAR           4u

/** @brief Bitmask to disable the front sonar sensor. */
#define DISABLE_FRONT_SONAR          8u

/** @brief Bitmask to disable the right sonar sensor. */
#define DISABLE_RIGHT_SONAR          2u

#endif /* CONTROLLER_MASKS_H */
