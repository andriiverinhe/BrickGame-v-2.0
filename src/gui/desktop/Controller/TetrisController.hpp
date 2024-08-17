/**
 * @file TetrisController.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file Tetris Controller
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "QBaseController.hpp"

extern "C" {
#include "../../../brick_game/tetris/GameTetris.h"
}
#include "../View/GameView.hpp"

namespace s21 {

/**
 * @brief A controller for the Tetris game.
 */
class TetrisController : public QBaseGameController {
  Q_OBJECT

 protected:
  GameTetris *model_;   /**< Game model */
  GameView *view_;      /**< Game view */
  UserAction_t action_; /**< User input action */

 public:
  explicit TetrisController(GameTetris *model, GameView *view,
                            QObject *parent = nullptr);
  ~TetrisController() = default;

  void run() override;
  void stop() override;

 public slots:
  void updateView() override;
  void sendInputSignal() override;
  void onUserActionReceived(const QKeyEvent *event) override;
};

}  // namespace s21