/**
 * @file ModelHelpers.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief A file with constants for the parser and prototypes for model
 * initialization.
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

#include "../GameModel.h"

#define SIGN_WIDTH 'w'     /**< Symbol for the `width` of the model. */
#define SIGN_HEIGHT 'h'    /**< Symbol for the `height` of the model. */
#define SIGN_TRUE_CELL '1' /**< Symbol for the `height` of the model. */
#define LITERAL_INFO_FIGURE \
  "t: h-%lu w-%lu" /**< The literal string format for figure information. */

/**
 * @brief Symbol indicating the beginning of a new model.
 */
#define LITERAL_TEMPLATE 't'

#define MIN_SIZE 1 /**< Minimal correct size. */

int initializeModels(Models *models, const char *filename);
void obtainingModels(Models *models, int *code, const char *filename);

#ifdef __cplusplus
}
#endif