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
    printf("Elevator initialized at floor %d\n", elevator.current_floor);
}

void elevator_move()
{
    int floor = elevio_floorSensor();
    if (floor != -1)
    {
        elevator.current_floor = floor;
        elevio_floorIndicator(elevator.current_floor);
        printf("Elevator reached floor %d\n", elevator.current_floor);

        if (elevator.current_floor == elevator.target_floor)
        {
            elevio_motorDirection(DIRN_STOP);
            elevator.state = DOOR_OPEN;
            elevator.door_open = 1;
            elevio_doorOpenLamp(1);
            sleep(3);
            elevator.door_open = 0;
            elevio_doorOpenLamp(0);
            elevator.state = IDLE;
            elevator.target_floor = -1;
        }
    }

    if (elevio_stopButton())
    {
        printf("Emergency stop button pressed\n");
        elevio_motorDirection(DIRN_STOP);
        elevator.state = STOPPED;
        elevio_stopLamp(1);

        /* Clear all orders in queue... */

        while (elevio_stopButton())
        {
            usleep(100000);
        }

        elevio_stopLamp(0);
        elevator.state = IDLE;
        elevator.target_floor = -1;
    }

    if (elevio_obstruction())
    {
        printf("Obstruction detected\n");
        elevio_motorDirection(DIRN_STOP);
        elevator.state = STOPPED;
        elevio_doorOpenLamp(1);
        while (elevio_obstruction())
        {
            usleep(100000);
        }
        sleep(3);
        elevio_doorOpenLamp(0);
    }
}
