#include <time.h>

static time_t start_time;
static int duration;

void timer_start(int seconds);

int timer_stop()
{
    return (time(NULL) - start_time) >= duration;
}
