#pragma once

#define N_FLOORS 4

static int queue[N_FLOORS][3];


void queue_add_from_floor(int[3] request);
void queue_add_from_elevator(int request);
void queue_iterate();
void queue_append();

bool queue_floor_present(int floor);

void queue_hitchikers(int start, int goal);
