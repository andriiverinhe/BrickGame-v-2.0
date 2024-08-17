/**
 * @file Move.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief MOVE finite automaton
 * @version 0.1
 * @date 2024-04-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../../GameTetris.h"

/**
 * @brief Get the coefficient for movement.
 *
 * This macro calculates the coefficient for movement based on the direction.
 * If the direction is Left, the coefficient is -1, otherwise it is 1.
 *
 * @param direction The direction of movement.
 * @return int The coefficient for movement.
 */
#define GET_COEF_MOVE(direction) (direction == Left) ? -1 : 1

/**
 * @brief Calculates the backward position along the X-axis.
 *
 * This macro calculates the backward position along the X-axis based on the
 * total number of columns and the current index.
 *
 * @param cols Total number of columns.
 * @param i Current index.
 * @return int Backward position along the X-axis.
 */
#define BACK_POS_X(cols, i) cols - i - 1

/**
 * @brief Calculates the backward position along the Y-axis.
 *
 * This macro calculates the backward position along the Y-axis based on the
 * total number of rows and the current index.
 *
 * @param rows Total number of rows.
 * @param i Current index.
 * @return int Backward position along the Y-axis.
 */
#define BACK_POS_Y(rows, i) rows - i - 1

/**
 * @brief Calculates the half number of rows.
 *
 * This macro calculates the half number of rows based on the total number of
 * rows.
 *
 * @param rows Total number of rows.
 * @return int Half number of rows.
 */
#define HALF_ROWS(rows) (rows / 2)

/**
 * @brief Calculates the half number of columns.
 *
 * This macro calculates the half number of columns based on the total number of
 * columns.
 *
 * @param cols Total number of columns.
 * @return int Half number of columns.
 */
#define HALF_COLS(cols) (cols / 2)

void FSM_Move(const UserAction_t action, GameTetris* game);

#ifdef __cplusplus
}
#endif