/**
 * @file Move.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief MOVE finite automaton
 * @version 0.1
 * @date 2024-04-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Move.h"

#include <stdlib.h>

#include "../../MacroPos.h"
#include "../Helpers/FSMHelpers.h"
#include "../Shift/Shift.h"

static bool isCentralSymmetricalModel(const Model* model);
static bool isAsixXSym(const Model* model);
static bool isAsixYSym(const Model* model);
static bool isAxialSymmericalModel(const Model* model);

static size_t getExtremePositionByX(const Model* model, const size_t y,
                                    UserAction_t extreme);
static void moving(GameTetris* game, const UserAction_t direction);

static void setCenter(Model* newm, const Model* prev);
static bool checkRotatedModel(const Model* model, const GameTetris* game);
static void rotation(GameTetris* game);

/**
 * @brief Check if the given model is centrally symmetrical.
 *
 * This function checks if the given model is centrally symmetrical.
 *
 * @param model The model to check.
 * @return true If the model is centrally symmetrical.
 * @return false If the model is not centrally symmetrical.
 */
static bool isCentralSymmetricalModel(const Model* model) {
  bool isSymmetrical = true;

  const size_t rows = model->rows;
  const size_t cols = model->cols;

  for (size_t i = 0; (i <= HALF_ROWS(rows)) && isSymmetrical; i++)
    for (size_t j = 0; (j <= HALF_COLS(cols)) && isSymmetrical; j++)
      if (model->model_[i][j] !=
          model->model_[BACK_POS_Y(rows, i)][BACK_POS_X(cols, j)])
        isSymmetrical = false;

  return isSymmetrical;
}

/**
 * @brief Check if the given model is symmetric with respect to the X-axis.
 *
 * This function checks if the given model is symmetric with respect to the
 * X-axis.
 *
 * @param model The model to check.
 * @return true If the model is symmetric with respect to the X-axis.
 * @return false If the model is not symmetric with respect to the X-axis.
 */
static bool isAsixXSym(const Model* model) {
  bool isSym = true;
  if (model->rows <= 1) isSym = false;
  for (size_t i = 0; (i < HALF_ROWS(model->rows)) && isSym; ++i)
    for (size_t j = 0; (j < model->cols) && isSym; ++j)
      if (model->model_[i][j] != model->model_[BACK_POS_Y(model->rows, i)][j])
        isSym = false;

  return isSym;
}

/**
 * @brief Check if the given model is symmetric with respect to the Y-axis.
 *
 * This function checks if the given model is symmetric with respect to the
 * Y-axis.
 *
 * @param model The model to check.
 * @return true If the model is symmetric with respect to the Y-axis.
 * @return false If the model is not symmetric with respect to the Y-axis.
 */
static bool isAsixYSym(const Model* model) {
  bool isSym = true;
  if (model->cols <= 1) isSym = false;
  for (size_t i = 0; (i < model->rows) && isSym; ++i)
    for (size_t j = 0; (j < HALF_COLS(model->cols)) && isSym; ++j)
      if (model->model_[i][j] != model->model_[i][BACK_POS_X(model->cols, j)])
        isSym = false;

  return isSym;
}

/**
 * @brief Check if the given model is axially symmetrical.
 *
 * This function checks if the given model is axially symmetrical, meaning it is
 * symmetric with respect to both the X-axis and Y-axis.
 *
 * @param model The model to check.
 * @return true If the model is axially symmetrical.
 * @return false If the model is not axially symmetrical.
 */
static bool isAxialSymmericalModel(const Model* model) {
  bool isSymmetrical = true;
  isSymmetrical &= isAsixXSym(model);
  isSymmetrical &= isAsixYSym(model);
  return isSymmetrical;
}

/**
 * @brief Get the extreme position by X-coordinate.
 *
 * This function retrieves the extreme position by X-coordinate for the given
 * model and Y-coordinate, based on the specified extreme direction.
 *
 * @param model The model to analyze.
 * @param y The Y-coordinate.
 * @param extreme The extreme direction (Left or Right).
 * @return size_t The extreme X-coordinate.
 */
static size_t getExtremePositionByX(const Model* model, const size_t y,
                                    UserAction_t extreme) {
  bool code = false;
  int x = 0;
  for (size_t i = 0; (i < model->cols) && (code == false); i++) {
    if (model->model_[y][i] == true) {
      x = i;
      if (extreme == Left) code = true;
    }
  }
  return x;
}

/**
 * @brief Move the current model in the specified direction.
 *
 * This function moves the current model in the specified direction (Left or
 * Right) if possible.
 *
 * @param game The Brick Game Tetris parameters.
 * @param direction The direction of movement (Left or Right).
 */
