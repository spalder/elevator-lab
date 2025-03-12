#include "elevator_control.h"

Elevator elevator = {
    .state = IDLE,
    .current_floor = -1,
    .target_floor = -1,
    .door_open = 0
};

void elevator_init()
{
    elevio_init();
    printf("Initializing elevator\n");

    elevator.state = IDLE;
    elevator.current_floor = elevio_floorSensor();
    elevator.target_floor = -1;
    elevator.door_open = 0;

    status_init();

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
        elevator.state = IDLE;
    }

    elevio_floorIndicator(elevator.current_floor);
    printf("Elevator initialized at floor %d\n", elevator.current_floor);
}

void elevator_move()
{
    if (elevio_stopButton()) {
        handle_emergency_stop();
        return;
    }

    if (elevio_obstruction() && (elevator.state == DOOR_OPEN || elevator.door_open)) {
        handle_obstruction();
        return;
    }

    const int floor = elevio_floorSensor();

    if (floor != -1) 
    {
        if (floor != elevator.current_floor)
        {
            elevator.current_floor = floor;
            elevio_floorIndicator(elevator.current_floor);
            printf("Elevator at floor %d\n", elevator.current_floor);
            
            if (floor == elevator.target_floor) 
            {
                elevio_motorDirection(DIRN_STOP);
                elevator.state = DOOR_OPEN;
                elevator.door_open = 1;
                elevio_doorOpenLamp(1);
                printf("Stopping at floor %d, door opening\n", floor);

                clear_floor_button_lamps(floor);

                timer_start(3);
                return;
            }
        }
    }

    else if (elevator.door_open)
    {
        elevator.door_open = 0; 
        elevio_doorOpenLamp(0);
    }

    if (elevator.state == DOOR_OPEN && timer_stopped()) 
    {
        printf("Door closing\n");
        elevator.door_open = 0;
        elevio_doorOpenLamp(0);
        
        int new_target = request_handler(elevator.current_floor, -1);
        
        if (new_target != -1 && new_target != elevator.current_floor) 
        {
            elevator.target_floor = new_target;
            
            if (new_target > elevator.current_floor) 
            {
                elevator.state = MOVING_UP;
                elevio_motorDirection(DIRN_UP);
                printf("Moving up to floor %d\n", elevator.target_floor);
            } 
            else 
            {
                elevator.state = MOVING_DOWN;
                elevio_motorDirection(DIRN_DOWN);
                printf("Moving down to floor %d\n", elevator.target_floor);
            }
        } 
        else 
        {
            elevator.state = IDLE;
            elevator.target_floor = -1;
            printf("Door closed, elevator IDLE\n");
        }
    }
}

void elevator_update()
{
    const int next_target_floor = request_handler(elevator.current_floor, elevator.target_floor);

    if (next_target_floor == -1 || elevator.state == STOPPED) 
    {
        printf("No new target floor\n");
        return;
    }

    /* Apply new next target if the elevator is ready */
    if (elevator.state == IDLE || (elevator.state == DOOR_OPEN && elevator.current_floor != next_target_floor)) 
    {
        elevator.target_floor = next_target_floor;
        printf("New target floor: %d\n", elevator.target_floor);
        
        if (elevator.current_floor == elevator.target_floor) 
        {
            elevio_motorDirection(DIRN_STOP);
            elevator.state = DOOR_OPEN;
            elevator.door_open = 1;
            elevio_doorOpenLamp(1);
            clear_floor_button_lamps(elevator.current_floor);
            
            timer_start(3);
        }
        else if (elevator.current_floor != -1) 
        {
            if (elevator.target_floor > elevator.current_floor && timer_stopped()) 
            {
                elevio_motorDirection(DIRN_UP);
                elevator.state = MOVING_UP;
                printf("Moving up to floor %d\n", elevator.target_floor);
            } 
            else if (elevator.target_floor < elevator.current_floor && timer_stopped()) 
            {
                elevio_motorDirection(DIRN_DOWN);
                elevator.state = MOVING_DOWN;
                printf("Moving down to floor %d\n", elevator.target_floor);
            }
        }
    }
}

void handle_emergency_stop()
{
    printf("Emergency stop button pressed\n");
    elevio_motorDirection(DIRN_STOP);
    elevator.state = STOPPED;
    elevio_stopLamp(1);

    for (int f = 0; f < N_FLOORS; f++) {
        clear_floor_button_lamps(f);
    }

    if (elevator.current_floor != -1) {
        elevator.door_open = 1;
        elevio_doorOpenLamp(1);
    }

    while (elevio_stopButton()) {
        usleep(100000);
    }

    elevio_stopLamp(0);
    
    if (elevator.current_floor != -1) 
    {
        timer_start(3);
    } 
    else 
    {
        elevator.state = IDLE;
        elevator.target_floor = -1;
    }
}

void handle_obstruction()
{
    printf("Obstruction detected, door held open\n");
    
    while (elevio_obstruction()) 
    {
        elevator.door_open = 1;
        elevio_doorOpenLamp(1);
        usleep(100000);
    }
    
    printf("Obstruction cleared, door closing in 3 seconds\n");
    timer_start(3);
}

void clear_floor_button_lamps(int floor)
{
    for (int b = 0; b < N_BUTTONS; b++) 
    {
        if ((floor == 0 && b == BUTTON_HALL_DOWN) || (floor == N_FLOORS - 1 && b == BUTTON_HALL_UP)) 
        {
            continue;
        }
        elevio_buttonLamp(floor, b, 0);

        status[floor][b] = 0;
    }
}
