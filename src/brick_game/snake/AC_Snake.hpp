#pragma once
#include <string>
#include <vector>

#include "../common/ReferenceActor/ReferenceActor.hpp"

namespace s21 {

/**
 * @brief Maximum snake length
 */
constexpr int16_t ST_MAX_LENGTH_SNAKE = 200;

/**
 * @brief Initial snake length
 */
constexpr int16_t ST_INIT_LENGTH_SNAKE = 4;

/**
 * @brief Maximum initial snake length
 */
constexpr int16_t ST_MAX_INIT_LENGTH_SNAKE = 5;

/**
 * @brief Snake initial location
 */
constexpr Coordinate ST_LOCATION_SNAKE = {5, 10};

/**
 * @brief Snake initial rotation
 */
constexpr Coordinate ST_ROTATION_SNAKE = {1, 0};

/**
 * @brief Bad position for the snake
 */
constexpr Coordinate ST_BAD_POSITION = {-100, -100};

/**
 * @brief Wall string
 */
const std::string CS_Wall = "Wall";

/**
 * @brief Fruit string
 */
const std::string CS_Fruit = "Fruit";

/**
 * @brief Snake string
 */
const std::string CS_Snake = "Snake";

/**
 * @brief No collision string
 */
const std::string CS_NoCollide = "No Collide";

/**
 * @brief A class representing a snake
 * @class AC_Snake
 * @extends ReferenceActor
 */
class AC_Snake : public ReferenceActor {
#ifdef TESTING
 public:
#else
 private:
#endif

  Coordinate blockAsix; /** Locked axles for movement */
  Coordinate track;     /** The track coordinate, which represents the snake's
                           movement path */
  std::vector<Coordinate>
      body; /** The snake's body, which is a vector of Coordinate objects
               representing the snake's segments */

 public:
  AC_Snake(void);
  AC_Snake(int length, Coordinate location);

  ~AC_Snake();

  void move() override;
  void setRotation(const int x, const int y) override;
  void setRotation(const Coordinate coord) override;
  void IncreaseLength(void);
  const std::vector<Coordinate>& getSnake(void) const;
  int getLength(void) const;
};

}  // namespace s21
