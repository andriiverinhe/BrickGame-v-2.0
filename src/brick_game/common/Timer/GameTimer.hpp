/**
 * @file GameTimer.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the timer of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <chrono>
#include <thread>

namespace s21 {

/**
 * @brief Game timer class.
 */
class GameTimer {
 public:
  /**
   * @brief Type time - std::chrono::time_point<std::chrono::steady_clock>
   */
  using type_time = std::chrono::time_point<std::chrono::steady_clock>;
  GameTimer(void);
  ~GameTimer() = default;

  void updateStartTime(void);
  void updateEndTime(void);

  void setDuration(const std::chrono::milliseconds time);
  const std::chrono::milliseconds getDuration(void) const;

  void setActive(bool active_);
  bool getActive(void) const;

 private:
  type_time start_time;               /** Start time */
  type_time end_time;                 /** End time */
  std::chrono::milliseconds duration; /** Duration */
  bool active;                        /** Active timer status */
};

}  // namespace s21
