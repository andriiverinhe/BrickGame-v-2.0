/**
 * @file GameView.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file game view
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GameView.hpp"

#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QPixmap>
namespace s21 {

/**
 * @brief The default constructor for GameView.
 *
 * @param parent The parent widget.
 */
GameView::GameView(QWidget *parent) : QWidget(parent), addition(CS_start) {
  gameInfo.field = nullptr;
  gameInfo.next = nullptr;
  gameInfo.score = 0;
  gameInfo.high_score = 0;
  gameInfo.level = 0;
  gameInfo.speed = 0;
  gameInfo.pause = 0;

  setGameSelected(CS_NSNAKE);
  initSetting();

  setFixedSize(setting.WWindow, setting.HWindow);
}

/**
 * @brief Initializes the game setting.
 */
void GameView::initSetting() {
  setting.WWindow = (fieldWidthP) * 2 + indentation4x;
  setting.HWindow = (fieldHeightP) + indentation2x;

  setting.offsetX = 0;
  setting.offsetY = 0;

  setting.fieldOffsetX = indentation1x;
  setting.fieldOffsetY = indentation1x;

  setting.line = setting.WWindow / 2;

  setting.nextOffsetX = setting.line + (fieldWidthP) / 2 - (nextWidthP / 2);
  setting.nextOffsetY = indentation7x;
}

/**
 * @brief Handles a key press event.
 *
 * @param event The key press event.
 */
void GameView::keyPressEvent(QKeyEvent *event) {
  emit userActionReceived(event);
}

/**
 * @brief Sets the selected game.
 *
 * @param gameName The name of the selected game.
 */
void GameView::setGameSelected(const QString &gameName) {
  this->gameSelected = gameName;
  if (gameName == CS_NSNAKE) QP_image = QPixmap(CS_SLOGO);
  if (gameName == CS_NTETRIS) QP_image = QPixmap(CS_TLOGO);
}

/**
 * @brief Gets the selected game.
 *
 * @return The name of the selected game.
 */
QString GameView::getGameSelected(void) { return this->gameSelected; }

/**
 * @brief Updates the game information.
 *
 * @param info The game information.
 * @param addition The addition to the game information.
 */
void GameView::updateGameInfo(const GameInfo_t &info, const QString addition) {
  gameInfo = info;
  this->addition = addition;
  update();
}

/**
 * @brief Gets the color of a specific code.
 *
 * @param code The code for the color.
 *
 * @return The color corresponding to the code.
 */
QColor GameView::getColor(const int code) {
  QColor color = Qt::white;
  switch (code) {
    case 1:
      color = Qt::blue;
      break;
    case 2:
    case ST_CODE_SNAKE:
      color = Qt::green;
      break;
    case 3:
      color = Qt::yellow;
      break;
    case 4:
    case ST_CODE_FRUIT:
      color = Qt::red;
      break;
    case 5:
      color = QColor("#c95e00");
      break;
    case 6:
      color = QColor("#c900c2");
      break;
    case 7:
      color = QColor("#00c961");
      break;
    default:
      color = QColor("#161d29");
      break;
  }
  return color;
}
}  // namespace s21