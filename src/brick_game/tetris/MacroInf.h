/**
 * @file MacroInf.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Macro file
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

#define ST_MODELS_COUNT 7 /**< Standart count models */

#define FAIL false /**< Represents a failed operation or function call. */
#define SUCCESS                                           \
  true /**< Represents a successful operation or function \
          call. */

#define SIZE_BUFFER 1024 /**< The size of the buffer. */
#define SIZE_COORD 2     /**< Number of coordinates */

/**
 * @brief The maximum level of the game.
 */
#define MAX_LEVEL 10

/**
 * @brief The minimum level of the game.
 */
#define MIN_LEVEL 1

/**
 * @brief The initial level of the game.
 */
#define INIT_LEVEL MIN_LEVEL

/**
 * @brief The initial score of the game.
 */
#define INIT_SCORE 0

#define COEF_SPEED_LEVEL_1 250000000  /**< Speed coefficient for level 1. */
#define COEF_SPEED_LEVEL_2 240000000  /**< Speed coefficient for level 2. */
#define COEF_SPEED_LEVEL_3 230000000  /**< Speed coefficient for level 3. */
#define COEF_SPEED_LEVEL_4 220000000  /**< Speed coefficient for level 4. */
#define COEF_SPEED_LEVEL_5 210000000  /**< Speed coefficient for level 5. */
#define COEF_SPEED_LEVEL_6 200000000  /**< Speed coefficient for level 6. */
#define COEF_SPEED_LEVEL_7 190000000  /**< Speed coefficient for level 7. */
#define COEF_SPEED_LEVEL_8 180000000  /**< Speed coefficient for level 8. */
#define COEF_SPEED_LEVEL_9 170000000  /**< Speed coefficient for level 9. */
#define COEF_SPEED_LEVEL_10 160000000 /**< Speed coefficient for level 10. */

#define NGAME_TETRIS "TETRIS" /**< The name of the game TETRIS. */
#define NAME_FILE_TEMPLATE                                                    \
  "Model_templates.txt" /**< The name of the template file used in the model. \
                         */

#ifdef __cplusplus
}
#endif