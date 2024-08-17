/**
 * @file Shift.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief SHIFT finite automaton
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Shift.h"

#include <stdbool.h>

#include "../../MacroPos.h"
#include "../Helpers/FSMHelpers.h"

static size_t getExtremePositionByY(const Model* model, const size_t cols);
static bool checkOperationGravity(GameTetris* game);

/**
 * @brief Get the extreme position by Y coordinate.
 *
 * @param model Pointer to the model.
 * @param cols Column index.
 * @return size_t The row index of the extreme position.
 */
static size_t getExtremePositionByY(const Model* model, const size_t cols) {
  size_t search_rows = 0;
  for (size_t i = 0; i < model->rows; i++)
    if (model->model_[i][cols] == true) search_rows = i;
  return search_rows;
}

/**
 * @brief Check if the operation gravity is possible for the current model.
 *
 * @param game Pointer to the game parameters.
 * @return true if gravity operation is possible, false otherwise.
 */
static bool checkOperationGravity(GameTetris* game) {
  bool codeGravity = true;

  for (size_t i = 0; (i < GET_CURRENT_COLS((*game))) && codeGravity; i++) {
    size_t index_pos_y = getExtremePositionByY(&game->current, i);
    int checkPosX = 0, checkPosY = 0;

    checkPosX =
        (int)i - (int)GET_CURRENT_MID_X((*game)) + GET_CURRENT_POS_X((*game));

    checkPosY = (int)index_pos_y - (int)GET_CURRENT_MID_Y((*game)) +
                GET_CURRENT_POS_Y((*game)) + COEF_POS_SHIFT;

    if (checkPosY < 0) continue;

    if (!isNormalCheckedPosition(checkPosX, checkPosY) ||
        (CELL_FIELD(checkPosY, checkPosX, (*game)) != false &&
         CELL_CURRENT_MODEL(index_pos_y, i, (*game)) == true)) {
      codeGravity = false;
      game->state = COLLISION;
    }
  }

  return codeGravity;
}

/**
 * @brief Shifts the current model downwards if possible.
 *
 * @param game Pointer to the game parameters.
 */
void FSM_Shift(GameTetris* game) {
  if (game && isNormalModel(&game->current)) {
    if (!game->engine.pause && checkOperationGravity(game)) {
      deletModelInField(game);
      game->current.position[Y]++;

      addedModelToField(game);
      game->state = MOVE;
    }
  }
}