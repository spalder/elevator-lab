#include "timer.h"

static time_t timer_end_time;

void timer_start(int duration_seconds)
{
    timer_end_time = time(NULL) + duration_seconds;
}

int timer_stopped()
{
    return time(NULL) >= timer_end_time;
}
