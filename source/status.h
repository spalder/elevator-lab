/**
 * @file status.h
 * @brief Handle the status of the elevator.
 */

#ifndef STATUS_H
#define STATUS_H

#include "driver/elevio.h"

extern int status[N_FLOORS][N_BUTTONS]; /**< Status matrix of the elevator buttons. */

/**
 * @brief Initialize the status matrix.
 * @details Initialize the status matrix to zero.
 * @return void
 */
void status_init();

/**
 * @brief Set the status matrix.
 * @details Set the status matrix based on the button presses.
 * @return void
 */
void status_set();

#endif // STATUS_H
