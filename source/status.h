#pragma once

#include "driver/elevio.h"

// Status of the elevator is a matrix of booleans and is in the following format:
// 
// up_light | down_light | cab_light


extern int status[N_FLOORS][N_BUTTONS];

void status_init();
void status_set();
