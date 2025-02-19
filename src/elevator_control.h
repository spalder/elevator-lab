#pragma once

#include "driver/elevio.h"

typedef enum {
    IDLE,
    MOVING,
    DOOR_OPEN,
    STOPPED
} ElevatorState;

static ElevatorState current_state;
static int current_floor;

void elevator_init();

void elevator_update();

voie elevator_move();
