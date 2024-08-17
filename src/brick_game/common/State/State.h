/**
 * @file State.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header File with game state.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define DS_Start "start" /**< String: `start` */
#define DS_End "end"     /**< String: `end` */
#define DS_Not "not"     /**< String: `not` */

/**
 * @brief @brief Defines an enumeration of game states.
This enumeration represents the different states that a game can be in.
 */
typedef enum {
  START,     /**< State START */
  SPAWN,     /**< State SPAWN */
  MOVE,      /**< State MOVE */
  SHIFT,     /**< State SHIFT */
  COLLISION, /**< State COLLISION */
  GAMEOVER,  /**< State GAMEOVER */
  PAUSE,     /**< State PAUSE */
  EXIT       /**< State EXIT */
} GameState_t;

bool isInfoState(GameState_t state);
bool isGamingState(GameState_t state);
bool isGamingStateWithoutKey(GameState_t state);
char *convertStateToStrInf(GameState_t state);

#ifdef __cplusplus
}
#endif