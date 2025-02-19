#include "elevator_control.h"

current_floor = -1;
current_state = IDLE;

void elevator_init()
{
    elevio_init();
    current_state = IDLE;
}

void elevator_update()
{
    switch (current_state)
    {
        case IDLE:

        case MOVING:
            if (elevio_floorSensor() != -1)
            {
                current_floor = elevio_floorSensor();
                elevio_floorIndicator(current_floor);
                if (/* <should stop> */)
                {
                    elevio_motorDirection(DIRN_STOP);
                    timer_start(3);
                    current_state = DOOR_OPEN;
                }
            }
            break;

        case DOOR_OPEN:
            if (timer_stopped())
            {
                elevio_doorOpenLamp()
            }
        case STOPPED:
            
    }
}

void elevator_move()
{
    int next_floor = /* <get next floor request from algo> */;
    next_floor > current_floor ? elevio_motorDirection(DIRN_UP) : elevio_motorDirection(DIRN_DOWN);
}
