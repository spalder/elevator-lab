#include "timer.h"

duration = 0;

void timer_start(int seconds)
{
    start_time = time(NULL);
    duration = seconds;
}
