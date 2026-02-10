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
 * @file sonar_constants.h
 * @brief Sonar timer channel assignment constants.
 *
 * Defines the timer channels associated with each ultrasonic sonar sensor
 * (left, front, right) used for obstacle detection on the rover.
 */

#ifndef INC_CONSTANTS_SONAR_CONSTANTS_H_
#define INC_CONSTANTS_SONAR_CONSTANTS_H_

/** @brief Timer channel for the left sonar sensor. */
#define SONAR_LEFT_CHANNEL            	TIM_CHANNEL_3

/** @brief Timer channel for the front sonar sensor. */
#define SONAR_FRONT_CHANNEL 			TIM_CHANNEL_2

/** @brief Timer channel for the right sonar sensor. */
#define SONAR_RIGHT_CHANNEL 			TIM_CHANNEL_4

#endif /* INC_CONSTANTS_SONAR_CONSTANTS_H_ */
