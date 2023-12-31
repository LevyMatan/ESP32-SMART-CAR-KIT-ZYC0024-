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

// initialize motors
L298N left_motor(gpLs, gpLf, gpLb);
L298N right_motor(gpRs, gpRf, gpRb);

static void DEBUG_print_direction(L298N::Direction direction) {
  switch (direction) {
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
void DEBUG_print_move_params(move_params_t *p_move_params) {
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
void wheel_action(move_params_t *p_move_params) {
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
void spin(int speed, spin_direction_t direction) {
  move_params_t move_params = {};
  move_params.right_speed = speed;
  move_params.left_speed = speed;
  if (RIGHT_E == direction) {
    move_params.left_direction = L298N::Direction::FORWARD;
    move_params.right_direction = L298N::Direction::BACKWARD;
  } else {
    move_params.left_direction = L298N::Direction::BACKWARD;
    move_params.right_direction = L298N::Direction::FORWARD;
  }
  wheel_action(&move_params);
}

/**
 * @brief Get the move params from joystick coordinates
 *        Constraints:
 *        left_speed and right_speed values should be in the range [0, 255].
 *
 * @param speed
 * @param turn
 * @return move_params_t
 */
move_params_t get_move_params_from_joystick_coordinates(int speed, int turn) {
  move_params_t move_params = {};
  // Compute direction.
  L298N::Direction direction;
  if (speed > 0) {
    direction = L298N::Direction::FORWARD;
  } else if (speed < 0) {
    direction = L298N::Direction::BACKWARD;
  } else {
    direction = L298N::Direction::STOP;
  }
  move_params.left_direction = direction;
  move_params.right_direction = direction;

#define MAX_SPEED (255)
#define MAX_NORMALIZED_SPEED (100)
  speed = abs(speed);
  speed = (speed > MAX_NORMALIZED_SPEED) ? MAX_NORMALIZED_SPEED : speed;
  turn = (abs(turn) > MAX_NORMALIZED_SPEED) ? MAX_NORMALIZED_SPEED : turn;
  int normolized_speed = speed * MAX_SPEED / MAX_NORMALIZED_SPEED;
  int normolized_turn = abs(turn) * MAX_SPEED / MAX_NORMALIZED_SPEED;

  move_params.left_speed = normolized_speed;  // 96
  move_params.right_speed = normolized_speed; // 96
  int decreased_speed = ((normolized_speed - normolized_turn) < 0)
                            ? 0
                            : (normolized_speed - normolized_turn);
  if (turn < 0) // turning left ==> decrease left speed
  {
    move_params.left_speed = decreased_speed;
  } else if (turn > 0) // turning right ==> decrease right speed
  {
    move_params.right_speed = decreased_speed;
  }

  return move_params;
}

MOVE_status_e verify_move_params(move_params_t *p_move_params) {
  if (p_move_params->left_speed < 0 || p_move_params->left_speed > MAX_SPEED) {
    return MOVE_STATUS_INVALID_LEFT_SPEED_E;
  }
  if (p_move_params->right_speed < 0 ||
      p_move_params->right_speed > MAX_SPEED) {
    return MOVE_STATUS_INVALID_RIGHT_SPEED_E;
  }
  return MOVE_STATUS_OK_E;
}
