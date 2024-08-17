/**
 * @file State.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source File with game state.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "State.h"

/**
 * @brief Checks if the game state represents an informational state.
 *
 * @param state The game state to check.
 * @return true if the state is either START or GAME_OVER, false otherwise.
 */
bool isInfoState(GameState_t state) {
  return (state == START || state == GAMEOVER);
}

/**
 * @brief Checks if the game state represents a gaming state.
 *
 * @param state The game state to check.
 * @return true if the state is between SPAWN and SHIFTING (inclusive), false
 * otherwise.
 */
bool isGamingState(GameState_t state) {
  return (state == SPAWN || state == MOVE || state == COLLISION ||
          state == SHIFT);
}

/**
 * @brief Checks if the game state represents a gaming state without user input.
 *
 * @param state The game state to check.
 * @return true if the state is either SPAWN, SHIFT, or COLLIDE, false
 * otherwise.
 */
bool isGamingStateWithoutKey(GameState_t state) {
  return (state == SPAWN || state == SHIFT || state == COLLISION);
}

/**
 * @brief Converts a game state to a string representation.
 *
 * This function takes a `GameState_t` enum value as input and returns a string
 * representation of the state. The function uses a switch statement to
 * determine which string to return based on the input state.
 *
 * @param state The game state to convert to a string representation.
 * @return char* A pointer to a string representing the game state.
 */
char *convertStateToStrInf(GameState_t state) {
  char *str = "\0";
  switch (state) {
    case START:
      str = DS_Start;
      break;
    case GAMEOVER:
      str = DS_End;
      break;
    default:
      str = DS_Not;
      break;
  }
  return str;
}
