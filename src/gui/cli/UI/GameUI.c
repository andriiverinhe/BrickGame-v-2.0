/**
 * @file GameUI.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief A file that describes the interface
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GameUI.h"

#include <string.h>

static void getSizeText(SizeText *sizeText, const int win);
static void drawBoardInfo(const SizeText *sizeText);
static int getPositionDrawInfoX(const char *str, const SizeText *sizeText);
static void drawTextPause(const SizeText *sizeText);
static void drawTextStart(const SizeText *sizeText, const char *gameName);
static void drawTextExit(const SizeText *sizeText, const char *gameName,
                         const GameInfo_t gameInfo);
static void drawUIField(int **field, WINDOW *win);
void drawUIBoard(WINDOW *win, const size_t x, const size_t y,
                 const size_t width, const size_t height);
static void drawNext(GameInfo_t *gameInfo, WINDOW *win);
static void drawUIInfo(const char *gameName, GameInfo_t *gameInfo, WINDOW *win);
static Color getColor(const int ind);
static void clearWinLine(WINDOW *win, const int x, const int y, const int end);

/**
 * @brief Initialize color pairs for curses.
 *
 * This function initializes color pairs for curses. It enables the use of
 * colors in the terminal window.
 *
 */
void initColor() {
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_CYAN);
  init_pair(4, COLOR_BLACK, COLOR_RED);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(6, COLOR_BLACK, COLOR_GREEN);
  init_pair(7, COLOR_RED, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_YELLOW);
  init_pair(9, COLOR_BLACK, COLOR_BLUE);
  init_pair(10, COLOR_GREEN, COLOR_BLACK);
}

/**
 * @brief Initialize the command-line interface (CLI).
 *
 * This function initializes the command-line interface (CLI) using the curses
 * library. It sets up the necessary configurations for curses, such as colors,
 * cursor visibility, echoing, and keypad input.
 *
 */
void initCli() {
  initscr();
  initColor();

  curs_set(0);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
}

/**
 * @brief Delete the command-line interface (CLI).
 *
 * This function clears the screen, refreshes it, and closes the curses library.
 */
void delCli() {
  clear();
  refresh();
  endwin();
}

/**
 * @brief Get the size of the text window.
 *
 * This function calculates the height, width, y-coordinate, and x-coordinate
 * of the text window based on the specified window identifier.
 *
 * @param sizeText Pointer to the SizeText structure where the size information
 * will be stored.
 * @param win The window identifier.
 *   WIN_PAUSE: Pause window.
 *   WIN_START: Start window.
 *   WIN_EXIT: Exit window.
 *   WIN_FIELD: Field window.
 */
static void getSizeText(SizeText *sizeText, const int win) {
  int height, width;
  GETMAXWH(height, width)

  if (WIN_PAUSE == win) {
    sizeText->height = HEIGHT_WIN_PAUSE;
    sizeText->width = WIDTH_WIN_PAUSE;
  }
  if (WIN_START == win) {
    sizeText->height = HEIGHT_WIN_START;
    sizeText->width = WIDTH_WIN_START;
  }
  if (WIN_EXIT == win) {
    sizeText->height = HEIGHT_WIN_EXIT;
    sizeText->width = WIDTH_WIN_EXIT;
  }
  if (WIN_FIELD == win) {
    sizeText->height = WINDOW_FIELD_HEIGHT;
    sizeText->width = WINDOW_FIELD_WIDTH;
  }

  sizeText->y = (height - sizeText->height) / 2;
  sizeText->x = (width - sizeText->width) / 2;
}

/**
 * @brief Initialize windows.
 *
 * This function creates and initializes the field window and the information
 * window.
 *
 * @param fieldW Pointer to a pointer to the field window.
 * @param infoW Pointer to a pointer to the information window.
 *
 */
