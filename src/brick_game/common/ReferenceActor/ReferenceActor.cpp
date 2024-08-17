/**
 * @file ReferenceActor.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file with the reference actor of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ReferenceActor.hpp"

#include <iostream>

namespace s21 {

/**
 * @brief Construct a new Reference Actor:: Reference Actor object
 */
ReferenceActor::ReferenceActor(void)
    : name(NOT_NAME),
      isAlive(true),
      movementBlocked(true),
      location{0, 0},
      rotation{0, 0} {}

/**
 * @brief Constructor for the actor with initial values.
 *
 * This constructor initializes the actor with a given name, alive status,
 * movement blockage, location, and rotation.
 *
 * @param name_ The name of the actor.
 * @param alive Whether the actor is alive.
 * @param block Whether the actor's movement is blocked.
 * @param loc The actor's initial location.
 * @param rot The actor's initial rotation.
 */
ReferenceActor::ReferenceActor(const std::string &name_, const bool alive,
                               const bool block, const Coordinate loc,
                               const Coordinate rot)
    : name(name_),
      isAlive(alive),
      movementBlocked(block),
      location(loc),
      rotation(rot) {}

/**
 * @brief Method to move the actor.
 *
 * This method is pure virtual and must be implemented by derived classes.
 */
void ReferenceActor::move(void) {
  if (!movementBlocked) {
    this->location.x += this->rotation.x;
    this->location.y += this->rotation.y;
  } else {
    std::cerr << "Movement is blocked" << std::endl;
  }
}

/**
 * @brief Method to set the actor's rotation.
 *
 * This method sets the actor's rotation using integer coordinates (x, y).
 *
 * @param x The x-coordinate of the new rotation.
 * @param y The y-coordinate of the new rotation.
 */
void ReferenceActor::setRotation(const int x, const int y) {
  setRotation({x, y});
}

/**
 * @brief Method to set the actor's rotation.
 *
 * This method sets the actor's rotation using a Coordinate object.
 *
 * @param coord The new rotation coordinate.
 */
void ReferenceActor::setRotation(const Coordinate coord) {
  if (!movementBlocked)
    this->rotation = coord;
  else
    std::cerr << "Movement is blocked" << std::endl;
}

/**
 * @brief Method to get the actor's rotation.
 *
 * This method returns the actor's current rotation as a Coordinate object.
 *
 * @return The actor's current rotation.
 */
Coordinate ReferenceActor::getRotation(void) { return this->rotation; }

/**
 * @brief Method to set the actor's location.
 *
 * This method sets the actor's location using integer coordinates (x, y).
 *
 * @param x The x-coordinate of the new location.
 * @param y The y-coordinate of the new location.
 */
void ReferenceActor::setLocation(const int x, const int y) {
  setLocation({x, y});
}

/**
 * @brief Method to set the actor's location.
 *
 * This method sets the actor's location using a Coordinate object.
 *
 * @param coord The new location coordinate.
 */
void ReferenceActor::setLocation(const Coordinate coord) {
  if (!movementBlocked)
    this->location = coord;
  else
    std::cerr << "Movement is blocked" << std::endl;
}

/**
 * @brief Method to get the actor's location.
 *
 * This method returns the actor's current location as a Coordinate object.
 *
 * @return The actor's current location.
 */
Coordinate ReferenceActor::getLocation(void) { return this->location; }

/**
 * @brief Method to set whether the actor is alive or not.
 *
 * This method sets whether the actor is alive or not based on a boolean value.
 *
 * @param alive Whether the actor should be considered alive or not.
 */
void ReferenceActor::setIsAlive(bool alive) { this->isAlive = alive; }

/**
 * @brief Method to get whether the actor is alive or not.
 *
 * This method returns whether the actor is currently alive or not as a boolean
 * value.
 *
 * @return Whether the actor is alive or not.
 */
bool ReferenceActor::getIsAlive(void) { return this->isAlive; }

/**
 * @brief Method to set whether the actor's movement is blocked or not.
 *
 * This method sets whether the actor's movement is blocked or not based on a
 * boolean value.
 *
 * @param block Whether the actor's movement should be blocked or not.
 */
void ReferenceActor::setMovementBlocked(bool block) {
  this->movementBlocked = block;
}

/**
 * @brief Method to get whether the actor's movement is blocked or not.
 *
 * This method returns whether the actor's movement is currently blocked or not
 * as a boolean value.
 *
 * @return Whether the actor's movement is blocked or not
 */
bool ReferenceActor::getMovementBlocked(void) { return this->movementBlocked; }

}  // namespace s21
