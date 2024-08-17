/**
 * @file Definitions.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file with the fsm `start`, fsm `gameover` of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Definitions.h"

#define BEGIN 1 /**< Code begin */
#define END 2   /**< Code end */

#include "../../Helpers/GameTetrisHelpers.h"
#include "../Helpers/FSMHelpers.h"

static void fsm_definitions(UserAction_t action, GameTetris *game,
                            const int code);

/**
 * @brief Defines a new state for a game based on the given action and code.
 *
 * This function updates the state of the game based on the user's action and
 * the given code. The function first checks if the game is valid, and then
 * updates the state accordingly.
 *
 * @param action The action taken by the user (e.g. start, terminate, etc.).
 * @param game The game object to be updated.
 * @param code An additional code provided by the user (e.g. END, BEGIN).
 */
static void fsm_definitions(UserAction_t action, GameTetris *game,
                            const int code) {
  if (game) {
    if (action == Terminate)
      game->state = EXIT;
    else if (action == Start) {
      if (code == END) reset(game, SPAWN);
      game->state = SPAWN;
    }
  }
}

/**
 * @brief Starts a new game or resumes a previous game.
 *
 * This function is called when the game starts or when the user wants to resume
 * a previous game. It updates the game state based on the given action.
 *
 * @param action The action taken by the user (e.g. start, resume, etc.).
 * @param game The game object to be updated.
 */
void FSM_Start(const UserAction_t action, GameTetris *game) {
  fsm_definitions(action, game, BEGIN);
}

/**
 * @brief Ends a game or resets the game state.
 *
 * This function is called when the game ends or when the user wants to reset
 * the game state. It updates the game state based on the given action and saves
 * the high score if necessary.
 *
 * @param action The action taken by the user (e.g. quit, restart, etc.).
 * @param game The game object to be updated.
 */
void FSM_GameOver(UserAction_t action, GameTetris *game) {
  fsm_definitions(action, game, END);
  if (action == Start || action == Terminate) saveHighScore(&game->engine);
}
