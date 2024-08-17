/**
 * @file Info.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Source file with the main structure of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Info.h"

#include <stdbool.h>

static int helperAllocate(int ***p, const size_t rows, const size_t cols);

/**
 * @brief Function to allocate memory for a two-dimensional array of type int.
 *
 * @param rows number of lines.
 * @param cols number of columns.
 * @param code execution code.
 * @return two-dimensional array of type int.
 */
int **allocateInt(const size_t rows, const size_t cols, int *code) {
  if (rows == 0 || cols == 0) {
    (*code) = BAD_SIZE;
    return NULL;
  }

  int **data = (int **)calloc(rows, sizeof(int *));

  if (data) {
    (*code) = GOOD_ALLOCATE;
    for (size_t i = 0; (i < rows) && (*code) == GOOD_ALLOCATE; i++) {
      data[i] = (int *)calloc(cols, sizeof(int));
      if (!data[i]) {
        data[i] = NULL;
        (*code) = BAD_ALLOCATE;
      }
    }
  } else {
    data = NULL;
    (*code) = BAD_ALLOCATE;
  }
  return data;
}

/**
 * @brief Function to free memory for a two-dimensional array of type int.
 *
 * @param data Array pointer.
 * @param rows Number of rows in the array.
 */
void freeIntDoubleArray(int ***data, const size_t rows) {
  if (data && (*data)) {
    for (size_t i = 0; i < rows; i++) {
      if ((*data)[i]) {
        free((*data)[i]);
        (*data)[i] = NULL;
      }
    }
    free((*data));
    (*data) = NULL;
  }
}

/**
 * @brief Helper function to allocate memory for a 2D integer array.
 *
 * This function allocates memory for a 2D integer array of size rows x cols.
 *
 * @param p Pointer to the pointer of the array.
 * @param rows Number of rows in the array.
 * @param cols Number of columns in the array.
 * @return int Returns GOOD_ALLOCATE if memory allocation is successful, else
 * returns BAD_ALLOCATE.
 */
static int helperAllocate(int ***p, const size_t rows, const size_t cols) {
  int code = BAD_ALLOCATE;
  if (p) *p = allocateInt(rows, cols, &code);
  return code;
}

/**
 * @brief Allocates memory for the game field.
 *
 * This function allocates memory for the game field array in the GameInfo_t
 * structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return int Returns GOOD_ALLOCATE if memory allocation is successful, else
 * returns BAD_ALLOCATE.
 */
int allocateField(GameInfo_t *engine) {
  if (!engine) return BAD_ALLOCATE;
  return helperAllocate(&engine->field, HFIELD, WFIELD);
}

/**
 * @brief Allocates memory for the next piece preview area.
 *
 * This function allocates memory for the next piece preview area array in the
 * GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return int Returns GOOD_ALLOCATE if memory allocation is successful, else
 * returns BAD_ALLOCATE.
 */
int allocateNext(GameInfo_t *engine) {
  if (!engine) return BAD_ALLOCATE;
  return helperAllocate(&engine->next, HNEXT, WFIELD);
}

/**
 * @brief Frees the memory allocated for the next piece preview area.
 *
 * This function frees the memory allocated for the next piece preview area
 * array in the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 */
void freeNext(GameInfo_t *engine) {
  if (engine) freeIntDoubleArray(&engine->next, HNEXT);
}

/**
 * @brief Frees the memory allocated for the game field.
 *
 * This function frees the memory allocated for the game field array in the
 * GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 */
void freeField(GameInfo_t *engine) {
  if (engine) freeIntDoubleArray(&engine->field, HFIELD);
}

/**
 * @brief Set the Score object
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @param score  The score value to set.
 */
void setScore(GameInfo_t *engine, const int score) {
  if (engine) engine->score = score;
}

/**
 * @brief Set the Hige Score object
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @param hscore  The score value to set.
 */
void setHigeScore(GameInfo_t *engine, const int hscore) {
  if (engine)
    if (hscore > engine->high_score) engine->high_score = hscore;
}

/**
 * @brief Set the Speed object
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @param speed  The speed value to set.
 */
void setSpeed(GameInfo_t *engine, const int speed) {
  if (engine) engine->speed = speed;
}

/**
 * @brief Set the Level object
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @param level  The level value to set.
 */
void setLevel(GameInfo_t *engine, const int level) {
  if (engine)
    if (0 < level && level <= 10) engine->level = level;
}

/**
 * @brief Set the Pause object
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @param pause  The pause value to set.
 */
void setPause(GameInfo_t *engine, const int pause) {
  if (engine) {
    if (pause == true)
      engine->pause = true;
    else
      engine->pause = false;
  }
}

/**
 * @brief Gets the score from the GameInfo_t structure.
 *
 * This function retrieves the score from the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return The score value.
 */
int getScore(const GameInfo_t *engine) {
  int score = 0;
  if (engine) score = engine->score;
  return score;
}

/**
 * @brief Gets the high score from the GameInfo_t structure.
 *
 * This function retrieves the high score from the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return The high score value.
 */
int getHigeScore(const GameInfo_t *engine) {
  int score = 0;
  if (engine) score = engine->score;
  return score;
}

/**
 * @brief Gets the speed from the GameInfo_t structure.
 *
 * This function retrieves the speed from the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return The speed value.
 */
int getSpeed(const GameInfo_t *engine) {
  int speed = 0;
  if (engine) speed = engine->speed;
  return speed;
}

/**
 * @brief Gets the level from the GameInfo_t structure.
 *
 * This function retrieves the level from the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return The level value.
 */
int getLevel(const GameInfo_t *engine) {
  int level = 0;
  if (engine) level = engine->level;
  return level;
}

/**
 * @brief Gets the pause state from the GameInfo_t structure.
 *
 * This function retrieves the pause state from the GameInfo_t structure.
 *
 * @param engine Pointer to the GameInfo_t structure.
 * @return The pause state value.
 */
int getPause(const GameInfo_t *engine) {
  int pause = false;
  if (engine) pause = engine->pause;
  return pause;
}