/**
 * @file timer.h
 * @brief Timer for elevator control system.
 */

#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
 * @brief Start a timer.
 * @details Start a timer with a given duration in seconds.
 * @param duration_seconds The duration of the timer in seconds.
 * @return void
 */
void timer_start(int duration_seconds);

/**
 * @brief Check if the timer has stopped.
 * @details Check if the timer has stopped.
 * @return 1 if the timer has stopped, 0 otherwise.
 */
int timer_stopped();

#endif // TIMER_H