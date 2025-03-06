#pragma once

#include "driver/elevio.h"

// Status of the elevator is a matrix of booleans and is in the following format:
// 
// up_light | down_light | cab_light


int status[4][3];

void status_init();
void status_set();
