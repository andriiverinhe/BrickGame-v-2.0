/**
 * @file GameTetrisHelpers.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief This file describes auxiliary functions that are stored in the type
 * directory, auxiliary functions for allocating and clearing memory and so on.
 * @version 0.1
 * @date 2024-04-13
 *
 * @copyright Copyright (c) 2024
 */

#include "GameTetrisHelpers.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Function to initialize the HighScore. Information is taken from a
 * special file where information is stored, the function parses the file and
 * retrieves information by a special literal.
 *
 * @param engine Pointer to the `GameInfo_t` structure, where the highScore
 * will be written.
 */
void initializeHighScore(GameInfo_t *engine) {
  if (!engine) return;
  FILE *file = fopen(FILENAME_BD, "r");
  int high_score = 0;

  if (file != NULL) {
    char buffer[SIZE_BUFFER] = "\0";
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      sscanf(buffer, HIGH_SCORE_LITTERAL, &high_score);
      if (high_score > getHigeScore(engine)) setHigeScore(engine, high_score);
    }

    fclose(file);
  }
}

/**
 * @brief Function for saving HighScore to a file, saves only if the points
 * scored exceed the current score record.
 *
 * @param engine Pointer to the `GameInfo_t` structure from which the
 * information is taken.
 */
void saveHighScore(const GameInfo_t *engine) {
  if (!engine) return;
  FILE *file = fopen(FILENAME_BD, "w+");

  if (file != NULL) {
    fprintf(file, HIGH_SCORE_LITTERAL, engine->high_score);
    fclose(file);
  }
}
