#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"

int main() 
{
    printf("=== Elevator Control System ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevator_init();

    while (!elevio_stopButton()) 
    {
        status_set();

        elevator_update();
        
        elevator_move();
        
        usleep(10000);
    }
    
    elevio_motorDirection(DIRN_STOP);
    printf("Elevator stopped. Exiting program.\n");
    return 0;
}
