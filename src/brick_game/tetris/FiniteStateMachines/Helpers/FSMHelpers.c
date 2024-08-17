/**
 * @file FSMHelpers.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File in which all auxiliary functions for finite automata are stored
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "FSMHelpers.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../MacroPos.h"

static void zerroingDoubleArray(int ***array_, const size_t rows,
                                const size_t cols);
static void helperModelOperation(GameTetris *game, const int mode);

/**
 * @brief Reset all elements of a double pointer array to false
 *
 * This function resets all elements of a double pointer array to false. It
 * takes a pointer to a pointer to an integer array, along with the dimensions
 * of the array. If the array pointer and the array itself are not NULL, the
 * function iterates through each element of the array and sets its value to
 * false.
 *
 * @param array_ Pointer to a pointer to an integer array
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 */
static void zerroingDoubleArray(int ***array_, const size_t rows,
                                const size_t cols) {
  if (*array_) {
    for (size_t i = 0; i < rows; i++)
      for (size_t j = 0; j < cols; j++) (*array_)[i][j] = false;
  }
}

/**
 * @brief Perform model operation on the game field
 *
 * This function performs a model operation on the game field based on the
 * specified mode. It calculates the position of the model on the field,
 * iterates through each cell of the model, and updates the corresponding cells
 * on the field accordingly.
 *
 * @param game Pointer to the Brick Game parameters structure
 * @param mode Mode of the operation (ADD or DEL)
 */
static void helperModelOperation(GameTetris *game, const int mode) {
  if (!game || !game->engine.field || !isNormalModel(&game->current)) return;
  int x_pos = GET_CURRENT_POS_X((*game)) - GET_CURRENT_MID_X((*game));
  int y_pos = GET_CURRENT_POS_Y((*game)) - GET_CURRENT_MID_Y((*game));
  const size_t rows = GET_CURRENT_ROWS((*game));
  const size_t cols = GET_CURRENT_COLS((*game));

  for (size_t i = 0; i < rows; i++, y_pos++, x_pos -= (int)cols)
    for (size_t j = 0; j < cols; j++, x_pos++) {
      if (!isNormalCheckedPosition(x_pos, y_pos)) continue;

      if (CELL_CURRENT_MODEL(i, j, (*game)) == true) {
        if (mode == ADD)
          CELL_FIELD(y_pos, x_pos, (*game)) = game->current_color;
        if (mode == DEL && CELL_FIELD(y_pos, x_pos, (*game)) != false)
          CELL_FIELD(y_pos, x_pos, (*game)) = false;
      }
    }
}

/**
 * @brief Check if the next index is within the bounds of the models array.
 *
 * @param game The GameTetris struct.
 * @return true If the next index is within the bounds of the models array.
 * @return false If the next index is outside the bounds of the models array.
 */
bool isNormalNextIndex(const GameTetris *game) {
  if (!game) return false;
  return game->index_next < getCountModels(&game->models);
}

/**
 * @brief Get a random index within the range of available models
 *
 * This function generates a random index within the range of available models.
 *
 * @param maxIndex The number of available models
 * @return An integer representing the random index
 */
int getRandomIndex(const size_t maxIndex) {
  const int min = 0;
  const int max = (int)maxIndex - 1;
  int index = min;
  if (max > min) index = rand() % (max - min + 1) + min;
  return index;
}

/**
 * @brief Reset the 'next' array in the game information structure
 *
 * This function resets the 'next' array in the game information structure to
 * false. It calls the zerroingDoubleArray function with the 'next' array
 * pointer, along with the dimensions of the 'next' array.
 *
 * @param engine Pointer to the game information structure
 */
void zeroingNext(GameInfo_t *engine) {
  if (engine) zerroingDoubleArray(&engine->next, HNEXT, WNEXT);
}

/**
 * @brief Reset the game field array in the game information structure
 *
 * This function resets the game field array in the game information structure
 * to false. It calls the zerroingDoubleArray function with the game field array
 * pointer, along with the dimensions of the game field array.
 *
 * @param engine Pointer to the game information structure
 */
void zeroingField(GameInfo_t *engine) {
  if (engine) zerroingDoubleArray(&engine->field, HFIELD, WFIELD);
}

/**
 * @brief Reset all information in the game parameters structure to initial
 * values
 *
 * This function resets all information stored in the game parameters structure
 * to its initial values. It deallocates memory for the current and next models,
 * sets all cells in the game field to false, and resets the level, speed, and
 * score.
 *
 * @param game Pointer to the game parameters structure
 */
void zeroingInfo(GameTetris *game) {
  if (!game) return;
  freeModel(&game->current);
  zeroingField(&game->engine);
  zeroingNext(&game->engine);

  setLevel(&game->engine, INIT_LEVEL);
  setSpeed(&game->engine, COEF_SPEED_LEVEL_1);
  setScore(&game->engine, INIT_SCORE);
}

/**
 * @brief Add current model to the game field
 *
 * This function adds the current model to the game field by calling the
 * helperModelOperation function with the `ADD` mode.
 *
 * @param game Pointer to the Brick Game parameters structure
 */
void addedModelToField(GameTetris *game) { helperModelOperation(game, ADD); }

/**
 * @brief Delete current model from the game field
 *
 * This function deletes the current model from the game field by calling the
 * helperModelOperation function with the `DEL` mode.
 *
 * @param game Pointer to the Brick Game parameters structure
 */
void deletModelInField(GameTetris *game) { helperModelOperation(game, DEL); }

/**
 * @brief Set the next double array based on the next model
 *
 * This function sets the next double array in the Brick Game parameters
 * structure based on the next model. It first clears the next double array by
 * calling the zeroingNext function, then iterates through each cell of the next
 * model and copies its values to the corresponding cells of the next double
 * array.
 *
 * @param game Pointer to the Brick Game parameters structure
 */
void setNextDooubleArray(GameTetris *game) {
  if (!game || !game->engine.next) return;
  zeroingNext(&game->engine);

  for (size_t i = 0; i < game->models.models[game->index_next].rows; i++)
    for (size_t j = 0; j < game->models.models[game->index_next].cols; j++)
      if (i < HNEXT && j < WNEXT)
        CELL_NEXT(i, j, (*game)) =
            game->models.models[game->index_next].model_[i][j];
}

/**
 * @brief Check if the given position is within the bounds of the field
 *
 * This function checks if the given position (x, y) is within the bounds of the
 * game field.
 *
 * @param x The x-coordinate of the position
 * @param y The y-coordinate of the position
 * @return true if the position is within the bounds of the field, false
 * otherwise
 */
bool isNormalCheckedPosition(const int x, const int y) {
  return (0 <= x && x < WFIELD) && (0 <= y && y < HFIELD);
}