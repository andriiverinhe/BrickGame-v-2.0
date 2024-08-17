/**
 * @file ReferenceClassGame.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File in which the virtual class of the game is implemented.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../Action/Action.h"
#include "../Info/Info.h"

namespace s21 {

/**
 * @brief Width of the game state.
 *
 * This constant represents the width of the game state.
 */
constexpr int ST_SIZE_WIDTH = WFIELD;

/**
 * @brief Height of the game state.
 *
 * This constant represents the height of the game state.
 */
constexpr int ST_SIZE_HEIGHT = HFIELD;

/**
 * @brief Action for moving left.
 *
 * This constant represents the action for moving the game state to the left.
 */
constexpr int ST_DIRACTION_LEFT = -1;

/**
 * @brief Action for moving right.
 *
 * This constant represents the action for moving the game state to the right.
 */
constexpr int ST_DIRACTION_RIGHT = 1;

/**
 * @brief Action for moving up.
 *
 * This constant represents the action for moving the game state up.
 */
constexpr int ST_DIRACTION_UP = -1;

/**
 * @brief Action for moving down.
 *
 * This constant represents the action for moving the game state down.
 */
constexpr int ST_DIRACTION_DOWN = 1;

/**
 * @brief File path for saving the game.
 *
 * This constant represents the file path for saving the game state.
 */
const std::string FILE_SAVE = "BD_Snake.txt";

/**
 * @brief Information string for saving high score.
 *
 * This constant represents the string used to save high score information.
 */
const std::string SAVING_INFO = "High Score: ";

/**
 * @brief The base class for the game.
 */
class Game {
#ifdef TESTING
 public:
#else
 protected:
#endif
  GameInfo_t engine;          /**< Struct Gameinfo */
  std::string filenameSaving; /**< filename BD */

 public:
  /**
   * @brief Construct a new Game object
   */
  Game(void) : engine({}), filenameSaving(FILE_SAVE){};

  /**
   * @brief Construct a new Game object
   *
   * @param filename fillename BD
   */
  explicit Game(const std::string &filename)
      : engine({}), filenameSaving(filename){};
  virtual ~Game() = default;

#ifdef TESTING
  virtual void userInput(UserAction_t action, bool hold) {
    (void)action;
    (void)hold;
  };
#else
  /**
   * @brief Processes user input based on the current game state.
   *
   * @param action The user action to process.
   * @param hold Indicates whether the action is being held.
   */
  virtual void userInput(UserAction_t action, bool hold) = 0;
#endif
  /**
   * @brief Updates and retrieves the current game state information.
   *
   * This function updates and retrieves the current game state information,
   * including the field, next piece, score, level, speed, and pause state.
   *
   * @return GameInfo_t The updated game state information.
   */
  virtual GameInfo_t updateCurrentState() { return this->engine; };

  /**
   * @brief Method to clean the game field.
   *
   * This method cleans the game field by setting all values to zero.
   */
  virtual void cleanField() {
    if (!engine.field) return;
    for (int i = 0; i < ST_SIZE_HEIGHT; i++)
      for (int j = 0; j < ST_SIZE_WIDTH; j++) engine.field[i][j] = 0;
  }

  /**
   * @brief Method to save the game high_score.
   *
   * This method saves the game high_score to a file.
   */
  virtual void save() {
    std::ofstream file(filenameSaving, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
      file << SAVING_INFO << engine.high_score << std::endl;
      file.close();
    }
  }

  /**
   * @brief Method to read saved game high_score.
   *
   * This method reads saved game high_score from a file and updates the high
   * score accordingly.
   */
  virtual void readSave() {
    std::ifstream file(filenameSaving);
    if (file.is_open()) {
      std::string line;
      std::getline(file, line);
      file.close();

      std::string::size_type pos = line.find(SAVING_INFO);
      if (pos != std::string::npos) {
        std::string scoreStr = line.substr(pos + SAVING_INFO.size());
        std::istringstream scoreStream(scoreStr);
        scoreStream >> engine.high_score;

      } else
        engine.high_score = 0;
    } else
      engine.high_score = 0;
  }
};

}  // namespace s21