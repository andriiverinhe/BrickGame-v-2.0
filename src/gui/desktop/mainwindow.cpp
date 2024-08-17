/**
 * @file mainwindow.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file mainwindow desktop
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "mainwindow.hpp"

#include "ui_mainwindow.h"
namespace s21 {

/**
 * @brief The constructor for the main window.
 *
 * @param parent The parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      GSnake(new GameSnake()),
      GTetris(new GameTetris()),
      controller(nullptr),
      View(new GameView(this)),
      game_select(QString(NGAME_SNAKE.c_str())) {
  initializeGameTetris(GTetris);
  updateParams(GTetris);

  ui->setupUi(this);

  ui->PB_Start->setFixedSize(BT_WIDTH, BT_HEIGHT);
  ui->PB_Tetris->setFixedSize(BT_WIDTH, BT_HEIGHT);
  ui->PB_Snake->setFixedSize(BT_WIDTH, BT_HEIGHT);
  ui->PB_Exit->setFixedSize(BT_WIDTH, BT_HEIGHT);

  ui->QW_Central->layout()->addWidget(View);

  setEnableMenu(true);
}

/**
 * @brief The destructor for the main window.
 */
MainWindow::~MainWindow() {
  if (GTetris) {
    cleanGameTetris(GTetris);
    delete GTetris;
  }
  if (GSnake) delete GSnake;
  if (View) delete View;
  if (controller) delete controller;
  if (ui) delete ui;
}

/**
 * @brief Enables or disables the menu.
 *
 * @param enable Whether to enable the menu.
 */
void MainWindow::setEnableMenu(bool enable) {
  if (ui == nullptr) return;
  if (ui->PB_Start) ui->PB_Start->setEnabled(enable);
  if (ui->PB_Exit) ui->PB_Exit->setEnabled(enable);
  if (ui->PB_Snake) ui->PB_Snake->setEnabled(enable);
  if (ui->PB_Tetris) ui->PB_Tetris->setEnabled(enable);

  if (ui->QVBL_menu) {
    for (int i = 0; i < ui->QVBL_menu->count(); ++i) {
      QLayoutItem *item = ui->QVBL_menu->itemAt(i);
      if (item->widget()) {
        item->widget()->setVisible(enable);
      }
    }
    ui->QVBL_menu->setEnabled(enable);
  }

  if (enable == false) {
    if (ui->QL_MenuImage) ui->QL_MenuImage->hide();
    if (View) {
      View->show();
      View->setFocus();
    }
  } else {
    if (ui->QW_Central) ui->QW_Central->setFocus();
    if (ui->QL_MenuImage) ui->QL_MenuImage->show();
    if (View) View->hide();
  }
}

/**
 * @brief The game is finished.
 */
void MainWindow::isGameFinished() { setEnableMenu(true); }

/**
 * @brief Refreshes the finish connect.
 */
void MainWindow::refreshFinishConnect(void) {
  if (controller) {
    disconnect(controller);
    connect(controller, &QBaseGameController::finished, this,
            &MainWindow::isGameFinished);
  }
}

/**
 * @brief Creates the controller.
 */
void MainWindow::createController() {
  if (controller) {
    delete controller;
    controller = nullptr;
  }

  if (game_select.compare(QString(NGAME_SNAKE.c_str())) == 0) {
    controller = new SnakeController(GSnake, View, this);
    refreshFinishConnect();
    on_PB_Snake_clicked();
  } else if (game_select.compare(NGAME_TETRIS) == 0) {
    controller = new TetrisController(GTetris, View, this);
    refreshFinishConnect();
    on_PB_Tetris_clicked();
  }
}

/**
 * @brief Handles the start button click.
 */
void MainWindow::on_PB_Start_clicked() {
  createController();

  if (controller) {
    setEnableMenu(false);
    controller->run();
  }
}

/**
 * @brief Handles the Tetris button click.
 */
void MainWindow::on_PB_Tetris_clicked() {
  if (ui->PB_Snake) ui->PB_Snake->setStyleSheet(NOT_STYLE);
  if (ui->PB_Tetris) ui->PB_Tetris->setStyleSheet(PRESSED_STYLE);
  game_select = NGAME_TETRIS;
}

/**
 * @brief Handles the Snake button click.
 */
void MainWindow::on_PB_Snake_clicked() {
  if (ui->PB_Snake) ui->PB_Snake->setStyleSheet(PRESSED_STYLE);
  if (ui->PB_Tetris) ui->PB_Tetris->setStyleSheet(NOT_STYLE);
  game_select = QString(NGAME_SNAKE.c_str());
}

/**
 * @brief Handles the exit button click.
 */
void MainWindow::on_PB_Exit_clicked() { QApplication::quit(); }

}  // namespace s21
