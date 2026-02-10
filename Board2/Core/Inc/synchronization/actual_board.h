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
 * @brief Board identity selection macro.
 *
 * Defines the compile-time macro that identifies which board
 * (Board 1 or Board 2) the firmware is being built for.
 * Exactly one of @c SYNC_BOARD1 or @c SYNC_BOARD2 should be defined.
 */

#ifndef INC_SYNCHRONIZATION_ACTUAL_BOARD_H_
#define INC_SYNCHRONIZATION_ACTUAL_BOARD_H_

/**
 * @brief Uncomment to build firmware for Board 1.
 */
//#define SYNC_BOARD1

/**
 * @brief Selects Board 2 as the active target board.
 */
#define SYNC_BOARD2

#endif /* INC_SYNCHRONIZATION_ACTUAL_BOARD_H_ */
