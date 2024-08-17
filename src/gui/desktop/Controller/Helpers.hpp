/**
 * @file Helpers.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Auxiliary file for the controller
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <QKeyEvent>

#include "../../../brick_game/common/Action/Action.h"
namespace s21 {
UserAction_t QKeyEventToUserAction(const QKeyEvent *event);
}