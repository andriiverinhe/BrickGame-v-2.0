/**
 * @file GameView.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file game view
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <QLabel>
#include <QString>
#include <QWidget>

extern "C" {
#include "../../../brick_game/common/Info/Info.h"
}

namespace s21 {

/**
 * @brief The start constant.
 */
const QString CS_start = "start";

/**
 * @brief The end constant.
 */
const QString CS_end = "end";

/**
 * @brief The not constant.
 */
const QString CS_not = "not";

/**
 * @brief The pause constant.
 */
const QString CS_pause = "PAUSE";

/**
 * @brief The restart constant.
 */
const QString CS_restart = "restart";

/**
 * @brief The name of the brick game constant.
 */
const QString CS_NBG = "Brick Game";

/**
 * @brief The name of the snake game constant.
 */
const QString CS_NSNAKE = "SNAKE";

/**
 * @brief The name of the Tetris game constant.
 */
const QString CS_NTETRIS = "TETRIS";

/**
 * @brief The logo path for the snake game constant.
 */
const QString CS_SLOGO = ":/im/images/SnakeLogo.jpg";

/**
 * @brief The logo path for the Tetris game constant.
 */
const QString CS_TLOGO = ":/im/images/TetrisLogo.png";

/**
 * @brief The text for pressing enter to start a game constant.
 */
const QString CS_press_enter = "Press <enter> to ";

/**
 * @brief The text for pressing escape to exit to the menu constant.
 */
const QString CS_esc_or_exit = "or <esc> to exit to menu";

/**
 * @brief The text for losing the game constant.
 */
const QString CS_lose = "You LOSE";

/**
 * @brief The text for winning the game constant.
 */
const QString CS_win = "You WIN";

/**
 * @brief The text for bad image error constant.
 */
const QString CS_bad_im = "Bad image";

/**
 * @brief The score format string constant.
 */
const QString CS_score = "SCORE: %1";

/**
 * @brief The high score format string constant.
 */
const QString CS_hscore = "HIGH SCORE: %1";

/**
 * @brief The level format string constant.
 */
const QString CS_level = "LEVEL: %1";

/**
 * @brief The size of a cell.
 */
static constexpr int cellSize = 30;

/**
 * @brief The width of the field.
 */
static constexpr int fieldWidth = WFIELD;

/**
 * @brief The height of the field.
 */
static constexpr int fieldHeight = HFIELD;

/**
 * @brief The width of the next section.
 */
static constexpr int nextWidth = WNEXT;

/**
 * @brief The height of the next section.
 */
static constexpr int nextHeight = HNEXT;

/**
 * @brief The pixel width of the field.
 */
static constexpr int fieldWidthP = fieldWidth * cellSize;

/**
 * @brief The pixel height of the field.
 */
static constexpr int fieldHeightP = fieldHeight * cellSize;

/**
 * @brief The pixel width of the next section.
 */
static constexpr int nextWidthP = nextWidth * cellSize;

/**
 * @brief The pixel height of the next section.
 */
static constexpr int nextHeightP = nextHeight * cellSize;

/**
 * @brief The indentation value for 1x.
 */
static constexpr int indentation1x = 10;

/**
 * @brief The indentation value for 2x.
 */
static constexpr int indentation2x = indentation1x * 2;

/**
 * @brief The indentation value for 3x.
 */
static constexpr int indentation3x = indentation1x * 3;

/**
 * @brief The indentation value for 4x.
 */
static constexpr int indentation4x = indentation1x * 4;

/**
 * @brief The indentation value for 5x.
 */
static constexpr int indentation5x = indentation1x * 5;

/**
 * @brief The indentation value for 7x.
 */
static constexpr int indentation7x = indentation1x * 7;

/**
 * @brief The indentation value for 11x.
 */
static constexpr int indentation11x = indentation1x * 11;

/**
 * @brief The indentation value for 13x.
 */
static constexpr int indentation13x = indentation1x * 13;

/**
 * @brief The width of the image.
 */
static constexpr int WIMAGE = 300;

/**
 * @brief The height of the image.
 */
static constexpr int HIMAGE = 230;

/**
 * @brief The position x for the first cell.
 */
static constexpr int POS_X1 = 20;

/**
 * @brief The position y for the third cell.
 */
static constexpr int POS_Y_3_CELLS = 10 + 3 * cellSize;

/**
 * @brief The position y for the fourth cell.
 */
static constexpr int POS_Y_4_CELLS = 10 + 4 * cellSize;

/**
 * @brief The maximum count of cells.
 */
static constexpr int MAX_COUNT_CELLS = 200;

/**
 * @brief A structure to hold the properties of the user interface.
 */
struct UserInterface_t {
  int offsetY; /**< The offset y-coordinate. */
  int offsetX; /**< The offset x-coordinate. */

  int fieldOffsetX; /**< The x-coordinate offset for the field. */
  int fieldOffsetY; /**< The y-coordinate offset for the field. */

  int line; /**< The current line number. */

  int nextOffsetX; /**< The x-coordinate offset for the next section. */
  int nextOffsetY; /**< The y-coordinate offset for the next section. */

  int WWindow; /**< The width of the window. */
  int HWindow; /**< The height of the window. */
};

/**
 * @brief A class for representing a game view.
 */
class GameView : public QWidget {
  Q_OBJECT

 public:
  explicit GameView(QWidget *parent = nullptr);

  void updateGameInfo(const GameInfo_t &info, const QString addition = "not");

  void setGameSelected(const QString &gameName);
  QString getGameSelected(void);

  void keyPressEvent(QKeyEvent *event) override;

 signals:
  /**
   * @brief Signals a user action received.
   *
   * @param event The user action event.
   */
  void userActionReceived(const QKeyEvent *event);

 protected:
  void paintEvent(QPaintEvent *event) override;

  void drawInfo(QPainter &painter, QBrush &brush);
  void drawField(QPainter &painter, QBrush &brush);
  void drawNext(QPainter &painter, QBrush &brush);
  void initSetting();

  QColor getColor(const int code);

  void drawInfoAddition(QPainter &painter, const int infoOffsetY);
  void drawInfoImage(QPainter &painter, QRect &infoRect, const int infoOffsetY);

 private:
  GameInfo_t gameInfo; /**< The game information structure. */

  QString addition; /**< The addition to the game information. */

  QString gameSelected; /**< The selected game name. */

  QPixmap QP_image; /**< The image for the game view (a QPixmap). */

  UserInterface_t
      setting; /**< The settings for the user interface (a UserInterface_t). */
};

}  // namespace s21