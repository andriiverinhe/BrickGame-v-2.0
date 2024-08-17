/**
 * @file MacroPos.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the macros position of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Retrieves the X-coordinate of the current model's position.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return int The X-coordinate of the current model's position.
 */
#define GET_CURRENT_POS_X(game) game.current.position[X]

/**
 * @brief Retrieves the Y-coordinate of the current model's position.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return int The Y-coordinate of the current model's position.
 */
#define GET_CURRENT_POS_Y(game) game.current.position[Y]

/**
 * @brief Retrieves the X-coordinate of the center of the current model.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return int The X-coordinate of the center of the current model.
 */
#define GET_CURRENT_MID_X(game) game.current.center[X]

/**
 * @brief Retrieves the Y-coordinate of the center of the current model.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return int The Y-coordinate of the center of the current model.
 */
#define GET_CURRENT_MID_Y(game) game.current.center[Y]

/**
 * @brief Retrieves the number of columns in the current model.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return size_t The number of columns in the current model.
 */
#define GET_CURRENT_COLS(game) game.current.cols

/**
 * @brief Retrieves the number of rows in the current model.
 *
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return size_t The number of rows in the current model.
 */
#define GET_CURRENT_ROWS(game) game.current.rows

/**
 * @brief Retrieves the X-coordinate of the next model's position.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return int The X-coordinate of the next model's position.
 */
#define GET_NEXT_POS_X(game) game.next.position[X]

/**
 * @brief Retrieves the Y-coordinate of the next model's position.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return int The Y-coordinate of the next model's position.
 */
#define GET_NEXT_POS_Y(game) game.next.position[Y]

/**
 * @brief Retrieves the X-coordinate of the center of the next model.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return int The X-coordinate of the center of the next model.
 */
#define GET_NEXT_MID_X(game) game.next.center[X]

/**
 * @brief Retrieves the Y-coordinate of the center of the next model.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return int The Y-coordinate of the center of the next model.
 */
#define GET_NEXT_MID_Y(game) game.next.center[Y]

/**
 * @brief Retrieves the number of columns in the next model.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return size_t The number of columns in the next model.
 */
#define GET_NEXT_COLS(game) game.next.cols

/**
 * @brief Retrieves the number of rows in the next model.
 *
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return size_t The number of rows in the next model.
 */
#define GET_NEXT_ROWS(game) game.next.rows

/**
 * @brief Retrieves the value of the cell in the next model at the specified
 * position.
 *
 * @param i The row index.
 * @param j The column index.
 * @param game The GameTetris structure containing information about the
 * next model.
 * @return bool The value of the cell in the next model at the specified
 * position.
 */
#define CELL_NEXT_MODEL(i, j, game) game.next.model_[i][j]

/**
 * @brief Retrieves the value of the cell in the current model at the specified
 * position.
 *
 * @param i The row index.
 * @param j The column index.
 * @param game The GameTetris structure containing information about the
 * current model.
 * @return bool The value of the cell in the current model at the specified
 * position.
 */
#define CELL_CURRENT_MODEL(i, j, game) game.current.model_[i][j]

/**
 * @brief Retrieves the value of the cell in the game field at the specified
 * position.
 *
 * @param i The row index.
 * @param j The column index.
 * @param game The GameTetris structure containing information about the
 * game field.
 * @return bool The value of the cell in the game field at the specified
 * position.
 */
#define CELL_FIELD(i, j, game) game.engine.field[i][j]

/**
 * @brief Retrieves the value of the cell in the next model at the specified
 * position in the game field.
 *
 * @param i The row index.
 * @param j The column index.
 * @param game The GameTetris structure containing information about the
 * game field.
 * @return bool The value of the cell in the next model at the specified
 * position in the game field.
 */
#define CELL_NEXT(i, j, game) game.engine.next[i][j]

#ifdef __cplusplus
}
#endif