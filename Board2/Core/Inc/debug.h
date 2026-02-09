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
 * @file debug.h
 * @brief Debugging configuration macros.
 *
 * This file contains preprocessor definitions to control debugging features,
 * execution modes, and verbosity of various modules.
 */

/** @brief SEGGER Debugging build configuration */
#define SEGGER_BUILD 0

/**
 * @brief LED Debug Enable
 * 1: Enables debug LED
 * 0: Disables debug LED
 */
#define LED_DEBUG 1

/**
 * @brief Task Execution Mode
 * 1: Executes real code
 * 0: Simulates load with HAL_Delay
 */
#define REAL_TASK 1

/**
 * @brief Global Debug Print Enable
 * 1: Enables debug prints
 * 0: Disables debug prints
 */
#define PRINT_TASK 0

/**
 * @brief Enable ReadController Task
 * 1: ReadController Task is scheduled
 * 0: ReadController Task is not scheduled
 */
#define RUN_READ_CONTROLLER 1

/**
 * @brief Enable ReadGyroscope Task
 * 1: ReadGyroscope Task is scheduled
 * 0: ReadGyroscope Task is not scheduled
 */
#define RUN_READ_GYROSCOPE 1

/**
 * @brief Enable Supervisor Task
 * 1: Supervisor Task is scheduled
 * 0: Supervisor Task is not scheduled
 */
#define RUN_SUPERVISOR 1

/**
 * @brief Enable ReadSonars Task
 * 1: ReadSonars Task is scheduled
 * 0: ReadSonars Task is not scheduled
 */
#define RUN_READ_SONARS 1


/**
 * @brief Enable Synchronization Task
 * 1: Synchronization Task is scheduled
 * 0: Synchronization Task is not scheduled
 */
#define RUN_SYNCHRONIZATION 1

/**
 * @brief Enable PollingServer Task
 * 1: PollingServer Task is scheduled
 * 0: PollingServer Task is not scheduled
 */
#define RUN_POLLING_SERVER 1

/** 
 * @brief Main Debug Verbosity
 * 1 to enable prints, 0 to disable them 
 */
#define VERBOSE_DEBUG_MAIN 1

/** 
 * @brief Interrupt Debug Verbosity
 * 1 to enable prints, 0 to disable them 
 */
#define VERBOSE_DEBUG_IT 1


