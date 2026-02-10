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
 * @file actual_board.h
 * @brief Board identity selection for the synchronization module.
 *
 * Defines which board (Board1 or Board2) the firmware is being compiled for.
 * Exactly one of @ref SYNC_BOARD1 or @ref SYNC_BOARD2 should be enabled
 * so that board-specific synchronization logic is selected at compile time.
 *
 */

#ifndef INC_SYNCHRONIZATION_ACTUAL_BOARD_H_
#define INC_SYNCHRONIZATION_ACTUAL_BOARD_H_

/** @brief Compile-time selector indicating this build targets Board 1. */
#define SYNC_BOARD1

/* #define SYNC_BOARD2 */  /**< @brief Uncomment to compile for Board 2 instead. */

#endif /* INC_SYNCHRONIZATION_ACTUAL_BOARD_H_ */
