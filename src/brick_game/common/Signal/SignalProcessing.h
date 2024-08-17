/**
 * @file SignalProcessing.h
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file with the signals of the game.
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "../Action/Action.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_DOWN_B 0402     /**< Key code for the down arrow button.*/
#define KEY_UP_B 0403       /**< Key code for the up arrow button.*/
#define KEY_LEFT_B 0404     /**< Key code for the left arrow button.*/
#define KEY_RIGHT_B 0405    /**< Key code for the right arrow button.*/
#define KEY_PAUSE_UPPER 'P' /**< Upper case key code for the pause button.*/
#define KEY_PAUSE_LOWER 'p' /**< Lower case key code for the pause button.*/

#define KEY_SPACE 32 /**< Key code for the space button.*/

#define KEY_ENTER1 10 /**< Key code for the Enter button (variant 1).*/
#define KEY_ENTER2 13 /**< Key code for the Enter button (variant 2).*/

#define KEY_EXIT_BT 'q' /**< Key code for the exit button.*/

UserAction_t get_signal(int signal);

#ifdef __cplusplus
}
#endif