#include "AC_Snake.hpp"

namespace s21 {

/**
 * @brief Construct a new ac snake::ac snake object
 *
 */
AC_Snake::AC_Snake(void)
    : ReferenceActor("Snake", true, true, ST_LOCATION_SNAKE, ST_ROTATION_SNAKE),
      blockAsix(ST_ROTATION_SNAKE),
      track(ST_BAD_POSITION) {
  body.reserve(ST_MAX_LENGTH_SNAKE);
  body.push_back(location);
}

/**
 * @brief Construct a new ac snake::ac snake object
 *
 * @param length length The initial length of the snake
 * @param location location The initial location of the snake
 */
AC_Snake::AC_Snake(int length, Coordinate location)
    : ReferenceActor("Snake", true, true, location, ST_ROTATION_SNAKE),
      blockAsix(ST_ROTATION_SNAKE) {
  body.reserve(ST_MAX_LENGTH_SNAKE);

  for (int i = 0; i < length && i < ST_INIT_LENGTH_SNAKE; i++)
    body.push_back({location.x - i, location.y});
  track = body.back();
}

/**
 * @brief Destroy the ac snake::ac snake object
 *
 */
AC_Snake::~AC_Snake() {}

/**
 * @brief Moves the snake
 * @note This method is only called if there is no blockage
 */
void AC_Snake::move() {
  if (!movementBlocked && (rotation.x != rotation.y)) {
    Coordinate *head = &body.front();
    Coordinate tmpHead = (*head);

    track = body.back();
    *head += rotation;
    location = *head;

    blockAsix.x = !rotation.x;
    blockAsix.y = !rotation.y;

    for (std::size_t i = 1; i < body.size(); i++) {
      Coordinate tmpCell = body[i];
      body[i] = tmpHead;
      tmpHead = tmpCell;
    }
  }
}

/**
 * @brief Sets the rotation of the snake
 * @param x The x-coordinate of the rotation
 * @param y The y-coordinate of the rotation
 */
void AC_Snake::setRotation(const int x, const int y) { setRotation({x, y}); }

/**
 * @brief Sets the rotation of the snake
 * @param coord A Coordinate object representing the new rotation
 */
void AC_Snake::setRotation(const Coordinate coord) {
  if (coord.x != !blockAsix.x && coord.y != !blockAsix.y)
    if (coord.x == 0 || coord.y == 0) rotation = coord;
}

/**
 * @brief Increases the length of the snake by adding its current position to
 * its body
 */
void AC_Snake::IncreaseLength(void) {
  if (track == ST_BAD_POSITION) return;
  if (isAlive) body.push_back(track);
  if (body.size() == ST_MAX_LENGTH_SNAKE) isAlive = false;
}

/**
 * @brief Returns the current state of the snake
 * @return A constant reference to the snake's body, which is a vector of
 * Coordinate objects
 */
const std::vector<Coordinate> &AC_Snake::getSnake(void) const {
  return this->body;
}

/**
 * @brief Returns the current length of the snake
 * @return The length of the snake, which is an integer representing the number
 * of body segments
 */
int AC_Snake::getLength(void) const { return body.size(); }

}  // namespace s21
