/**
 * @file move.cpp
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
#include "move.hpp"
#endif

extern int gpLs;
extern int gpLb;
extern int gpLf;
extern int gpRs;
extern int gpRb;
extern int gpRf;

//initialize motors
L298N left_motor(gpLs, gpLf, gpLb);
L298N right_motor(gpRs, gpRf, gpRb);

static void DEBUG_print_direction(L298N::Direction direction)
{
    switch (direction)
    {
    case L298N::Direction::FORWARD:
        Serial.println("FORWARD");
        break;
    case L298N::Direction::BACKWARD:
        Serial.println("BACKWARD");
        break;
    case L298N::Direction::STOP:
        Serial.println("STOP");
        break;
    default:
        Serial.println("ERROR");
        break;
    }
}

/**
 * @brief This function prints the move parameters using Serial.
 *
 * @param p_move_params
 */
void DEBUG_print_move_params(move_params_t* p_move_params)
{
    Serial.print("left_direction: ");
    DEBUG_print_direction(p_move_params->left_direction);
    Serial.print("left_speed: ");
    Serial.println(p_move_params->left_speed);
    Serial.print("right_direction: ");
    DEBUG_print_direction(p_move_params->right_direction);
    Serial.print("right_speed: ");
    Serial.println(p_move_params->right_speed);
}

/**
 * @brief This function send the motors the move parameters.
 *
 * @param p_move_params
 */
void wheel_action(move_params_t* p_move_params)
{
    left_motor.setSpeed(p_move_params->left_speed);
    right_motor.setSpeed(p_move_params->right_speed);
    left_motor.run(p_move_params->left_direction);
    right_motor.run(p_move_params->right_direction);
}

/**
 * @brief This function spins the car inplace.
 *
 * @param speed
 * @param direction
 */
void spin(int speed, spin_direction_t direction)
{
    move_params_t move_params = {};
    move_params.right_speed = speed;
    move_params.left_speed = speed;
    if (RIGHT_E == direction)
    {
        move_params.left_direction = L298N::Direction::FORWARD;
        move_params.right_direction = L298N::Direction::BACKWARD;
    }
    else
    {
        move_params.left_direction = L298N::Direction::BACKWARD;
        move_params.right_direction = L298N::Direction::FORWARD;
    }
    wheel_action(&move_params);
}

/**
 * @brief Get the move params from joystick coordinates
 *
 * @param x
 * @param y
 * @return move_params_t
 */
move_params_t get_move_params_from_joystick_coordinates(int x, int y)
{
    move_params_t move_params = {};
    if (y > 0)
    {
        move_params.left_direction = L298N::Direction::FORWARD;
        move_params.right_direction = L298N::Direction::FORWARD;
    }
    else if (y < 0)
    {
        move_params.left_direction = L298N::Direction::BACKWARD;
        move_params.right_direction = L298N::Direction::BACKWARD;
    }
    else
    {
        move_params.left_direction = L298N::Direction::STOP;
        move_params.right_direction = L298N::Direction::STOP;
    }

    #define MAX_SPEED            (255)
    #define MAX_NORMALIZED_SPEED (142)

    int base_speed = sqrt(x * x + y * y);
    int normolized_speed = base_speed * MAX_SPEED / MAX_NORMALIZED_SPEED;
    if (x < 0) // turning left
    {
        move_params.left_speed = base_speed + x;
        move_params.right_speed = base_speed;
    }
    else if (x > 0) // turning right
    {
        move_params.left_speed = base_speed;
        move_params.right_speed = base_speed - x;
    }
    else // going straight
    {
        move_params.left_speed = base_speed;
        move_params.right_speed = base_speed;
    }

    // normalize speed - keep speed to [0, MAX_SPEED]
    int max_speed = max(move_params.left_speed, move_params.right_speed);
    if (max_speed > MAX_SPEED)
    {
        move_params.left_speed = move_params.left_speed * MAX_SPEED / max_speed;
        move_params.right_speed = move_params.right_speed * MAX_SPEED / max_speed;
    }
    return move_params;
}
