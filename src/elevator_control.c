#include "elevator_control.h"

void elevator_init()
{
    elevio_init();
    printf("Initializing elevator\n");

    elevator.state = IDLE;
    elevator.current_floor = elevio_floorSensor();
    elevator.target_floor = -1;
    elevator.door_open = 0;

    if (elevator.current_floor == -1)
    {
        /* Undefined initial state */
        elevio_motorDirection(DIRN_DOWN);
        elevator.state = MOVING_DOWN;
        
        /* Wait for elevator to reach known floor */
        while ((elevator.current_floor = elevio_floorSensor()) == -1)
        {
            usleep(100000);
        }

        elevio_motorDirection(DIRN_STOP);
    }

    elevio_floorIndicator(elevator.current_floor);
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
