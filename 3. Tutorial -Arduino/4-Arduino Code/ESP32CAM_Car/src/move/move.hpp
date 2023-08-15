/**
 * @file move.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief This file defines all the robot's movement functions.
 *        It contains all the commands towards the motors.
 *        Helper functions to compute speed from joystick input.
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MOVE_H__
#define __MOVE_H__

#include "Arduino.h"

#ifndef L298N_h
#include "L298N.h"
#endif

/**
 * @brief This enum defines the direction of the spin.
 *        A spin means the motors are spinning in opposite directions.
 *        While normal turn means the motors are spinning in the same direction with different speeds.
 */
typedef enum spin_direction_e
{
    RIGHT_E,
    LEFT_E,
} spin_direction_t;

/**
 * @brief This struct defines all the parameters car needs to move.
 *       It contains the speed and direction of each motor.
 *       Speed for either motor is between 0-255.
 *
 */
typedef struct move_params_s
{
    int left_speed;
    L298N::Direction left_direction;
    int right_speed;
    L298N::Direction right_direction;
    int direction;
} move_params_t;

/**
 * @brief This function prints the move parameters using Serial.
 *
 * @param p_move_params
 */
void DEBUG_print_move_params(move_params_t* p_move_params);

/**
 * @brief This function spins the car inplace.
 *
 * @param speed
 * @param direction
 */
void spin(int speed, spin_direction_t direction);

/**
 * @brief Get the move params from joystick coordinates
 *
 * @param x
 * @param y
 * @return move_params_t
 */
move_params_t get_move_params_from_joystick_coordinates(int x, int y);

/**
 * @brief This function send the motors the move parameters.
 *
 * @param p_move_params
 */
void wheel_action(move_params_t* p_move_params);

#endif // __MOVE_H__