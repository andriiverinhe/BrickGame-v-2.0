/**
 * @file Info.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the main structure of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define WFIELD 10 /**< Width field */
#define HFIELD 20 /**< Height field */

#define WNEXT 4 /**< Width next */
#define HNEXT 2 /**< Height next */

#define ST_CODE_SNAKE 100 /**< int code snake */
#define ST_CODE_FRUIT 200 /**< int code fruit */

#define BAD_SIZE 2      /**< Indicates a bad size value. */
#define GOOD_ALLOCATE 1 /**<  Indicates a successful allocation. */
#define BAD_ALLOCATE 0  /**< Indicates a failed allocation. */

/**
 * @brief A structure holding information about a game.
 */
typedef struct {
  int **field;    /**< A 2D array of pointers to game field. */
  int **next;     /**< A 2D array of pointers to next. */
  int score;      /**< The current score of the game. */
  int high_score; /**< The high score of the game. */
  int level;      /**< The current level of the game. */
  int speed;      /**< The current speed of the game. */
  int pause;      /**< A flag indicating whether the game is paused or not. */
} GameInfo_t;

int **allocateInt(const size_t rows, const size_t cols, int *code);
void freeIntDoubleArray(int ***data, const size_t rows);

int allocateField(GameInfo_t *engine);
int allocateNext(GameInfo_t *engine);
void freeField(GameInfo_t *engine);
void freeNext(GameInfo_t *engine);

void setScore(GameInfo_t *engine, const int score);
void setHigeScore(GameInfo_t *engine, const int hscore);
void setSpeed(GameInfo_t *engine, const int speed);
void setLevel(GameInfo_t *engine, const int level);
void setPause(GameInfo_t *engine, const int pause);

int getScore(const GameInfo_t *engine);
int getHigeScore(const GameInfo_t *engine);
int getSpeed(const GameInfo_t *engine);
int getLevel(const GameInfo_t *engine);
int getPause(const GameInfo_t *engine);

#ifdef __cplusplus
}
#endif