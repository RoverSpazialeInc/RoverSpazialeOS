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
 * @file scheduler_utils.c
 * @brief RTOS scheduler utility functions for Board2.
 *
 * Provides helpers to temporarily raise a task's priority to prevent
 * preemption (priority ceiling) and restore it afterward, creating
 * cooperative critical sections without disabling interrupts.
 */

#include "scheduler_utils.h"

/**
 * @brief Raises the calling task's priority to osPriorityHigh5.
 *
 * This effectively prevents preemption by other normal-priority tasks
 * while keeping interrupts enabled.
 *
 * @return The previous priority of the task (to be restored later).
 */
osPriority_t scheduler_set_high_priority(void)
{
    osThreadId_t thread_id = osThreadGetId();
    osPriority_t old_prio = osThreadGetPriority(thread_id);
    
    // Set priority to High5 (highest non-realtime priority in typical cmsis v2 configs)
    // This effectively prevents preemption by other normal tasks.
    osThreadSetPriority(thread_id, osPriorityHigh5);
    
    return old_prio;
}

/**
 * @brief Restores the calling task's priority to a previously saved value.
 *
 * @param old_prio The priority value to restore.
 */
void scheduler_restore_priority(osPriority_t old_prio)
{
    osThreadId_t thread_id = osThreadGetId();
    osThreadSetPriority(thread_id, old_prio);
}
