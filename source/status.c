#include "status.h"

void status_init() {
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < N_BUTTONS; j++) {
            status[i][j] = 0;
        }
    }
}

void status_set() {
    int a;
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button < N_BUTTONS; button++) {
            a = elevio_callButton(floor, button);
            status[i][j] = a;
            elevio_buttonLamp(floor, button, a);
        }
    }
}