static void moving(GameTetris* game, const UserAction_t direction) {
  int code = true;
  int coef = GET_COEF_MOVE(direction);

  for (size_t j = 0; (j < GET_CURRENT_ROWS((*game))) && code == true; j++) {
    int index_pos_x = (int)getExtremePositionByX(&game->current, j, direction);
    index_pos_x -= GET_CURRENT_MID_X((*game));

    int checkPosX = 0, checkPosY = 0;
    checkPosX = (int)GET_CURRENT_POS_X((*game)) + (int)index_pos_x + coef;

    checkPosY = (int)GET_CURRENT_POS_Y((*game)) +
                (int)(j - (int)GET_CURRENT_MID_Y((*game)));

    if (checkPosX >= 0 && checkPosX < WFIELD) {
      if (checkPosY >= 0 && checkPosY < HFIELD)
        if (CELL_FIELD(checkPosY, checkPosX, (*game)) != false) code = false;
    } else
      code = false;
  }

  if (code == true) {
    deletModelInField(game);
    game->current.position[X] += coef;
    addedModelToField(game);
  }
}

/**
 * @brief Set the center of the new model based on the previous model's center.
 *
 * This function sets the center of the new model based on the center of the
 * previous model. If the previous model is centrally symmetrical, it ensures
 * that the center of the new model is within its bounds.
 *
 * @param newm The new model whose center is to be set.
 * @param prev The previous model whose center is used as a reference.
 */
static void setCenter(Model* newm, const Model* prev) {
  if (isCentralSymmetricalModel(prev)) {
    COORD x = Y, y = X;
    if (prev->center[X] < (int)newm->cols &&
        prev->center[Y] < (int)newm->rows) {
      x = X;
      y = Y;
    }
    newm->center[X] = prev->center[x];
    newm->center[Y] = prev->center[y];
  }
}

/**
 * @brief Check if the rotated model can be placed on the game field.
 *
 * This function checks if the rotated model can be placed on the game field
 * without overlapping with other occupied cells.
 *
 * @param model The model to be checked.
 * @param game The game parameters.
 * @return true If the rotated model can be placed on the game field without
 * overlapping.
 * @return false If the rotated model overlaps with occupied cells on the game
 * field.
 */
static bool checkRotatedModel(const Model* model, const GameTetris* game) {
  int pos_x = model->position[X] - model->center[X];
  int pos_y = model->position[Y] - model->center[Y];

  bool codeRotate = true;

  for (size_t i = 0; (i < model->rows) && codeRotate;
       i++, pos_y++, pos_x -= model->cols) {
    for (size_t j = 0; (j < model->cols) && codeRotate; j++, pos_x++) {
      if (!isNormalCheckedPosition(pos_x, pos_y)) {
        codeRotate = false;
        continue;
      }

      if (model->model_[i][j] != false &&
          CELL_FIELD(pos_y, pos_x, (*game)) != false)
        codeRotate = false;
    }
  }
  return codeRotate;
}

/**
 * @brief Rotate the current model.
 *
 * This function rotates the current model clockwise if it is not axially
 * symmetrical. It first deletes the current model from the field, then creates
 * a rotated copy of the model, sets its center, checks if it can be placed on
 * the field, and updates the current model if it can. Finally, it adds the
 * updated model to the field.
 *
 * @param game The game parameters.
 */
static void rotation(GameTetris* game) {
  if (!isAxialSymmericalModel(&game->current)) {
    deletModelInField(game);

    Model rotatedm = {0};
    copyModel(&game->current, &rotatedm);
    rotateModel(&rotatedm);

    setCenter(&rotatedm, &game->current);

    if (checkRotatedModel(&rotatedm, game)) {
      freeModel(&game->current);
      copyModel(&rotatedm, &game->current);
    }

    addedModelToField(game);
    freeModel(&rotatedm);
  }
}

/**
 * @brief Handle move actions in the game state machine.
 *
 * This function handles move actions in the game state machine. It performs
 * different actions based on the given action parameter:
 *
 * `-` If the action is Left or Right, it moves the current model horizontally.
 * `-` If the action is Action, it rotates the current model.
 * `-` If the action is Down, it continuously moves the current model downward
 * until it collides.
 *
 * @param action The action to handle.
 * @param game The game parameters.
 */
void FSM_Move(const UserAction_t action, GameTetris* game) {
  if (!game && !isNormalModel(&game->current)) return;

  if (action == Pause) setPause(&game->engine, !getPause(&game->engine));
  if (getPause(&game->engine) == false) {
    if (game->timer.indicator == false) runTime(&game->timer);
    switch (action) {
      case Down:
        while (game->state != COLLISION) FSM_Shift(game);
        break;

      case Left:
      case Right:
        moving(game, action);
        break;

      case Action:
        rotation(game);
        break;

      case Terminate:
        game->state = GAMEOVER;
        break;

      default:
        break;
    }
  }
}