/**
 * @file Spawn.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief SPAWN finite automaton
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Spawn.h"

#include "../Helpers/FSMHelpers.h"

static void getCurrent(GameTetris *game);
static void getNext(GameTetris *game);

/**
 * @brief Retrieves the current model.
 *
 * This function updates the current model in the Brick Game Parameters
 * (game). If there is a next figure available, it copies the next figure
 * into the current model; otherwise, it selects a random model from the
 * available models.
 *
 * The position of the current model is set to the predefined start position
 * (START_X, START_Y).
 *
 * @param game Pointer to the Brick Game Parameters structure.
 */
static void getCurrent(GameTetris *game) {
  freeModel(&game->current);
  if (isNormalNextIndex(game))
    copyModel(&game->models.models[game->index_next], &game->current);
  else
    copyModel(&GET_RANDOM_MODEL(game), &game->current);

  game->current.position[X] = START_X;
  game->current.position[Y] = START_Y;
}

/**
 * @brief Retrieves the next model.
 *
 * This function updates the next model in the Brick Game Parameters (game)
 * by selecting a random model from the available models. It also updates the
 * double array representation of the next model if the next model is valid.
 *
 * @param game Pointer to the Brick Game Parameters structure.
 */
static void getNext(GameTetris *game) {
  game->index_next = getRandomIndex(getCountModels(&game->models));
  if (isNormalNextIndex(game)) setNextDooubleArray(game);
}

/**
 * @brief Handles the spawn state of the finite state machine.
 *
 * This function updates the current and next models in the Brick Game
 * Parameters (game) and transitions the state of the finite state machine
 * based on the availability of the models.
 *
 * @param game Pointer to the Brick Game Parameters structure.
 */
void FSM_Spawn(GameTetris *game) {
  if (game) {
    getCurrent(game);
    getNext(game);
    game->current_color = getRandomIndex(6) + 1;
    game->state = MOVE;
  }
}