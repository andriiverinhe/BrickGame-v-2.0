/**
 * @file GameTetris.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File with the basic structures of the game
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GameTetris.h"

#include "FiniteStateMachines/Helpers/FSMHelpers.h"
#include "Helpers/GameTetrisHelpers.h"
#include "Model/Helpers/ModelHelpers.h"

/**
 * @brief Initializes the GameInfo_t structure.
 *
 * This function initializes the GameInfo_t structure by allocating memory for
 * the game field and next figures, setting initial score, high score, level,
 * speed, and pause state.
 *
 * @param engine Pointer to the GameInfo_t structure to be initialized.
 */
int initializeGameInfo(GameInfo_t *engine) {
  int code = FAIL;
  if (engine) {
    code = SUCCESS;
    allocateField(engine);
    allocateNext(engine);
    initializeHighScore(engine);
    setLevel(engine, INIT_LEVEL);
    setScore(engine, INIT_SCORE);
    setSpeed(engine, COEF_SPEED_LEVEL_1);
    setPause(engine, false);
  }
  return code;
}

/**
 * @brief Initializes the GameTetris structure.
 *
 * This function initializes the GameTetris structure by initializing
 * the game information, models, and setting the game state to START.
 *
 * @param game Pointer to the GameTetris structure to be initialized.
 */
int initializeGameTetris(GameTetris *game) {
  int code = FAIL;
  if (game) {
    initializeGameInfo(&game->engine);
    initializeTimer(&game->timer);
    game->state = START;
    const char *filenamebd = NAME_FILE_TEMPLATE;
    if (initializeModels(&game->models, (char *)filenamebd) == SUCCESS) {
      game->index_next = game->models.count + 1;
      code = SUCCESS;
    }
  }

  return code;
}

/**
 * @brief Frees the memory allocated for the GameInfo_t structure.
 *
 * This function frees the memory allocated for the field and next arrays
 * in the GameInfo_t structure and resets the score, high score, level, speed,
 * and pause attributes.
 *
 * @param engine Pointer to the GameInfo_t structure to be freed.
 */
void cleanGameInfo(GameInfo_t *engine) {
  if (engine) {
    freeField(engine);
    freeNext(engine);
    setHigeScore(engine, 0);
    setLevel(engine, 0);
    setScore(engine, 0);
    setSpeed(engine, 0);
    setPause(engine, 0);
  }
}

/**
 * @brief Frees the memory allocated for the GameTetris structure.
 *
 * This function frees the memory allocated for the GameInfo_t structure,
 * current and next models, and the models array in the GameTetris
 * structure. Additionally, it sets the state attribute to EXIT.
 *
 * @param game Pointer to the GameTetris structure to be freed.
 */
void cleanGameTetris(GameTetris *game) {
  if (game) {
    cleanGameInfo(&game->engine);
    freeModel(&game->current);
    freeModels(&game->models);
    freeTimer(&game->timer);
    game->state = EXIT;
  }
}

/**
 * @brief Updates the game parameters.
 *
 * This function updates the game parameters and returns a pointer to the
 * updated GameTetris structure.
 *
 * @param game Pointer to the GameTetris structure containing the updated
 * parameters.
 * @return GameTetris* Pointer to the updated GameTetris structure.
 */
GameTetris *updateParams(GameTetris *game) {
  static GameTetris *data;
  if (game != NULL) data = game;
  return data;
}

/**
 * @brief Updates and retrieves the current game state information.
 *
 * This function updates and retrieves the current game state information,
 * including the field, next piece, score, level, speed, and pause state.
 *
 * @return GameInfo_t The updated game state information.
 */
GameInfo_t updateCurrentState(void) {
  const GameTetris *game = updateParams(NULL);
  return game->engine;
}

/**
 * @brief Resets the game state to a specific state.
 *
 * @param game The struct GameTetris.
 * @param reset_state The state to which the game should be moved
 */
void reset(GameTetris *game, const GameState_t reset_state) {
  if (!game) return;
  if (reset_state == START || reset_state == SPAWN)
    game->state = reset_state;
  else
    game->state = SPAWN;
  zeroingInfo(game);
}