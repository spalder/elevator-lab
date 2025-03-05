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

Elevator elevator;

void elevator_init();

void elevator_update();

void elevator_move();

void handle_emergency_stop();

void handle_obstruction();

#endif // ELEVATOR_CONTROL_H