bool initWindow(WINDOW **fieldW, WINDOW **infoW) {
  if (!fieldW || !infoW) return false;
  SizeText SizeText = {0};

  getSizeText(&SizeText, WIN_FIELD);

  int halfField = (WINDOW_FIELD_WIDTH) / 2;
  (*fieldW) = newwin(WINDOW_FIELD_HEIGHT, WINDOW_FIELD_WIDTH, SizeText.y,
                     SizeText.x - halfField);
  (*infoW) = newwin(WINDOW_FIELD_HEIGHT, WINDOW_FIELD_WIDTH, SizeText.y,
                    SizeText.x + halfField);

  return ((*fieldW) != NULL && (*infoW) != NULL);
}

/**
 * @brief Delete a window.
 *
 * This function deletes the specified window.
 *
 * @param win Pointer to the window to delete.
 *
 */
void deleteWindow(WINDOW **win) {
  if (!win || !CHECK_WIN(*win)) return;

  werase(*win);
  delwin(*win);
  clear();
}

/**
 * @brief Draw the board info.
 *
 * This function draws the board info box using ASCII characters.
 *
 * @param sizeText Pointer to the SizeText structure containing the dimensions
 * and position of the box.
 *
 * @return void
 */
static void drawBoardInfo(const SizeText *sizeText) {
  attron(A_BOLD);
  attron(COLOR_PAIR(WHITE_BLACK));
  const int x = sizeText->x;
  const int y = sizeText->y;
  const int height = sizeText->height;
  const int width = sizeText->width;

  mvhline(y - SIZE_BOX, x - SIZE_BOX, ACS_HLINE, width + 2);
  mvhline(y + height, x - SIZE_BOX, ACS_HLINE, width + 2);
  mvvline(y, x - SIZE_BOX, ACS_VLINE, height);
  mvvline(y, x + width, ACS_VLINE, height);
  mvaddch(y - SIZE_BOX, x - SIZE_BOX, ACS_ULCORNER);
  mvaddch(y - SIZE_BOX, x + width, ACS_URCORNER);
  mvaddch(y + height, x - SIZE_BOX, ACS_LLCORNER);
  mvaddch(y + height, x + width, ACS_LRCORNER);

  attroff(A_BOLD);
}

/**
 * @brief Get the X-coordinate for drawing info text.
 *
 * This function calculates the X-coordinate for drawing info text based on the
 * width of the box and the length of the text.
 *
 * @param str The info text string.
 * @param sizeText Pointer to the SizeText structure containing the dimensions
 * and position of the box.
 *
 * @return int The X-coordinate for drawing the info text.
 */
static int getPositionDrawInfoX(const char *str, const SizeText *sizeText) {
  return (sizeText->x + sizeText->width / 2 - strlen(str) / 2);
}

/**
 * @brief Draw the pause text.
 *
 * This function draws the pause text in the middle of the pause window.
 *
 * @param sizeText Pointer to the SizeText structure containing the dimensions
 * and position of the pause window.
 */
static void drawTextPause(const SizeText *sizeText) {
  const char *pausestr = GET_INFO_PRINT(IPAUSE);
  mvprintw(sizeText->y + DRAW_POS_Y1, getPositionDrawInfoX(pausestr, sizeText),
           "%s", pausestr);
}

/**
 * @brief Draw the start text.
 *
 * This function draws the start text in the middle of the start window.
 *
 * @param sizeText Pointer to the SizeText structure containing the dimensions
 * and position of the pause window.
 */
static void drawTextStart(const SizeText *sizeText, const char *gameName) {
  const char *namebg = GET_INFO_PRINT(INAMEBG);
  // const char *name = GET_INFO_PRINT(INAME);
  const char *enterp = GET_INFO_PRINT(IPRESSENTER);
  const char *escp = GET_INFO_PRINT(IPRESSESC);

  mvprintw(sizeText->y + DRAW_POS_Y1, getPositionDrawInfoX(namebg, sizeText),
           "%s", namebg);
  mvprintw(sizeText->y + DRAW_POS_Y2, getPositionDrawInfoX(gameName, sizeText),
           "%s", gameName);
  mvprintw(sizeText->y + DRAW_POS_Y3, getPositionDrawInfoX(enterp, sizeText),
           "%s", enterp);
  mvprintw(sizeText->y + DRAW_POS_Y4, getPositionDrawInfoX(escp, sizeText),
           "%s", escp);
}

