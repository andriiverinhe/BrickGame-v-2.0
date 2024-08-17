/**
 * @file Timer.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief The file that describes the thread for the timer.
 * @version 0.1
 * @date 2024-04-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include <stdbool.h>

// #include "../type/GameType.h"

/**
 * @brief Structure representing a game timer.
 */
typedef struct {
  bool indicator;    /**< State indicator of the timer. */
  pthread_t *thread; /**< Pointer to the timer thread. */
} GameTimer_t;

bool initializeTimer(GameTimer_t *timer);
void freeTimer(GameTimer_t *timer);
void stopTime(GameTimer_t *timer);
void runTime(GameTimer_t *timer);

#ifdef __cplusplus
}
#endif