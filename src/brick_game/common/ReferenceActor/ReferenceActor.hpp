/**
 * @file ReferenceActor.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the reference actor of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

namespace s21 {

/**
 * @brief A structure representing a coordinate in a 2D space.
 */
struct Coordinate {
  int x; /**< The x-coordinate of the point. */
  int y; /**< The y-coordinate of the point. */

  /**
   * @brief Equality operator for comparing two coordinates.
   *
   * This operator checks if two coordinates have the same x and y values.
   *
   * @param other The other coordinate to compare with.
   * @return true if the coordinates are equal, false otherwise.
   */
  bool operator==(const Coordinate& other) const {
    return (this->x == other.x && this->y == other.y);
  }

  /**
   * @brief Inequality operator for comparing two coordinates.
   *
   * This operator checks if two coordinates have different x and/or y values.
   *
   * @param other The other coordinate to compare with.
   * @return true if the coordinates are not equal, false otherwise.
   */
  bool operator!=(const Coordinate& other) const {
    return (this->x != other.x || this->y != other.y);
  }

  /**
   * @brief Assignment operator for adding another coordinate to this one.
   *
   * This operator adds the x and y values of the other coordinate to this one.
   *
   * @param other The other coordinate to add to this one.
   * @return A reference to this coordinate after the operation.
   */
  Coordinate& operator+=(const Coordinate& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }
};

/**
 * @brief String: `none`
 */
const std::string NOT_NAME = "none";

/**
 * @brief A base class for actors in a game.
 */
class ReferenceActor {
 protected:
  std::string name;     /**< Actor name */
  bool isAlive;         /**< Actor isAlive */
  bool movementBlocked; /**< Variable movement blocked*/
  Coordinate location;  /**< Actor location */
  Coordinate rotation;  /**< Actor rotation */

 public:
  ReferenceActor(void);
  ReferenceActor(const std::string& name_, const bool alive, const bool block,
                 const Coordinate loc, const Coordinate rot);
  virtual ~ReferenceActor() = default;

  virtual void move(void);

  virtual void setRotation(const int x, const int y);
  virtual void setRotation(const Coordinate coord);
  virtual Coordinate getRotation(void);

  virtual void setLocation(const int x, const int y);
  virtual void setLocation(const Coordinate coord);
  virtual Coordinate getLocation(void);

  virtual void setIsAlive(bool alive);
  virtual bool getIsAlive(void);

  virtual void setMovementBlocked(bool block);
  virtual bool getMovementBlocked(void);
};
}  // namespace s21
