/**
 * @file TetrisLoop.c
 * @author nenamaxi (an.veringe@gmail.co)
 * @brief Tetris game source file
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "TetrisLoop.h"

#include <stdbool.h>

#include "../../../../brick_game/common/Signal/SignalProcessing.h"
#include "../GameUI.h"

/**
 * @brief Starts the game loop.
 *
 * This function initializes game settings, initializes the command-line
 * interface, initializes game components, and runs the game loop. It
 * continuously updates the game state based on user input and thread operations
 * until the game state becomes EXIT.
 */
void game_tetris() {
  bool code = true;

  GameTetris game = {0};
  code &= initializeGameTetris(&game);

  GameWindows gameWin = {0};
  code &= initGameWindow(&gameWin);

  if (code == SUCCESS) {
    updateParams(&game);
    while (game.state != EXIT) {
      userInput(get_signal(getch()), false);
      update(GET_INFO_PRINT(ITNAME), &gameWin, updateCurrentState(),
             convertStateToStrInf(game.state));
    }
  }

  cleanGameTetris(&game);
  freeGameWindow(&gameWin);
}