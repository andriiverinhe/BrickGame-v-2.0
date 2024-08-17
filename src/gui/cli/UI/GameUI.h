/**
 * @file GameUI.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief A file that describes the interface
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

#include <ncurses.h>

#include "../../../brick_game/common/Info/Info.h"

/**
 * @defgroup UI User Interface Macros
 * @brief Collection of macros for ui parameters and accessors.
 * @{
 */

#define MAX_CELLS 200                  /**< Max count cells */
#define WINDOW_FIELD_HEIGHT HFIELD + 2 /**< Window field height */
#define HEIGHT_BOARD_NEXT 6            /**< Height of the `Board Next` */
#define HEIGHT_WIN_PAUSE 3             /**< Height of the `pause window` */
#define HEIGHT_WIN_START 9             /**< Height of the `start window` */
#define HEIGHT_WIN_EXIT 9              /**< Height of the `exit window` */

#define WINDOW_FIELD_WIDTH WFIELD * 2 + 2 /**< Window field width */
#define WIDTH_BOARD_NEXT 15               /**< Width of the `Board Next` */
#define WIDTH_WIN_PAUSE 40                /**< Width of the `pause window` */
#define WIDTH_WIN_START 45                /**< Width of the `start window` */
#define WIDTH_WIN_EXIT 40                 /**< Width of the `exit window` */

#define WIN_PAUSE 0 /**< Pause window code */
#define WIN_START 1 /**< Start window code */
#define WIN_EXIT 2  /**< Exit window code */
#define WIN_FIELD 3 /**< Field window code */
#define SIZE_BOX 1  /**< Thickness box */

#define DRAW_POS_Y1 1 /**< First y-axis cordinate for drawing*/
#define DRAW_POS_Y2 3 /**< Second y-axis cordinate for drawing*/
#define DRAW_POS_Y3 5 /**< Third y-axis cordinate for drawing*/
#define DRAW_POS_Y4 7 /**< Fourth cordinate on the y-axis for drawing*/

#define START_X_BOAR \
  3 /**< Initial x-axis position for drawing the frame for the next shape */
#define START_Y_BOAR \
  3 /**< Initial y-axis position for drawing the frame for the next shape */

/**
 * @brief Macro to return the first position of the square on the window
 * @param x current position in the field array
 * @return The first position of the part square
 */
#define GET_POS_X1(x) x * 2 + 1

/**
 * @brief Macro to return the second position of the square in the window
 * @param x current position in the field array
 * @return second position of a part of the square
 */
#define GET_POS_X2(x) GET_POS_X1(x) + 1

/**
 * @brief Macro to get terminal dimensions
 * @param width variable to record the width
 * @param height variable to record the height
 */
#define GETMAXWH(height, width) getmaxyx(stdscr, height, width);
/**
 * @brief Macro for setting window color pair
 * @param win The window in which the color will be set
 * @param index Color pair index
 */
#define SET_COLOR_PAIR(win, index) wbkgdset(win, COLOR_PAIR(index));

#define CHECK_WIN(win) (win != NULL)       /**< Checking the window for NULL*/
#define CHECK_FIELD(field) (field != NULL) /**< Checking the field for NULL*/

/**
 * @brief Macro for drawing a box
 * @param win drawing window
 */
#define DRAW_BOX(win) box(win, 0, 0);

/**
 * @brief Macro for setting box color pair
 * @param win The box in which the color will be set
 * @param index Color pair index
 */
#define COLOR_BOX(win, index) wbkgd(win, COLOR_PAIR(index));

/**
 * @brief Macro for setting text color pair
 * @param win The box in which the color will be set
 * @param index Color pair index
 */
#define COLOR_TEXT(win, index) wattron(win, COLOR_PAIR(index));

/**
 * @brief Macro for inserting a square
 * @param win The window in which the square will be installed
 * @param x x position from the field
 * @param y y position from the field
 */
#define DRAW_CELL(x, y, win)            \
  mvwaddch(win, y, GET_POS_X1(x), ' '); \
  mvwaddch(win, y, GET_POS_X2(x), ' ');

/**
 * @brief The macro returns the text according to the index, indices from the
 * `INDEX_TEXT_INFO` enumeration.
 */
