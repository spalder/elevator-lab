#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"

int main() {
    printf("=== Elevator Control System ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevator_init();

    while (!elevio_stopButton()) {
        int next_target = -1;
        for (int f = 0; f < N_FLOORS; f++) {
            for (int b = 0; b < N_BUTTONS; b++) {
                if (elevio_callButton(f, b)) {
                    elevio_buttonLamp(f, b, 1);
                    next_target = f;
                }
            }
        }

        elevator_update(next_target);
        
        elevator_move();
        
        usleep(10000);
    }
    
    elevio_motorDirection(DIRN_STOP);
    printf("Elevator stopped. Exiting program.\n");
    return 0;
}