/**
 * @brief Draw the exit text.
 *
 * This function draws the exit text in the middle of the exit window.
 *
 * @param sizeText Pointer to the SizeText structure containing the dimensions
 * and position of the pause window.
 * @param gameInfo Pointer to the GameInfo_t structure containing the game
 * information.
 */
static void drawTextExit(const SizeText *sizeText, const char *gameName,
                         const GameInfo_t gameInfo) {
  const char *state = GET_INFO_PRINT(ILOSE);
  if (strcmp(gameName, (char *)GET_INFO_PRINT(ISNAME)) == 0)
    if (gameInfo.score >= (int)MAX_CELLS) state = GET_INFO_PRINT(IWIN);

  const char *score = GET_INFO_PRINT(ISCORE);
  const char *level = GET_INFO_PRINT(ILEVEL);
  const char *exorres = GET_INFO_PRINT(IEXITORREST);

  mvprintw(sizeText->y + DRAW_POS_Y1, getPositionDrawInfoX(state, sizeText),
           "%s", state);
  mvprintw(sizeText->y + DRAW_POS_Y2, getPositionDrawInfoX(score, sizeText),
           "%s%d", score, gameInfo.score);
  mvprintw(sizeText->y + DRAW_POS_Y3, getPositionDrawInfoX(level, sizeText),
           "%s%d", level, gameInfo.level);
  mvprintw(sizeText->y + DRAW_POS_Y4, getPositionDrawInfoX(exorres, sizeText),
           "%s", exorres);
}

/**
 * @brief Print info.
 *
 * This function prints game information.
 *
 * @param win The window that will be drawn.
 * @param gameName Name game.
 * @param gameInfo Pointer to the GameInfo_t structure containing information
 * about the game.
 */
void printInfoWindow(int win, const char *gameName, const GameInfo_t gameInfo) {
  if (win != WIN_PAUSE) clear();
  SizeText sizeText = {0};
  getSizeText(&sizeText, win);

  if (win == WIN_PAUSE) drawTextPause(&sizeText);
  if (win == WIN_START) drawTextStart(&sizeText, gameName);
  if (win == WIN_EXIT) drawTextExit(&sizeText, gameName, gameInfo);

  drawBoardInfo(&sizeText);

  refresh();
}

/**
 * @brief Get the Color object
 *
 * @param ind index color
 * @return Color
 */
static Color getColor(const int ind) {
  Color color = WHITE_BLACK;

  switch (ind) {
    case 1:
      color = BLACK_MAGENTA;
      break;
    case 2:
      color = BLACK_GREEN;
      break;
    case 3:
    case ST_CODE_FRUIT:
      color = BLACK_RED;
      break;
    case 4:
      color = BLACK_YELLOW;
      break;
    case 5:
      color = BLACK_BLUE;
      break;
    case 6:
    case ST_CODE_SNAKE:
      color = BLACK_CYAN;
      break;
    case 7:
      color = BLACK_WHITE;
      break;
    default:
      color = WHITE_BLACK;
      break;
  }
  return color;
}

/**
 * @brief Draw the game field in the specified window.
 *
 * This function draws the game field in the specified window.
 *
 * @param field The game field to be drawn.
 * @param win The window where the game field will be drawn.
 */
static void drawUIField(int **field, WINDOW *win) {
  if (CHECK_FIELD(field) && CHECK_WIN(win)) {
    DRAW_BOX(win)
    COLOR_BOX(win, BLACK_MAGENTA)

    for (size_t i = 0; i < HFIELD; i++)
      for (size_t j = 0; j < WFIELD; j++) {
        SET_COLOR_PAIR(win, getColor(field[i][j]))
        DRAW_CELL(j, i + SIZE_BOX, win);
      }
  }
}

