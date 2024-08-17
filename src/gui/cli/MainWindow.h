/**
 * @file MainWindow.h
 * @author nenamaxi(an.veringe@gmail.com)
 * @brief Header file Mainwindow
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../../brick_game/common/Signal/SignalProcessing.h"

#define MENU_HEIGHT 20 /**< Menu Height */
#define MENU_WIDTH 40  /**< Menu WIDTH */

#define BUFF_STR 256  /**< Size string */
#define BASE_COUNT 10 /**< Base count */

#define INDEX_FIRST_GAME 0  /**< Index of the first game */
#define INDEX_SECOND_GAME 1 /**< Index of the second game */
#define COUNT_GAME 2        /**< Number of games */
#define COUNT_INFO 4        /**< Number of info */

/**
 * @brief A structure holding information about a main window.
 */
typedef struct {
  char title[BUFF_STR]; /**< A character array holding the title of the main
                           window. */
  char description[BUFF_STR]; /**< A character array holding a description of
                                 the main window. */

  size_t sgame; /**< The select of a game in the array. */
  size_t cgame; /**< The count of games in the array. */
  char games[BASE_COUNT]
            [BUFF_STR]; /**< A character array holding the names of games. */

  size_t sinfo; /**< The select of an information item in the array. */
  size_t cinfo; /**< The count of information items in the array. */
  char info[BASE_COUNT]
           [BUFF_STR]; /**< A character array holding the information items. */

  bool vertical; /**< A flag indicating whether the window is displayed
                    vertically or not. */
  bool
      centered; /**< A flag indicating whether the window is centered or not. */
} Mainwindow;

bool launch(Mainwindow *menu);
bool initMainWindow(Mainwindow *mw);

#ifdef __cplusplus
}
#endif