/**
 * @file Action.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the main structure of the action.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

/**
 * @brief Enumeration representing user actions in the game.
 */
typedef enum {
  Start,     /**< Start action */
  Pause,     /**< Pause action */
  Terminate, /**< Terminate action */
  Left,      /**< Left arrow key action */
  Right,     /**< Right arrow key action */
  Up,        /**< Up arrow key action */
  Down,      /**< Down arrow key action */
  Action     /**< Action key action */
} UserAction_t;