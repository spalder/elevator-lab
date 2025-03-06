#include "timer.h"

static time_t start_time;
static int duration = 0;

void timer_start(int seconds)
{
    start_time = time(NULL);
    duration = seconds;
}

int timer_stopped()
{
    return (time(NULL) - start_time >= duration);
}
