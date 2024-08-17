/**
 * @file mainwindow.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file mainwindow desktop
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <QMainWindow>
#include <QString>

extern "C" {
#include "../../brick_game/common/Action/Action.h"
#include "../../brick_game/tetris/GameTetris.h"
}

#include "../../brick_game/snake/GameSnake.hpp"
#include "Controller/QBaseController.hpp"
#include "Controller/SnakeController.hpp"
#include "Controller/TetrisController.hpp"
#include "View/GameView.hpp"

namespace Ui {
class MainWindow;
}

namespace s21 {

constexpr int BT_WIDTH = 300; /**< Button width */
constexpr int BT_HEIGHT = 50; /**< Button height */

const QString NOT_STYLE = ""; /**< Without style */
/**
 * @brief  Button style
 */
const QString PRESSED_STYLE =
    "QPushButton {"
    "        background-color: #3a6cb1;"
    "        color: #282c34;"
    "        border: none;"
    "        border-radius: 10px;"
    "        padding: 10px;"
    "        font-size: 16px;"
    "}"
    "QPushButton:hover {"
    "        background-color: #61afef;"
    "}"
    "QPushButton:pressed {"
    "        background-color: #528bde;"
    "}";

/**
 * @brief The main window class for the game.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  void refreshFinishConnect(void);
  void setEnableMenu(bool enable);
  void createController();

 private slots:
  void on_PB_Start_clicked();
  void on_PB_Tetris_clicked();
  void on_PB_Snake_clicked();
  void on_PB_Exit_clicked();

  void isGameFinished();

 private:
  Ui::MainWindow *ui; /**< The user interface object. */

  QString game_select; /**< The selected game type. */

  s21::GameSnake *GSnake; /**< A pointer to the snake game object. */
  GameTetris *GTetris;    /**< A pointer to the Tetris game object. */

  GameView *View; /**< A pointer to the game view object. */
  QBaseGameController
      *controller; /**< A pointer to the base game controller object. */
};

}  // namespace s21