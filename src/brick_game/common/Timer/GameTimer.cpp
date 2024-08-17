/**
 * @file GameTimer.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file with the timer of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GameTimer.hpp"

#include <iostream>

namespace s21 {

/**
 * @brief Construct a new Game Timer:: Game Timer object
 */
GameTimer::GameTimer(void)
    : start_time(std::chrono::steady_clock::now()),
      end_time(std::chrono::steady_clock::now()) {
  active = false;
}

/**
 * @brief Updates the start time of the timer.
 *
 */
void GameTimer::updateStartTime(void) {
  start_time = std::chrono::steady_clock::now();
}

/**
 * @brief Updates the end time of the timer.
 *
 */
void GameTimer::updateEndTime(void) {
  end_time = std::chrono::steady_clock::now();
  auto timeHasPassed = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  active = (timeHasPassed < duration);
}

/**
 * @brief  Sets the duration of the timer.
 *
 * @param time duration
 */
void GameTimer::setDuration(std::chrono::milliseconds time) {
  this->duration = time;
}

/**
 * @brief  Gets the duration of the timer.
 *
 * @return const std::chrono::milliseconds
 */
const std::chrono::milliseconds GameTimer::getDuration(void) const {
  return duration;
}

/**
 * @brief  Sets the active of the timer.
 *
 * @param active_ Status active
 */
void GameTimer::setActive(bool active_) { this->active = active_; }

/**
 * @brief  Gets the duration of the timer.
 *
 * @return true
 * @return false
 */
bool GameTimer::getActive(void) const { return this->active; }

}  // namespace s21
