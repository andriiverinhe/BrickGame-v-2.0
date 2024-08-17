/**
 * @file SignalProcessing.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file with the signals of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SignalProcessing.h"

/**
 * @brief Get the signal object
 *
 * @param signal User input signal
 * @return UserAction_t
 */
UserAction_t get_signal(int signal) {
  UserAction_t action = (UserAction_t)-1;

  switch (signal) {
    case KEY_SPACE:
      action = Action;
      break;
    case KEY_LEFT_B:
      action = Left;
      break;
    case KEY_RIGHT_B:
      action = Right;
      break;
    case KEY_UP_B:
      action = Up;
      break;
    case KEY_DOWN_B:
      action = Down;
      break;

    case KEY_ENTER1:
    case KEY_ENTER2:
      action = Start;
      break;
    case KEY_PAUSE_LOWER:
    case KEY_PAUSE_UPPER:
      action = Pause;
      break;
    case KEY_EXIT_BT:
      action = Terminate;
      break;

    default:
      break;
  }

  return action;
}