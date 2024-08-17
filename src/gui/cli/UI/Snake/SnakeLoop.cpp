/**
 * @file SnakeLoop.cpp
 * @author nenamaxi (an.veringe@gmail.co)
 * @brief Snake game header file
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SnakeLoop.hpp"

extern "C" {
#include "../../../../brick_game/common/Signal/SignalProcessing.h"
#include "../GameUI.h"
}

/**
 * @brief Starts the game loop.
 *
 * This function initializes game settings, initializes the command-line
 * interface, initializes game components, and runs the game loop. It
 * continuously updates the game state based on user input and thread operations
 * until the game state becomes EXIT.
 */
void game_snake() {
  s21::GameSnake snake;
  GameWindows gameWin = {0, 0, 0};
  initGameWindow(&gameWin);

  while (snake.getState() != EXIT) {
    snake.userInput(get_signal(getch()), false);
    update(GET_INFO_PRINT(ISNAME), &gameWin, snake.updateCurrentState(),
           convertStateToStrInf(snake.getState()));
  }
  freeGameWindow(&gameWin);
}