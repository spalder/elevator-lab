#include "status.h"

int status[N_FLOORS][N_BUTTONS];

void status_init() {
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < N_BUTTONS; j++) {
            status[i][j] = 0;
        }
    }
}

void status_set() {
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button < N_BUTTONS; button++) {
            if ((floor == 0 && button == BUTTON_HALL_DOWN) ||
                (floor == N_FLOORS - 1 && button == BUTTON_HALL_UP)) {
                continue;
            }

            int button_pressed = elevio_callButton(floor, button);
            if (button_pressed)
            {
                status[floor][button] = button_pressed;
                elevio_buttonLamp(floor, button, button_pressed);
            }
       }
    }
}
