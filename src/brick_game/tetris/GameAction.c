/**
 * @file GameAction.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File with the basic game action
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "FiniteStateMachines/FiniteStateMachines.h"
#include "GameTetris.h"

/**
 * @brief Processes user input based on the current game state.
 *
 * @param action The user action to process.
 * @param hold Indicates whether the action is being held.
 */
void userInput(UserAction_t action, bool hold) {
  (void)hold;
  GameTetris *game = updateParams(NULL);
  if (game) {
    switch (game->state) {
      case START:
        FSM_Start(action, game);
        break;

      case SPAWN:
        FSM_Spawn(game);
        break;

      case MOVE:
        FSM_Move(action, game);
        break;

      case SHIFT:
        FSM_Shift(game);
        break;

      case COLLISION:
        FSM_Collision(game);
        break;

      case GAMEOVER:
        FSM_GameOver(action, game);
        break;

      default:
        break;
    }
  }
}