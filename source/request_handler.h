/**
 * @file request_handler.h
 * @brief Elevator request handler.
 */

#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "status.h"
#include "elevator_control.h"

/**
 * @brief Handle elevator requests.
 * @details Find the best possible target floor based on the current floor and target floor.
 * @param current_floor The current floor of the elevator.
 * @param target_floor The current target floor of the elevator.
 * @return Next target floor.
 */
int request_handler(int current_floor, int target_floor);

#endif // REQUEST_HANDLER_H
