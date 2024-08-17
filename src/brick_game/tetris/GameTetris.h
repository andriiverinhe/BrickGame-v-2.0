/**
 * @file GameTetris.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File with the basic structures of the game
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

#include "../common/Action/Action.h"
#include "../common/Info/Info.h"
#include "../common/State/State.h"
#include "MacroInf.h"
#include "MacroPos.h"
#include "Model/GameModel.h"
#include "Timer/Timer.h"

/**
 * @brief Structure representing game parameters.
 */
typedef struct {
  Models models;     /**< Collection of available models. */
  Model current;     /**< Current model in the game. */
  int current_color; /**< Current model color */
  size_t index_next; /**< Next model index */
  GameState_t state; /**< Current state of the game. */
  GameTimer_t timer; /**< Timer for shifting */
  GameInfo_t engine; /**< Information about the game. */
} GameTetris;

void userInput(UserAction_t action, bool hold);

int initializeGameInfo(GameInfo_t *engine);
int initializeGameTetris(GameTetris *game);
void cleanGameInfo(GameInfo_t *engine);
void cleanGameTetris(GameTetris *game);
GameTetris *updateParams(GameTetris *game);
GameInfo_t updateCurrentState(void);
void reset(GameTetris *game, const GameState_t reset_state);

#ifdef __cplusplus
}
#endif