/**
 * @brief Draw a board in the specified window.
 *
 * This function draws a rectangular board.
 *
 * @param win The window in which the board will be drawn.
 * @param x The initial x-coordinate of the board.
 * @param y The initial y-coordinate of the board.
 * @param width The width of the board.
 * @param height The height of the board.
 */
void drawUIBoard(WINDOW *win, const size_t x, const size_t y,
                 const size_t width, const size_t height) {
  for (size_t i = x; i < (x + width + 1); i++) {
    if (i == x) {
      mvwaddch(win, y, i, ACS_ULCORNER);
      mvwaddch(win, y + height - 1, i, ACS_LLCORNER);
    } else if (i == (x + width)) {
      mvwaddch(win, y, i, ACS_URCORNER);
      mvwaddch(win, y + height - 1, i, ACS_LRCORNER);
    } else {
      mvwaddch(win, y, i, ACS_HLINE);
      mvwaddch(win, y + height - 1, i, ACS_HLINE);
    }
  }

  for (size_t i = y + 1; i < (y + height - 1); i++) {
    mvwaddch(win, i, x, ACS_VLINE);
    mvwaddch(win, i, x + width, ACS_VLINE);
  }

  size_t draw_x = x + 1;
  size_t draw_y = y + 1;
  for (size_t i = 0; i < height - 2; i++) {
    for (size_t j = 0; j < width - 1; j++) {
      mvwaddch(win, draw_y, draw_x++, ' ');
    }
    draw_x -= width - 1;
    draw_y++;
  }
}

/**
 * @brief Draw the next model preview board.
 *
 * This function draws the next model preview board in the specified window.
 *
 * @param gameInfo Pointer to the GameInfo_t structure containing game
 * information.
 * @param win The window where the next model preview board will be drawn.
 */
static void drawNext(GameInfo_t *gameInfo, WINDOW *win) {
  SET_COLOR_PAIR(win, WHITE_BLACK);
  drawUIBoard(win, START_X_BOAR, START_Y_BOAR, WIDTH_BOARD_NEXT,
              HEIGHT_BOARD_NEXT);
  mvwprintw(win, 4, 9, GET_INFO_PRINT(INEXT));

  size_t draw_x = START_X_BOAR;
  size_t draw_y = START_Y_BOAR * 2;

  SET_COLOR_PAIR(win, BLACK_MAGENTA);

  if (!gameInfo->next) return;
  for (size_t i = 0; i < HNEXT; i++, draw_x -= WNEXT, draw_y++) {
    for (size_t j = 0; j < WNEXT; j++, draw_x++) {
      if (gameInfo->next[i][j] == true) {
        DRAW_CELL(draw_x, draw_y, win)
      }
    }
  }
}

/**
 * @brief Clears a line in a window.
 *
 * @param win The window to clear the line in.
 * @param x The starting position of the line to clear.
 * @param y The y-coordinate of the line to clear.
 * @param end The ending position of the line to clear.
 */
static void clearWinLine(WINDOW *win, const int x, const int y, const int end) {
  if (win)
    for (int i = x; i < end; i++) mvwaddch(win, y, i, ' ');
}

/**
 * @brief Draw the game information board.
 *
 * This function draws the game information board, including high score, current
 * score, and level, as well as the preview of the next model in the specified
 * window.
 *
 * @param gameInfo Pointer to the GameInfo_t structure containing game
 * information.
 * @param win The window where the game information board will be drawn.
 */