#define GET_INFO_PRINT(index)                                             \
  (((index) == ITNAME)        ? "TETRIS"                                  \
   : ((index) == ISNAME)      ? "SNAKE"                                   \
   : ((index) == IHIGH_SCORE) ? "HIGH SCORE: "                            \
   : ((index) == ISCORE)      ? "SCORE: "                                 \
   : ((index) == ILEVEL)      ? "LEVEL: "                                 \
   : ((index) == INEXT)       ? "NEXT"                                    \
   : ((index) == IPAUSE)      ? "PAUSE"                                   \
   : ((index) == INAMEBG)     ? "Brick Games"                             \
   : ((index) == IPRESSENTER) ? "START Game press <Enter>"                \
   : ((index) == IPRESSESC)   ? "EXIT Game press <q>"                     \
   : ((index) == ILOSE)       ? "You lose"                                \
   : ((index) == IWIN)        ? "You Win"                                 \
   : ((index) == IEXITORREST) ? "Press <q> to exit or <ENTER> to restart" \
   : ((index) == ISTART)      ? "START"                                   \
   : ((index) == IEXIT)       ? "EXIT"                                    \
   : ((index) == ISELECT)     ? "SELECT THE GAME AND THEN CLICK START"    \
   : ((index) == ISSTART)     ? "start"                                   \
   : ((index) == ISEND)       ? "end"                                     \
   : ((index) == ISNOT)       ? "not"                                     \
                              : NULL)

/**
 * @}
 */

/**
 * @brief Enumeration to get the text to display information in the window.
 */
typedef enum {
  ITNAME = 0,       /**< Game name - `TETRIS`*/
  ISNAME = 1,       /**< Game name - `SNAKE`*/
  IHIGH_SCORE = 2,  /**< High Score - `HIGH SCORE: ` */
  ISCORE = 3,       /**< Score - `SCORE: ` */
  ILEVEL = 4,       /**< Level - `LEVEL: ` */
  INEXT = 5,        /**< Next - `NEXT` */
  IPAUSE = 6,       /**< Pause - `PAUSE` */
  INAMEBG = 7,      /**< Brick Game text - `Brick Games` */
  IPRESSENTER = 8,  /**< Press enter - `START Game press <Enter>` */
  IPRESSESC = 9,    /**< Press esc - `EXIT Game press <ESC>` */
  ILOSE = 10,       /**< Lose info - `You lose` */
  IWIN = 11,        /**< Win info - `You win` */
  IEXITORREST = 12, /**< ent or esc - `Press ESC to exit or ENTER to restart` */
  ISTART = 13,      /**< String - `START` */
  IEXIT = 14,       /**< String - `EXIT` */
  ISELECT = 15,     /**< String - `SELECT THE GAME AND THEN CLICK START` */
  ISSTART = 16,     /**< String - `start` */
  ISEND = 17,       /**< String - `end` */
  ISNOT = 18        /**< String - `not` */
} INDEX_TEXT_INFO;

/**
 * @brief Enumeration of color indices
 */
typedef enum {
  BLACK_MAGENTA = 1, /**< `Text` - Black, `Bakcground` - Magenta*/
  WHITE_BLACK = 2,   /**< `Text` - White, `Bakcground` - Black  */
  BLACK_CYAN = 3,    /**< `Text` - Black, `Bakcground` - Cyan   */
  BLACK_RED = 4,     /**< `Text` - Black, `Bakcground` - Red    */
  BLACK_WHITE = 5,   /**< `Text` - Black, `Bakcground` - White  */
  BLACK_GREEN = 6,   /**< `Text` - Black, `Bakcground` - Green  */
  RED_BLACK = 7,     /**< `Text` - Red,   `Bakcground` - Black  */
  BLACK_YELLOW = 8,  /**< `Text` - Black, `Bakcground` - Yellow */
  BLACK_BLUE = 9,    /**< `Text` - Black, `Bakcground` - Blue   */
  GREEN_BLACK = 10   /**< `Text` - Green, `Bakcground` - Black  */
} Color;

/**
 * @brief Structure for displaying terminal information
 */
typedef struct {
  int height; /**< Terminal height */
  int width;  /**< Terminal width */

  int y; /**< Center on `y` */
  int x; /**< Center on `x` */
} SizeText;

/**
 * @brief Structure representing game windows.
 *
 * This structure contains pointers to the game field window and the game info
 * window, as well as a boolean flag indicating whether the info window has been
 * drawn.
 */
typedef struct {
  bool infoDraw; /**< Flag indicating whether the info window has been drawn. */
  WINDOW *fieldw; /**< Pointer to the game field window. */
  WINDOW *infow;  /**< Pointer to the game info window. */
} GameWindows;

void initCli();
void initColor();
bool initWindow(WINDOW **fieldW, WINDOW **infoW);
bool initGameWindow(GameWindows *gameWin);

void delCli();
void deleteWindow(WINDOW **win);
void freeGameWindow(GameWindows *gameWin);

void printInfoWindow(int win, const char *gameName, const GameInfo_t gameInfo);
void refreshUIWin(const char *gameName, GameInfo_t gameInfo,
                  GameWindows *gameWin);

void update(const char *gameName, GameWindows *gameWin, GameInfo_t gameInfo,
            const char *addition);

#ifdef __cplusplus
}
#endif