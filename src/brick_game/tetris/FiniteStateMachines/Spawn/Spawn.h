/**
 * @file Spawn.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief SPAWN finite automaton
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../GameTetris.h"

#define START_X 4  /**< Start position `x` */
#define START_Y -1 /**< Start position `y` */

/**
 * @brief Retrieves a random model from the available models.
 *
 * This macro returns a randomly selected model from the models stored in the
 * Brick Game Parameters (game).
 *
 * @param game Pointer to the Brick Game Parameters structure containing
 *                 the models.
 *
 * @return The randomly selected model from the available models.
 */
#define GET_RANDOM_MODEL(game) \
  game->models.models[getRandomIndex(game->models.count)]

void FSM_Spawn(GameTetris *game);

#ifdef __cplusplus
}
#endif