static void drawUIInfo(const char *gameName, GameInfo_t *gameInfo,
                       WINDOW *win) {
  DRAW_BOX(win)
  COLOR_BOX(win, BLACK_MAGENTA)
  COLOR_TEXT(win, BLACK_MAGENTA)

  mvwprintw(win, 2, 8, "%s", gameName);
  clearWinLine(win, 2, 10, WINDOW_FIELD_WIDTH - 1);
  mvwprintw(win, 10, 2, "%s%d ", GET_INFO_PRINT(IHIGH_SCORE),
            gameInfo->high_score);
  clearWinLine(win, 2, 12, WINDOW_FIELD_WIDTH - 1);
  mvwprintw(win, 12, 2, "%s%d ", GET_INFO_PRINT(ISCORE), gameInfo->score);
  clearWinLine(win, 2, 14, WINDOW_FIELD_WIDTH - 1);
  mvwprintw(win, 14, 2, "%s%d ", GET_INFO_PRINT(ILEVEL), gameInfo->level);

  drawNext(gameInfo, win);
}

/**
 * @brief Refresh the user interface windows.
 *
 * This function refreshes the game field window and the game information
 * window.
 *
 * @param gameName Name game.
 * @param gameInfo The current game information.
 * @param gameWin The struct window.
 */
void refreshUIWin(const char *gameName, GameInfo_t gameInfo,
                  GameWindows *gameWin) {
  if (!gameWin || !gameWin->fieldw || !gameWin->infow) return;

  if (gameWin->infoDraw == true) {
    gameWin->infoDraw = false;
    clear();
    refresh();
  }

  drawUIField(gameInfo.field, gameWin->fieldw);
  drawUIInfo(gameName, &gameInfo, gameWin->infow);

  refresh();
  if (gameWin->fieldw) wrefresh(gameWin->fieldw);
  if (gameWin->infow) wrefresh(gameWin->infow);
}

/**
 * @brief Initialize the game windows.
 *
 * This function initializes the game windows and sets the infoDraw flag to
 * false.
 *
 * @param gameWin Pointer to the game windows structure.
 * @return true if initialization is successful, false otherwise.
 */
bool initGameWindow(GameWindows *gameWin) {
  if (!gameWin) return false;
  gameWin->infoDraw = false;
  return initWindow(&gameWin->fieldw, &gameWin->infow);
}

/**
 * @brief Free the memory allocated for game windows.
 *
 * This function frees the memory allocated for the game windows.
 *
 * @param gameWin Pointer to the game windows structure.
 */
void freeGameWindow(GameWindows *gameWin) {
  if (!gameWin) return;
  deleteWindow(&gameWin->fieldw);
  deleteWindow(&gameWin->infow);
}

/**
 * @brief Draw the appropriate information window based on the game state.
 *
 * This function draws the information window based on the current game state
 * and game information.
 *
 * @param state The current state of the game.
 * @param gameInfo The game information.
 */
static void infoDrawf(const char *gameName, const char *addition,
                      GameInfo_t gameInfo) {
  int win = -1;

  if (strcmp(addition, GET_INFO_PRINT(ISSTART)) == 0)
    win = WIN_START;
  else if (strcmp(addition, GET_INFO_PRINT(ISEND)) == 0)
    win = WIN_EXIT;
  else if (gameInfo.pause)
    win = WIN_PAUSE;

  printInfoWindow(win, gameName, gameInfo);
}

/**
 * @brief Update function for the game state.
 *
 * This function updates the game state and refreshes the user interface window
 * accordingly.
 *
 * @param gameName Game name.
 * @param gameWin Pointer to the game windows.
 * @param gameInfo The game information.
 * @param addition The game addition information.
 */
void update(const char *gameName, GameWindows *gameWin, GameInfo_t gameInfo,
            const char *addition) {
  if (!gameWin) return;
  if (strcmp(addition, GET_INFO_PRINT(ISNOT)) == 0 && !gameInfo.pause) {
    refreshUIWin(gameName, gameInfo, gameWin);
  } else {
    if (gameWin->infoDraw == false) {
      infoDrawf(gameName, addition, gameInfo);
      gameWin->infoDraw = true;
    }
  }
}