/**
 * @file TetrisController.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file Tetris Controller
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "TetrisController.hpp"

#include "Helpers.hpp"
namespace s21 {

/**
 * @brief The constructor for TetrisController.
 *
 * @param model The game model.
 * @param view The game view.
 * @param parent The parent object.
 */
TetrisController::TetrisController(GameTetris *model, GameView *view,
                                   QObject *parent)
    : QBaseGameController(parent), model_(model), view_(view) {
  action_ = (UserAction_t)-1;
  connect(timer_output, &QTimer::timeout, this, &TetrisController::updateView);
  connect(timer_input, &QTimer::timeout, this,
          &TetrisController::sendInputSignal);
  connect(view, &GameView::userActionReceived, this,
          &TetrisController::onUserActionReceived);
  view->setGameSelected(NGAME_TETRIS);
}

/**
 * @brief Runs the Tetris game controller.
 */
void TetrisController::run() {
  reset(model_, START);
  timer_input->start(0);
  timer_output->start(0);
}

/**
 * @brief Stops the Tetris game controller.
 */
void TetrisController::stop() {
  timer_input->stop();
  timer_output->stop();
}

/**
 * @brief Updates the game view.
 */
void TetrisController::updateView() {
  this->view_->updateGameInfo(updateCurrentState(),
                              (QString)convertStateToStrInf(model_->state));
  if (model_->state == EXIT) {
    this->stop();
    emit finished();
  }
}

/**
 * @brief Sends an input signal to the game controller.
 */
void TetrisController::sendInputSignal() {
  userInput(action_, false);
  action_ = (UserAction_t)-1;
}

/**
 * @brief Handles a user action received event for the Tetris game controller.
 */
void TetrisController::onUserActionReceived(const QKeyEvent *event) {
  action_ = QKeyEventToUserAction(event);
}
}  // namespace s21