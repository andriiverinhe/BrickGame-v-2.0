/**
 * @file GameTetrisHelpers.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief This file describes auxiliary functions that are stored in the type
 * directory, auxiliary functions for allocating and clearing memory and so on.
 * @version 0.1
 * @date 2024-04-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../GameTetris.h"

/**
 * @brief The name of the file to store the information.
 */
#define FILENAME_BD "BD_Tetris.txt"

/**
 * @brief Literals for reading and writing information from a file.
 */
#define HIGH_SCORE_LITTERAL "High Score: %d"

void saveHighScore(const GameInfo_t *engine);
void initializeHighScore(GameInfo_t *engine);

#ifdef __cplusplus
}
#endif