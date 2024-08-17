/**
 * @file MainWindow.c
 * @author nenamaxi(an.veringe@gmail.com)
 * @brief Source file Mainwindow
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "MainWindow.h"

#include <ncurses.h>

#include "UI/GameUI.h"

static void draw(WINDOW *wmenu, Mainwindow *menu, const int *highlight);
static void movement(WINDOW *wmenu, Mainwindow *menu, int *highlight,
                     bool *launch, bool *exec);

/**
 * @brief Draws a menu window.
 *
 * @param wmenu The window to draw the menu in.
 * @param menu The main window structure containing information about the menu.
 * @param highlight The index of the highlighted item in the menu.
 */
static void draw(WINDOW *wmenu, Mainwindow *menu, const int *highlight) {
  if (!wmenu || !menu) return;
  wattron(wmenu, A_BOLD);

  for (int i = 0; i < (int)menu->cinfo; i++) {
    COLOR_TEXT(wmenu, WHITE_BLACK);
    if (i == (*highlight)) {
      wattron(wmenu, A_REVERSE);
      COLOR_TEXT(wmenu, GREEN_BLACK);
    }
    if (strcmp(menu->info[i], menu->games[menu->sgame]) == 0)
      COLOR_TEXT(wmenu, RED_BLACK);

    mvwprintw(wmenu, i + i + 4,
              ((MENU_WIDTH / 2) - (strlen(menu->info[i]) / 2)), "%s",
              menu->info[i]);

    wattroff(wmenu, A_REVERSE);
  }
  wattroff(wmenu, A_BOLD);
}

/**
 * @brief Manages the user input and updates the menu state.
 *
 * @param wmenu The window to read user input from.
 * @param menu The main window structure containing information about the menu.
 * @param highlight The index of the currently highlighted item in the menu.
 * @param launch A flag indicating whether the menu should launch a game.
 * @param exec A flag indicating whether the menu should execute a command.
 */
static void movement(WINDOW *wmenu, Mainwindow *menu, int *highlight,
                     bool *launch, bool *exec) {
  switch (get_signal(wgetch(wmenu))) {
    case Left:
    case Up:
      (*highlight)--;
      if ((*highlight) == -1) (*highlight) = 0;
      break;

    case Right:
    case Down:
      (*highlight)++;
      if ((*highlight) == (int)menu->cinfo) (*highlight) = (int)menu->cinfo - 1;
      break;

    case Start:
      if (strcmp(menu->info[(*highlight)], GET_INFO_PRINT(IEXIT)) == 0) {
        (*launch) = false;
        (*exec) = false;
      }
      if (strcmp(menu->info[(*highlight)], GET_INFO_PRINT(ISTART)) == 0) {
        (*launch) = true;
        (*exec) = false;
      }
      if (strcmp(menu->info[(*highlight)], menu->games[INDEX_FIRST_GAME]) == 0)
        menu->sgame = INDEX_FIRST_GAME;
      if (strcmp(menu->info[(*highlight)], menu->games[INDEX_SECOND_GAME]) == 0)
        menu->sgame = INDEX_SECOND_GAME;
      break;

    default:
      break;
  }
}

/**
 * @brief Launches a game menu.
 *
 * @param menu The main window structure containing information about the menu.
 *
 * @return Whether the game was launched successfully.
 */
bool launch(Mainwindow *menu) {
  bool launch = false;
  int highlight = 0;
  int yMax, xMax;

  getmaxyx(stdscr, yMax, xMax);

  WINDOW *wmenu = newwin(MENU_HEIGHT, MENU_WIDTH, yMax / 2 - MENU_HEIGHT / 2,
                         xMax / 2 - MENU_WIDTH / 2);

  keypad(wmenu, true);
  DRAW_BOX(wmenu);
  COLOR_BOX(wmenu, WHITE_BLACK);

  mvwprintw(wmenu, 0, 2, "%s", menu->title);
  mvwprintw(wmenu, 2, 2, "%s", menu->description);

  refresh();
  wrefresh(wmenu);

  bool exec = true;
  while (exec) {
    draw(wmenu, menu, &highlight);
    movement(wmenu, menu, &highlight, &launch, &exec);
    refresh();
    wrefresh(wmenu);
  }

  keypad(wmenu, false);
  wclear(wmenu);
  refresh();
  wrefresh(wmenu);
  werase(wmenu);
  delwin(wmenu);
  return launch;
}

/**
 * @brief Initializes the main window structure.
 *
 * @param mw The main window structure to be initialized.
 *
 * @return Whether the initialization was successful.
 */
bool initMainWindow(Mainwindow *mw) {
  strcpy(mw->title, GET_INFO_PRINT(INAMEBG));
  strcpy(mw->description, GET_INFO_PRINT(ISELECT));

  mw->sgame = 0;
  mw->cgame = COUNT_GAME;
  strcpy(mw->games[INDEX_FIRST_GAME], GET_INFO_PRINT(ITNAME));
  strcpy(mw->games[INDEX_SECOND_GAME], GET_INFO_PRINT(ISNAME));

  mw->sinfo = 0;
  mw->cinfo = COUNT_INFO;
  strcpy(mw->info[0], GET_INFO_PRINT(ISTART));
  strcpy(mw->info[1], GET_INFO_PRINT(ITNAME));
  strcpy(mw->info[2], GET_INFO_PRINT(ISNAME));
  strcpy(mw->info[3], GET_INFO_PRINT(IEXIT));

  mw->vertical = true;
  mw->centered = true;
  return true;
}