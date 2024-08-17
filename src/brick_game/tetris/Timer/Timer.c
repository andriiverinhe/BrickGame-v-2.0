/**
 * @file Timer.c
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief The file that describes the thread for the timer.
 * @version 0.1
 * @date 2024-04-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../GameTetris.h"

static void *operationTimer(void *arg);
static void createThread(GameTimer_t *timer);

/**
 * @brief Performs a timer operation.
 *
 * This function is responsible for executing a timer operation. It updates the
 * game parameters and changes the game state if necessary based on the current
 * game state and pause status.
 *
 * @param arg A pointer to a GameTimer_t structure containing timer information.
 * @return void* Always returns NULL.
 */
static void *operationTimer(void *arg) {
  GameTimer_t *timer = (GameTimer_t *)arg;
  GameTetris *game = updateParams(NULL);
  if (!timer || !game) return NULL;

  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = getSpeed(&game->engine);

  nanosleep(&ts, NULL);

  timer->indicator = false;
  if (!game->engine.pause && game->state == MOVE) game->state = SHIFT;

  return NULL;
}

/**
 * @brief Creates a thread for timer operation.
 *
 * This function creates a new thread for timer operation using the provided
 * timer information. The thread executes the operationTimer function.
 *
 * @param timer A pointer to a GameTimer_t structure containing timer
 * information.
 */
static void createThread(GameTimer_t *timer) {
  if (timer) {
    timer->indicator = true;
    pthread_create(timer->thread, NULL, operationTimer, (void *)timer);
  }
}

/**
 * @brief Stops the timer thread.
 *
 * This function stops the timer thread associated with the given timer.
 *
 * @param timer A pointer to a GameTimer_t structure containing timer
 * information.
 */
void stopTime(GameTimer_t *timer) {
  if (timer && timer->thread)
    if (*timer->thread != 0) pthread_join(*timer->thread, NULL);
}

/**
 * @brief Runs the timer if the game is not paused and the state is MOVE.
 *
 * This function runs the timer if the game is not paused and the state is MOVE.
 * It stops the existing timer thread and creates a new one to handle timer
 * operations.
 *
 * @param timer A pointer to a GameTimer_t structure containing timer
 * information.
 */
void runTime(GameTimer_t *timer) {
  stopTime(timer);
  createThread(timer);
}

/**
 * @brief Initializes the game timer.
 *
 * This function initializes the game timer by allocating memory for the timer
 * thread and setting the indicator to false.
 *
 * @param timer A pointer to a GameTimer_t structure to be initialized.
 * @return true if the initialization is successful, false otherwise.
 */
bool initializeTimer(GameTimer_t *timer) {
  bool code = false;
  if (timer) {
    timer->indicator = false;
    timer->thread = (pthread_t *)calloc(1, sizeof(pthread_t));
    if (timer->thread) code = true;
  }
  return code;
}

/**
 * @brief Frees resources associated with the game timer.
 *
 * This function frees the memory allocated for the timer thread and releases
 * any resources associated with the game timer.
 *
 * @param timer A pointer to a GameTimer_t structure whose resources are to be
 * freed.
 */
void freeTimer(GameTimer_t *timer) {
  if (timer && timer->thread) {
    if (*timer->thread != 0) pthread_join(*timer->thread, NULL);
    free(timer->thread);
  }
}
