/**
 * @file Collision.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief COLLISION finite automaton
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../GameTetris.h"

#define MAX_INDEX_Y HFIELD - 1 /**< Maximum index value by `y` */

#define POINT_ONE_LINE 100   /**< Points per level collected */
#define POINT_TWO_LINE 300   /**< Points for two levels collected */
#define POINT_THREE_LINE 700 /**< Points for three levels collected */
#define POINT_FOUR_LINE 1500 /**< Points for four collected levels*/

#define PROCENT_MAX 100        /**< The maximum value for percentage. */
#define DIVISORTOGETANUMBER 10 /**< The divisor to get a number.*/
#define MAX_SCORE 999999       /**< The maximum score. */
#define MIN_SCORE 0            /**< The minimum score. */

/**
 * @brief Macro to check if a number is less than or equal to another number.
 *
 * @param first The first number.
 * @param second The second number.
 * @return True if the first number is less than or equal to the second number,
 * false otherwise.
 */
#define LESSOREQUUAL(first, second) (first <= second)

/**
 * @brief Macro to check if the first number is greater than the second number.
 *
 * @param first The first number.
 * @param second The second number.
 * @return True if the first number is greater than the second number, false
 * otherwise.
 */
#define MORE(first, second) (first > second)

/**
 * @brief Macro to check if a score is within a certain range of levels.
 *
 * @param lfirst The lower level bound.
 * @param lsecond The upper level bound.
 * @param score The score to check.
 * @return True if the score falls within the specified range, false otherwise.
 */
#define CHECKED_LEVEL(lfirst, lsecond, score) \
  (LESSOREQUUAL(lfirst, score) && MORE(lsecond, score))

/**
 * @brief Represents the score levels in the game.
 */
typedef enum {
  FIRST = 600,    /**< Score level for the first tier. */
  SECOND = 1200,  /**< Score level for the second tier. */
  THIRD = 1800,   /**< Score level for the third tier. */
  FOURTH = 2400,  /**< Score level for the fourth tier. */
  FIFTH = 3000,   /**< Score level for the fifth tier. */
  SIXTH = 3600,   /**< Score level for the sixth tier. */
  SEVENTH = 4200, /**< Score level for the seventh tier. */
  EIGHTH = 4800,  /**< Score level for the eighth tier. */
  NINETH = 5400,  /**< Score level for the ninth tier. */
  TENTH = 6000    /**< Score level for the tenth tier. */
} LevelScore;

/**
 * @brief Represents the levels in the game.
 */
typedef enum {
  LFIRST = 1,   /**< First level. */
  LSECOND = 2,  /**< Second level. */
  LTHIRD = 3,   /**< Third level. */
  LFOURTH = 4,  /**< Fourth level. */
  LFIFTH = 5,   /**< Fifth level. */
  LSIXTH = 6,   /**< Sixth level. */
  LSEVENTH = 7, /**< Seventh level. */
  LEIGHTH = 8,  /**< Eighth level. */
  LNINETH = 9,  /**< Ninth level. */
  LTENTH = 10   /**< Tenth level. */
} LEVEL;

void FSM_Collision(GameTetris *game);

#ifdef TESTING
unsigned int getTime(const GameInfo_t *engine);
#else
#endif

#ifdef __cplusplus
}
#endif