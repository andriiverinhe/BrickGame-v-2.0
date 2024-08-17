/**
 * @file Collision.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief COLLISION finite automaton
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Collision.h"

#include "../../Helpers/GameTetrisHelpers.h"
#include "../../MacroPos.h"
#include "../Helpers/FSMHelpers.h"

static size_t getScoreAdded(const size_t crows);
static size_t getNewLevel(const size_t score);
static bool checkRowsDelete(const GameTetris *game, const size_t rows);
static void deleteRows(const GameTetris *game, const size_t rows);
static bool checkGameOver(GameTetris *game);

/**
 * @brief Calculates the time interval based on the game speed.
 *
 * This function calculates the time interval (in milliseconds) based on the
 * game speed specified in the GameTetris structure. The time interval
 * decreases as the game speed increases.
 *
 * @param engine Pointer to the GameInfo_t structure containing the game
 * speed.
 * @return unsigned int The time interval in milliseconds.
 */
unsigned int getTime(const GameInfo_t *engine) {
  unsigned int time = 1;
  switch (getLevel(engine)) {
    case LFIRST:
      time = COEF_SPEED_LEVEL_1;
      break;
    case LSECOND:
      time = COEF_SPEED_LEVEL_2;
      break;
    case LTHIRD:
      time = COEF_SPEED_LEVEL_3;
      break;
    case LFOURTH:
      time = COEF_SPEED_LEVEL_4;
      break;
    case LFIFTH:
      time = COEF_SPEED_LEVEL_5;
      break;
    case LSIXTH:
      time = COEF_SPEED_LEVEL_6;
      break;
    case LSEVENTH:
      time = COEF_SPEED_LEVEL_7;
      break;
    case LEIGHTH:
      time = COEF_SPEED_LEVEL_8;
      break;
    case LNINETH:
      time = COEF_SPEED_LEVEL_9;
      break;
    case LTENTH:
      time = COEF_SPEED_LEVEL_10;
      break;
    default:
      time = COEF_SPEED_LEVEL_1;
      break;
  }
  return time;
}

/**
 * @brief Calculates the score added based on the number of completed rows.
 *
 * @param crows The number of completed rows.
 * @return The score added.
 */
static size_t getScoreAdded(const size_t crows) {
  size_t score = 0;
  switch (crows) {
    case LFIRST:
      score = POINT_ONE_LINE;
      break;
    case LSECOND:
      score = POINT_TWO_LINE;
      break;
    case LTHIRD:
      score = POINT_THREE_LINE;
      break;
    case LFOURTH:
      score = POINT_FOUR_LINE;
      break;

    default:
      break;
  }
  return score;
}

/**
 * @brief Determines the new level based on the current score.
 *
 * @param score The current score.
 * @return The new level.
 */
static size_t getNewLevel(const size_t score) {
  size_t lvl = (score / FIRST);
  if (lvl > LTENTH) lvl = LTENTH;
  return lvl;
}

/**
 * @brief Checks if all cells in a specified row are occupied.
 *
 * @param game The game parameters.
 * @param rows The row index to check.
 * @return true if all cells in the row are occupied, false otherwise.
 */
static bool checkRowsDelete(const GameTetris *game, const size_t rows) {
  bool del = true;
  for (size_t i = 0; (i < WFIELD) && (del == true); i++)
    if (game->engine.field[rows][i] == false) del = false;
  // del &= game->engine.field[rows][i];
  return del;
}

/**
 * @brief Deletes a specified row by shifting all rows above it down by one.
 *
 * @param game The game parameters.
 * @param rows The index of the row to delete.
 */
static void deleteRows(const GameTetris *game, const size_t rows) {
  for (size_t i = 0; i < WFIELD; i++)
    for (size_t j = rows; j > 0; j--)
      game->engine.field[j][i] = game->engine.field[j - 1][i];
}

/**
 * @brief Checks if the game is over by examining the top row of the game field.
 *
 * @param game The game parameters.
 * @return true if the game is not over, false otherwise.
 */
static bool checkGameOver(GameTetris *game) {
  bool ok = true;
  for (size_t i = 0; (i < WFIELD) && ok; i++) {
    if (CELL_FIELD(0, i, (*game)) != false) {
      game->state = GAMEOVER;
      ok = false;
    } else
      game->state = SPAWN;
  }
  return ok;
}

/**
 * @brief Handles collision events in the game state machine.
 *
 * @param game The game parameters.
 */
void FSM_Collision(GameTetris *game) {
  if (!game) return;
  if (checkGameOver(game)) {
    int count_rows = 0;
    for (size_t j = MAX_INDEX_Y; j > 0;) {
      if (checkRowsDelete(game, j)) {
        deleteRows(game, j);
        count_rows++;
      } else
        j--;
    }

    setScore(&game->engine,
             getScore(&game->engine) + getScoreAdded(count_rows));
    setLevel(&game->engine, getNewLevel(getScore(&game->engine)));
    setSpeed(&game->engine, getTime(&game->engine));

    if (getScore(&game->engine) >= getHigeScore(&game->engine))
      saveHighScore(&game->engine);

    setHigeScore(&game->engine, getScore(&game->engine));
  }
}