/**
 * @file elevator_control.h
 * @brief Elevator control system.
 */

#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include "driver/elevio.h"
#include "request_handler.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Elevator state enumeration.
 * @details This enumeration defines the possible states of the elevator.
 */
typedef enum {
    IDLE,        /**< Idle state */
    MOVING_UP,   /**< Moving up state */
    MOVING_DOWN, /**< Moving down state */
    DOOR_OPEN,   /**< Door open state */
    STOPPED      /**< Stopped state */
} ElevatorState;

/**
 * @brief Elevator structure.
 * @details This structure holds the current state, floor, target floor, and door status of the elevator.
 */
typedef struct {
    ElevatorState state; /**< Elevator state */
    int current_floor;   /**< Current floor */
    int target_floor;    /**< Target floor */
    int door_open;       /**< Door open status */
} Elevator;

/**
 * @brief Initialize the elevator.
 * @details The elevator is initialized to a known state, with exception handling for the case where the elevator is in an unknown state.
 * @return void
 */
void elevator_init();

/**
 * @brief Move the elevator.
 * @return void
 */
void elevator_move();

/**
 * @brief Update the elevator.
 * @details Update the elevator state based on the next target floor.
 * @return void
 */
void elevator_update();

/**
 * @brief Handle an emergency stop.
 * @details Stop the elevator reset state and target.
 * @return void
 */
void handle_emergency_stop();

/**
 * @brief Handle an obstruction.
 * @details Stop the elevator and open the door.
 * @return void
 */
void handle_obstruction();

/**
 * @brief Clear the floor button lamps.
 * @details Clear the floor button lamps for a given floor.
 * @param floor
 * @return void
 */
void clear_floor_button_lamps(int floor);

#endif // ELEVATOR_CONTROL_H