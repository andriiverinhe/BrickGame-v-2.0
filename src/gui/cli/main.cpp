#include <locale>

#include "UI/Snake/SnakeLoop.hpp"

extern "C" {
#include "MainWindow.h"
#include "UI/GameUI.h"
#include "UI/Tetris/TetrisLoop.h"
}

#include <stdlib.h>
#include <time.h>

int main() {
  setlocale(LC_ALL, "ru");
  srand(time(NULL));
  initCli();

  Mainwindow mainwindow;
  initMainWindow(&mainwindow);

  while (launch(&mainwindow)) {
    if (strcmp(mainwindow.games[mainwindow.sgame], s21::NGAME_SNAKE.data()) ==
        0)
      game_snake();
    if (strcmp(mainwindow.games[mainwindow.sgame], NGAME_TETRIS) == 0)
      game_tetris();
  }

  delCli();
  return 0;
}
