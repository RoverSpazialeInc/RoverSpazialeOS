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
 * @file freeRTOS_functions.h
 * @brief FreeRTOS task state transition function declarations.
 *
 * Declares stub functions that trigger transitions to degraded,
 * emergency, and faulty operating modes within the FreeRTOS task model.
 */

#ifndef INC_STUB_FREE_RTOS_FUNCTIONS_H_
#define INC_STUB_FREE_RTOS_FUNCTIONS_H_

/**
 * @brief Trigger a transition to degraded operating mode.
 */
void enterDegraded();

/**
 * @brief Trigger a transition to emergency operating mode.
 */
void enterEmergency();

/**
 * @brief Trigger a transition to faulty operating mode.
 */
void enterFaulty();

#endif /* INC_STUB_FREE_RTOS_FUNCTIONS_H_ */
