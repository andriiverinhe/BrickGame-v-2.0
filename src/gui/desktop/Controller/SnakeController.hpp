/**
 * @file SnakeController.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file Snake Controller
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../../../brick_game/snake/GameSnake.hpp"
#include "../View/GameView.hpp"
#include "QBaseController.hpp"
namespace s21 {

/**
 * @brief A controller for the Snake game.
 */
class SnakeController : public QBaseGameController {
  Q_OBJECT

 protected:
  GameSnake *model_;    /**< Game model */
  GameView *view_;      /**< Game view */
  UserAction_t action_; /**< User input action */

 public:
  explicit SnakeController(GameSnake *model, GameView *view,
                           QObject *parent = nullptr);

  ~SnakeController() = default;
  void run() override;
  void stop() override;

 public slots:
  void updateView() override;
  void sendInputSignal() override;
  void onUserActionReceived(const QKeyEvent *event) override;
};
}  // namespace s21