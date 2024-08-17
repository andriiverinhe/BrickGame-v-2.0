/**
 * @file GameModel.c
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

#include "GameModel.h"

#include <stdlib.h>

#include "../../common/Info/Info.h"
#include "Helpers/ModelHelpers.h"

/**
 * @brief Allocates memory for a game model.
 *
 * This function allocates memory for the game model specified by the `Model`
 * structure. It dynamically allocates memory for a 2D array representing the
 * model's grid, based on the number of rows and columns specified in the
 * `model` parameter. If successful, the function returns SUCCESS
 * (true), otherwise, it returns an error code indicating the reason for
 * failure.
 *
 * @param model Pointer to the `Model` structure containing information about
 * the model to allocate memory for.
 * @return int Returns SUCCESS (true) if memory allocation is
 * successful, otherwise returns an error code.
 */
int allocateModel(Model *model) {
  if (!model) return BAD_ALLOCATE;
  int code = checkSizeModel(model);
  if (code) {
    model->model_ =
        allocateInt(getRowsModel(model), getColsModel(model), &code);
    if (code == BAD_ALLOCATE) freeModel(model);
  } else {
    code = BAD_SIZE;
  }
  return code;
}

/**
 * @brief Allocates memory for the game models.
 *
 * This function allocates memory for the game models specified by the `Models`
 * structure. It dynamically allocates memory for an array of `Model` structures
 * based on the count provided in the `models` parameter. If successful, the
 * function returns SUCCESS (true), otherwise, it returns
 * FAIL (false).
 *
 * @param models Pointer to the `Models` structure containing information about
 * the models to allocate memory for.
 * @return int Returns SUCCESS (true) if memory allocation is
 * successful, FAIL (false) otherwise.
 */
int allocateModels(Models *models) {
  if (!models) return BAD_ALLOCATE;
  int code = GOOD_ALLOCATE;
  size_t cm = getCountModels(models);
  if (cm > 0) {
    models->models = (Model *)calloc(cm, sizeof(Model));
    if (!models->models) code = BAD_ALLOCATE;
  } else {
    code = BAD_SIZE;
  }
  return code;
}

/**
 * @brief Frees memory allocated for a game model.
 *
 * This function frees the memory allocated for the game model specified by the
 * `Model` structure. It releases the memory of the 2D array representing the
 * model's grid and sets the relevant fields of the `Model` structure to NULL
 * and 0. It is essential to call this function to avoid memory leaks after the
 * model is no longer needed.
 *
 * @param model Pointer to the `Model` structure containing the model to free
 * memory for.
 */
void freeModel(Model *model) {
  if (model) {
    freeIntDoubleArray(&model->model_, getRowsModel(model));
    model->model_ = NULL;
    setRowsModel(model, 0);
    setColsModel(model, 0);
  }
}

/**
 * @brief Frees memory allocated for multiple game models.
 *
 * This function frees the memory allocated for an array of game models
 * specified by the `Models` structure. It iterates through each model in the
 * array, frees the memory of the 2D arrays representing their grids, and then
 * frees the memory allocated for the array itself. Finally, it sets the
 * relevant fields of the `Models` structure to NULL and 0. It is essential to
 * call this function to avoid memory leaks after the models are no longer
 * needed.
 *
 * @param models Pointer to the `Models` structure containing the array of
 * models to free memory for.
 */
void freeModels(Models *models) {
  if (models && models->models) {
    for (size_t i = 0; i < getCountModels(models); i++)
      freeModel(&models->models[i]);

    free(models->models);
    models->models = NULL;
    setCountModels(models, 0);
  }
}

/**
 * @brief Set the number of rows for a model.
 *
 * @param model Pointer to the Model structure.
 * @param rows Number of rows to set.
 */
void setRowsModel(Model *model, const size_t rows) {
  if (model) model->rows = rows;
}

/**
 * @brief Set the number of columns for a model.
 *
 * @param model Pointer to the Model structure.
 * @param cols Number of columns to set.
 */
void setColsModel(Model *model, const size_t cols) {
  if (model) model->cols = cols;
};

