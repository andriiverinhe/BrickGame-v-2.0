/**
 * @file Shift.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief SHIFT finite automaton
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

#define COEF_POS_SHIFT 1 /**< The coefficient for position shifting. */

void FSM_Shift(GameTetris* game);

#ifdef __cplusplus
}
#endif