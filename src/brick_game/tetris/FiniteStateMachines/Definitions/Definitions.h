/**
 * @file Definitions.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the fsm `start`, fsm `gameover` of the game.
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

#include "../../GameTetris.h"
void FSM_Start(const UserAction_t action, GameTetris *game);
void FSM_GameOver(UserAction_t action, GameTetris *game);

#ifdef __cplusplus
}
#endif