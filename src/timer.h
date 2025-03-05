#ifndef TIMER_H
#define TIMER_H

#include <time.h>

static time_t start_time;
static int duration;

void timer_start(int seconds);

int timer_stopped();

#endif // TIMER_H