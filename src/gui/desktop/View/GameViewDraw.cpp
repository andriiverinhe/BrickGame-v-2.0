/**
 * @file GameViewDraw.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file game view
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QPixmap>

#include "GameView.hpp"

namespace s21 {

/**
 * @brief Draws the game information addition.
 *
 * @param painter The painter.
 * @param infoOffsetY The offset y-coordinate for the information addition.
 */
void GameView::drawInfoAddition(QPainter &painter, const int infoOffsetY) {
  if (addition == CS_start || addition == CS_end) {
    if (addition == CS_start)
      painter.drawText(POS_X1, POS_Y_3_CELLS, CS_press_enter + addition);
    else
      painter.drawText(POS_X1, POS_Y_3_CELLS, CS_press_enter + CS_restart);
    painter.drawText(POS_X1, POS_Y_4_CELLS, CS_esc_or_exit);

    QString str_lose_or_win = CS_lose;
    if (gameSelected == CS_NSNAKE && gameInfo.score == MAX_COUNT_CELLS)
      str_lose_or_win = CS_win;

    painter.drawText(setting.nextOffsetX + indentation2x,
                     infoOffsetY - indentation2x, str_lose_or_win);
  }
}

/**
 * @brief Draws the game information image.
 *
 * @param painter The painter.
 * @param infoRect The rectangle for the information image.
 * @param infoOffsetY The offset y-coordinate for the information image.
 */
void GameView::drawInfoImage(QPainter &painter, QRect &infoRect,
                             const int infoOffsetY) {
  int imageOffsetY = infoRect.bottom() + (indentation4x);
  QRect imageRect(setting.line + indentation1x, imageOffsetY, WIMAGE, HIMAGE);

  if (!QP_image.isNull()) {
    QPixmap scaledImage = QP_image.scaled(imageRect.size(), Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
    int xOffset = imageRect.x() + (imageRect.width() - scaledImage.width()) / 2;
    int yOffset =
        imageRect.y() + (imageRect.height() - scaledImage.height()) / 2;
    painter.drawPixmap(xOffset, yOffset, scaledImage);
  } else {
    painter.drawText(imageRect, Qt::AlignCenter, CS_bad_im);
  }
}

/**
 * @brief Draws the game information.
 *
 * @param painter The painter.
 * @param brush The brush.
 */
void GameView::drawInfo(QPainter &painter, QBrush &brush) {
  int infoOffsetY = setting.nextOffsetY + nextHeightP + indentation7x;
  QRect infoRect(setting.line + indentation1x, infoOffsetY, WFIELD * cellSize,
                 indentation13x);
  painter.drawRect(infoRect);

  painter.setPen(QColor("#c7c312"));

  painter.drawText(setting.nextOffsetX, indentation5x, CS_NBG);

  painter.drawText(setting.line + indentation4x, infoOffsetY + indentation3x,
                   QString(CS_score).arg(gameInfo.score));
  painter.drawText(setting.line + indentation4x, infoOffsetY + indentation7x,
                   QString(CS_level).arg(gameInfo.level));
  painter.drawText(setting.line + indentation4x, infoOffsetY + indentation11x,
                   QString(CS_hscore).arg(gameInfo.high_score));

  if (gameInfo.pause)
    painter.drawText(setting.nextOffsetX + indentation2x,
                     infoOffsetY - indentation2x, CS_pause);

  drawInfoAddition(painter, infoOffsetY);
  drawInfoImage(painter, infoRect, infoOffsetY);
}

/**
 * @brief Draws the game field.
 *
 * @param painter The painter.
 * @param brush The brush.
 */
void GameView::drawField(QPainter &painter, QBrush &brush) {
  QRect fieldRect(setting.fieldOffsetX, setting.fieldOffsetY, fieldWidthP,
                  fieldHeightP);
  painter.drawRect(fieldRect);

  for (int y = 0; y < fieldHeight; ++y) {
    for (int x = 0; x < fieldWidth; ++x) {
      QRect rect(setting.fieldOffsetX + x * cellSize,
                 setting.fieldOffsetY + y * cellSize, cellSize, cellSize);
      int cellValue = gameInfo.field[y][x];

      brush.setColor(getColor(cellValue));
      brush.setStyle(Qt::SolidPattern);

      painter.fillRect(rect, brush);
      painter.drawRect(rect);
    }
  }
}

/**
 * @brief Draws the next section.
 *
 * @param painter The painter.
 * @param brush The brush.
 */
void GameView::drawNext(QPainter &painter, QBrush &brush) {
  QRect nextOuterRect(setting.nextOffsetX, setting.nextOffsetY,
                      nextWidthP + POS_X1, nextHeightP + POS_X1);
  QRect nextInnerRect(setting.nextOffsetX + indentation1x,
                      setting.nextOffsetY + indentation1x, nextWidthP,
                      nextHeightP);

  painter.drawRect(nextOuterRect);
  painter.drawRect(nextInnerRect);

  for (int y = 0; y < nextHeight; ++y) {
    for (int x = 0; x < nextWidth; ++x) {
      QRect rect(nextInnerRect.x() + x * cellSize,
                 nextInnerRect.y() + y * cellSize, cellSize, cellSize);
      int cellValue = gameInfo.next[y][x];

      brush.setColor(getColor(cellValue));
      brush.setStyle(Qt::SolidPattern);

      painter.fillRect(rect, brush);
      painter.drawRect(rect);
    }
  }
}

/**
 * @brief Paints the game view.
 *
 * @param event The paint event.
 */
void GameView::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  if (gameInfo.field == nullptr || gameInfo.next == nullptr) return;

  QPainter painter(this);
  QBrush brush;
  QPen pen(QColor(Qt::black));
  pen.setWidth(2);
  painter.setPen(pen);

  painter.fillRect(this->rect(), QColor("#191919"));

  QFont font = painter.font();
  font.setPointSize(18);
  font.setBold(true);
  painter.setFont(font);

  painter.drawRect(setting.offsetX, setting.offsetY, setting.WWindow,
                   setting.HWindow);

  drawField(painter, brush);

  painter.drawLine(setting.line, setting.offsetY, setting.line, height());

  drawNext(painter, brush);

  drawInfo(painter, brush);
}
}  // namespace s21