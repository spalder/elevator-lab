#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include "driver/elevio.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    DOOR_OPEN,
    STOPPED
} ElevatorState;

typedef struct {
    ElevatorState state;
    int current_floor;
    int target_floor;
    int door_open;
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
 * @param[in] next_target_floor 
 * @return void
 */
void elevator_update(int next_target_floor);

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

#endif // ELEVATOR_CONTROL_H
