/**
 * @file ModelHelpers.c
 * @author  nenamaxi (an.veringe@gmail.com)
 * @brief A file with constants for the parser and prototypes for model
 * initialization.
 * @version 0.1
 * @date 2024-04-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ModelHelpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int initModel(FILE *file, Model *model);
static void setCenterModel(Model *model);
static int realloc_(Models *models);
static int parssingFile(FILE *file, Models *models);

/**
 * @brief Initialize the model from a file
 *
 * This function reads data from a file and initializes the model structure
 * accordingly. It allocates memory for the model using allocateModel and
 * then reads data from the file to populate the model's internal
 * representation.
 *
 * @param file Pointer to the file to read data from
 * @param model Pointer to the Model structure to initialize
 * @return int Returns GOOD_ALLOCATE if memory allocation is successful and data
 * is read from the file successfully, otherwise returns FAIL
 */
static int initModel(FILE *file, Model *model) {
  int code = allocateModel(model);

  if (code == SUCCESS) {
    char buffer[SIZE_BUFFER] = "\0";

    for (size_t i = 0;
         (i < getRowsModel(model)) && (fgets(buffer, sizeof(buffer), file));
         i++)
      for (size_t j = 0; (j < getColsModel(model)) && (j < SIZE_BUFFER); j++)
        if (buffer[j] == SIGN_TRUE_CELL) model->model_[i][j] = true;
  }
  return code;
}

/**
 * @brief Set the center of the model
 *
 * This function calculates the center coordinates of the model based on its
 * dimensions (rows and columns) and updates the center array accordingly.
 *
 * @param model Pointer to the Model structure
 */
static void setCenterModel(Model *model) {
  model->center[Y] = (getRowsModel(model) > 1) ? getRowsModel(model) - 1 : 0;

  int resx = 0;
  if ((getColsModel(model) % 2) == 0) {
    resx = (getColsModel(model) / 2) - 1;
  } else
    resx = getColsModel(model) % 2;
  model->center[X] = resx;
}

/**
 * @brief Reallocate memory for models array
 *
 * This function reallocates memory for the models array in the Models
 * structure. If the count of models is 0, it initializes the models array by
 * allocating memory for one Model structure. If the count is greater than 0, it
 * reallocates memory to increase the size of the models array by one.
 *
 * @param models Pointer to the Models structure
 * @return int Returns SUCCESS if memory reallocation is successful,
 * otherwise FAIL
 */
static int realloc_(Models *models) {
  int code = FAIL;
  if (getCountModels(models) == 0) {
    setCountModels(models, (getCountModels(models) + 1));
    code = allocateModels(models);
  } else {
    Model *tmpModel = NULL;
    if (models->models)
      tmpModel =
          (Model *)realloc(models->models, (++models->count) * sizeof(Model));
    else
      code = allocateModels(models);

    if (tmpModel) {
      models->models = tmpModel;
      code = SUCCESS;
    }
  }
  return code;
}

/**
 * @brief Parse a file to initialize models
 *
 * This function parses a file to initialize models based on the content of the
 * file. It reads each line of the file and checks if it starts with a specified
 * literal template. If a line matches the template, it extracts the size
 * information for the model from the line, initializes a new model, and sets
 * its size and content accordingly.
 *
 * @param file Pointer to the FILE object representing the file to parse
 * @param models Pointer to the Models structure to store the initialized models
 * @return int Returns SUCCESS if parsing and initialization are
 * successful, otherwise FAIL
 */
static int parssingFile(FILE *file, Models *models) {
  char buffer[SIZE_BUFFER] = "\0";
  int code = SUCCESS;

  while (fgets(buffer, sizeof(buffer), file) && (code == SUCCESS)) {
    unsigned long tmp_rows = 0;
    unsigned long tmp_cols = 0;

    if (sscanf(buffer, LITERAL_INFO_FIGURE, &tmp_rows, &tmp_cols) ==
        SIZE_COORD) {
      if (tmp_rows < MIN_SIZE || tmp_cols < MIN_SIZE) continue;

      code = realloc_(models);
      if (code == SUCCESS) {
        Model *pm = &models->models[getCountModels(models) - MIN_SIZE];
        setRowsModel(pm, tmp_rows);
        setColsModel(pm, tmp_cols);
        code = initModel(file, pm);
        setCenterModel(pm);
      }
    }
  }
  return code;
}

/**
 * @brief Obtain models from a file template
 *
 * This function reads models from a file template, parses the content,
 * and populates the provided Models structure with the parsed models.
 * It sets the return code based on the success or failure of the parsing
 * operation.
 *
 * @param models Pointer to the Models structure to store the parsed models
 * @param code Pointer to an integer variable to store the return code
 * @param filename filename template
 */
void obtainingModels(Models *models, int *code, const char *filename) {
  *code = FAIL;
  if (models && filename) {
    FILE *fileTemplate = fopen(filename, "r");

    if (NULL != fileTemplate) {
      *code = parssingFile(fileTemplate, models);
      fclose(fileTemplate);
    }
  }
}

/**
 * @brief Initialize models from a file template
 *
 * This function initializes models by obtaining them from a file template.
 * It calls the obtainingModels function to parse the file template and
 * populate the provided Models structure with the parsed models. If the
 * number of models obtained is less than a specified threshold, it sets the
 * return code to indicate failure.
 *
 * @param models Pointer to the Models structure to store the parsed models
 * @param filename filename BD
 * @return int Return code indicating the success or failure of the
 * initialization operation
 */
int initializeModels(Models *models, const char *filename) {
  int code = FAIL;
  if (models && filename) {
    obtainingModels(models, &code, filename);
    if (getCountModels(models) < ST_MODELS_COUNT) code = FAIL;
  }
  return code;
}