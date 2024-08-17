/**
 * @file Helpers.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Auxiliary file for the controller
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Helpers.hpp"

namespace s21 {

/**
 * @brief Converts a QKeyEvent to a UserAction_t.
 *
 * @param event The QKeyEvent to convert.
 *
 * @return The converted UserAction_t.
 */
UserAction_t QKeyEventToUserAction(const QKeyEvent *event) {
  UserAction_t action = (UserAction_t)-1;
  switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:
      action = Up;
      break;
    case Qt::Key_S:
    case Qt::Key_Down:
      action = Down;
      break;
    case Qt::Key_A:
    case Qt::Key_Left:
      action = Left;
      break;
    case Qt::Key_D:
    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Space:
      action = Action;
      break;
    case Qt::Key_P:
    case Qt::Key_Pause:
      action = Pause;
      break;
    case Qt::Key_Escape:
      action = Terminate;
      break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
      action = Start;
      break;
    default:
      action = (UserAction_t)-1;
      break;
  }
  return action;
}
}  // namespace s21