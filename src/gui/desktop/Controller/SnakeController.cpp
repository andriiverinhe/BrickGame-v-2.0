/**
 * @file SnakeController.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file Snake Controller
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SnakeController.hpp"

#include "Helpers.hpp"
namespace s21 {
/**
 * @brief The constructor for SnakeController.
 *
 * @param model The game model.
 * @param view The game view.
 * @param parent The parent object.
 */
SnakeController::SnakeController(GameSnake *model, GameView *view,
                                 QObject *parent)
    : QBaseGameController(parent), model_(model), view_(view) {
  action_ = (UserAction_t)-1;
  connect(timer_output, &QTimer::timeout, this, &SnakeController::updateView);
  connect(timer_input, &QTimer::timeout, this,
          &SnakeController::sendInputSignal);
  connect(view, &GameView::userActionReceived, this,
          &SnakeController::onUserActionReceived);
  view->setGameSelected(QString(NGAME_SNAKE.c_str()));
}

/**
 * @brief Runs the Snake game controller.
 */
void SnakeController::run() {
  model_->reset(START);
  timer_input->start(0);
  timer_output->start(0);
}

/**
 * @brief Stops the Snake game controller.
 */
void SnakeController::stop() {
  timer_input->stop();
  timer_output->stop();
}

/**
 * @brief Updates the game view.
 */
void SnakeController::updateView() {
  view_->updateGameInfo(model_->updateCurrentState(),
                        (QString)convertStateToStrInf(model_->getState()));

  if (model_->getState() == EXIT) {
    this->stop();
    emit finished();
  }
}

/**
 * @brief Sends an input signal to the game controller.
 */
void SnakeController::sendInputSignal() {
  this->model_->userInput(action_, false);
  action_ = (UserAction_t)-1;
}

/**
 * @brief Handles a user action received event for the Snake game controller.
 */
void SnakeController::onUserActionReceived(const QKeyEvent *event) {
  action_ = QKeyEventToUserAction(event);
}
}  // namespace s21