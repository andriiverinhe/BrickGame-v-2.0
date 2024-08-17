/**
 * @file FSMHelpers.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief File in which all auxiliary functions for finite automata are stored
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

#define ADD 100  /**< Constant representing addition operation */
#define DEL -100 /**< Constant representing deletion operation */

int getRandomIndex(const size_t maxIndex);
bool isNormalNextIndex(const GameTetris *game);

void zeroingNext(GameInfo_t *engine);
void zeroingField(GameInfo_t *engine);
void zeroingInfo(GameTetris *game);

void setNextDooubleArray(GameTetris *game);
void addedModelToField(GameTetris *game);
void deletModelInField(GameTetris *game);
bool isNormalCheckedPosition(const int x, const int y);

#ifdef __cplusplus
}
#endif