/**
 * @brief Set the count of models in a collection.
 *
 * @param models Pointer to the Models structure.
 * @param count Number of models to set.
 */
void setCountModels(Models *models, const size_t count) {
  if (models) models->count = count;
}

/**
 * @brief Get the number of rows for a model.
 *
 * @param model Pointer to the Model structure.
 * @return Number of rows.
 */
size_t getRowsModel(const Model *model) {
  size_t rows = 0;
  if (model) rows = model->rows;
  return rows;
}

/**
 * @brief Get the number of columns for a model.
 *
 * @param model Pointer to the Model structure.
 * @return Number of columns.
 */
size_t getColsModel(const Model *model) {
  size_t cols = 0;
  if (model) cols = model->cols;
  return cols;
}

/**
 * @brief Get the count of models in a collection.
 *
 * @param models Pointer to the Models structure.
 * @return Count of models.
 */
size_t getCountModels(const Models *models) {
  size_t count = 0;
  if (models) count = models->count;
  return count;
}

/**
 * @brief Check if the model size meets the minimum size requirement
 *
 * This function checks if the size of the provided model meets the minimum
 * size requirement.
 *
 * @param model Pointer to the Model structure to check
 * @return true if the model size meets the minimum size requirement, false
 * otherwise
 */
bool checkSizeModel(const Model *model) {
  if (!model) return false;
  return (model->cols >= MIN_SIZE) && (model->rows >= MIN_SIZE);
}

/**
 * @brief Check model
 *
 * @param model Pointer to the Model structure
 * @return true if model is correct
 * @return false  if model is incorrect
 */
bool isNormalModel(const Model *model) {
  return (model && checkSizeModel(model) && model->model_);
}

/**
 * @brief Copy the contents of one model to another
 *
 * This function copies the contents of one model to another model. It
 * deallocates the memory of the destination model if it already contains data.
 *
 * @param src The source model to copy from
 * @param dest The destination model to copy to
 */
void copyModel(const Model *src, Model *dest) {
  if (!src || !dest) return;
  if (dest->model_) freeModel(dest);

  dest->center[X] = src->center[X];
  dest->center[Y] = src->center[Y];
  dest->position[X] = src->position[X];
  dest->position[Y] = src->position[Y];
  setColsModel(dest, src->cols);
  setRowsModel(dest, src->rows);

  if (allocateModel(dest)) {
    for (size_t i = 0; i < src->rows; i++)
      for (size_t j = 0; j < src->cols; j++)
        dest->model_[i][j] = src->model_[i][j];
  }
}

/**
 * @brief Rotate the model clockwise by 90 degrees.
 *
 * This function rotates the given model clockwise by 90 degrees. It allocates
 * memory for the rotated model, copies the rotated values from the original
 * model, and updates the model's dimensions and center accordingly.
 *
 * @param model Pointer to the model structure to be rotated.
 * @return true If the rotation operation succeeds.
 * @return false If the rotation operation fails, typically due to invalid input
 * or memory allocation issues.
 */
bool rotateModel(Model *model) {
  if (!isNormalModel(model)) return FAIL;
  int code = FAIL;

  Model newModel = {0};
  const size_t mrows = getRowsModel(model);
  const size_t mcols = getColsModel(model);
  setColsModel(&newModel, mrows);
  setRowsModel(&newModel, mcols);

  code = allocateModel(&newModel);
  if (code == SUCCESS) {
    for (size_t i = 0; i < mrows; i++)
      for (size_t j = 0; j < mcols; j++) {
        newModel.model_[j][i] = model->model_[mrows - i - 1][j];
        if ((mrows - i - 1 == (size_t)model->center[Y]) &&
            j == (size_t)model->center[X]) {
          newModel.center[X] = i;
          newModel.center[Y] = j;
        }
      }
    freeModel(model);
    model->model_ = newModel.model_;
    setColsModel(model, mrows);
    setRowsModel(model, mcols);
    model->center[X] = newModel.center[X];
    model->center[Y] = newModel.center[Y];
  }

  return code;
}