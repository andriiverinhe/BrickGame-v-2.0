/**
 * @file GameModel.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief A header file containing structure and function declarations for the
 * game models.
 *
 * This file contains declarations of structures and functions used to work with
 * game models.
 *
 * @version 0.1
 * @date 2024-04-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#include "../MacroInf.h"

/**
 * @brief Enumeration of coordinate directions.
 *
 * An enumeration defining the possible coordinate directions.
 * X corresponds to the horizontal direction and Y corresponds to the vertical
 * direction.
 */
typedef enum {
  X = 0, /**< Horizontal direction. */
  Y = 1, /**< Vertical direction. */
} COORD;

/**
 * @brief Structure representing a game model.
 *
 * This structure represents a game model, which consists of rows and columns
 * defining its size, a 2D array storing the model's shape, an array storing the
 * model's position, and another array storing the coordinates of the model's
 * center.
 */
typedef struct {
  size_t rows;              /**< Number of rows in the model. */
  size_t cols;              /**< Number of columns in the model. */
  int **model_;             /**< 2D array representing the model's shape. */
  int position[SIZE_COORD]; /**< Array storing the model's position. */
  int center[SIZE_COORD];   /**< Array storing the coordinates of the model's
                                    center. */
} Model;

/**
 * @brief Structure representing a collection of game models.
 *
 * This structure represents a collection of game models, containing an array of
 * `Model` structures and a count indicating the number of models in the
 * collection.
 */
typedef struct {
  Model *models; /**< Pointer to an array of `Model` structures representing the
                    game models. */
  size_t count;  /**< Number of models in the collection. */
} Models;

int allocateModel(Model *model);
int allocateModels(Models *models);

void freeModel(Model *model);
void freeModels(Models *models);

void setRowsModel(Model *model, const size_t rows);
void setColsModel(Model *model, const size_t cols);
void setCountModels(Models *models, const size_t count);

size_t getRowsModel(const Model *model);
size_t getColsModel(const Model *model);
size_t getCountModels(const Models *models);

bool checkSizeModel(const Model *model);
bool isNormalModel(const Model *model);
void copyModel(const Model *src, Model *dest);

bool rotateModel(Model *model);

#ifdef __cplusplus
}
#endif