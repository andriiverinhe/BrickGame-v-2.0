/**
 * @file GameSnake.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Snake game header file.
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../common/ReferenceActor/ReferenceActor.hpp"
#include "../common/ReferenceGame/ReferenceClassGame.hpp"
#include "../common/State/State.h"
#include "../common/Timer/GameTimer.hpp"
#include "AC_Snake.hpp"

namespace s21 {

/**
 * @brief Maximum level for the game.
 */
constexpr int16_t ST_MAX_LEVEL = 10;

/**
 * @brief Points required to reach a new level.
 */
constexpr int16_t ST_POINT_FOR_LEVEL = 5;

/**
 * @brief Initial speed for the game entities.
 */
constexpr int16_t ST_INIT_SPEED = 200;

/**
 * @brief Coefficient for speed adjustment.
 */
constexpr int16_t ST_COEFICIENT_SPEED = 10;

/**
 * @brief Name of the snake game.
 */
const std::string NGAME_SNAKE = "SNAKE";

/**
 * @brief The GameSnake class represents the snake game.
 *
 * This class extends the Game class and provides functionality for the snake
 * game.
 */
class GameSnake : public Game {
#ifdef TESTING
 public:
#else
 private:
#endif
  AC_Snake snake;       /** Actor snake */
  ReferenceActor fruit; /** Actor fruit */
  GameTimer timer;      /** The game timer. */
  GameState_t state;    /** The current state of the game. */

 public:
  GameSnake(void);
  ~GameSnake();

  GameState_t getState() const;
  void setState(const GameState_t sstate);
  void reset(const GameState_t reset_state);

  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;

#ifdef TESTING
 public:
#else
 private:
#endif
  void addSnakeToField();
  void addFruitToField();
  void updateInfo();

  void generateFruit(const int x, const int y);
  void generateFruitInRandomPosition();
  bool checkCollideSnake();
  bool checkCollide(std::string &object);

  void helperFsmSpawn();
  void setDiraction(UserAction_t action);
  void caseMove(UserAction_t action);
  void helperFsmShift();
  void helperFsmCollision();
};

}  // namespace s21