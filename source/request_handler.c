#include "request_handler.h"

int request_handler(int current_floor, int target_floor) {
    printf("Request handler called\n");
    printf("Current floor: %d, Target floor: %d\n", current_floor, target_floor);

    if ((current_floor >= N_FLOORS && current_floor != -1) || (target_floor >= N_FLOORS && target_floor != -1)) 
    {
        printf("Invalid floor, returning -1 from request handler\n");
        return -1;
    }

    int any_pressed = 0;
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if ((f == 0 && b == BUTTON_HALL_DOWN) || 
                (f == N_FLOORS-1 && b == BUTTON_HALL_UP)) {
                continue;
            }
            if (status[f][b]) {
                any_pressed = 1;
                break;
            }
        }
        if (any_pressed) 
        {
            break;
        }
    }

    if (!any_pressed) {
        return target_floor;
    }

    /* At target floor, or have no target */
    if (current_floor == target_floor || target_floor == -1) 
    {
        for (int floor = (current_floor != -1) ? current_floor + 1 : 0; floor < N_FLOORS; floor++) 
        {
            if (status[floor][BUTTON_HALL_UP] || status[floor][BUTTON_HALL_DOWN] || status[floor][BUTTON_CAB]) 
            {
                return floor;                           
            }
        }

        for (int floor = (current_floor != -1) ? current_floor - 1 : 0; floor >= 0; floor--) 
        {
            if (status[floor][BUTTON_HALL_UP] || status[floor][BUTTON_HALL_DOWN] || status[floor][BUTTON_CAB]) 
            {
                return floor;
            }
        }
    }

    /* Moving up */
    else if (current_floor < target_floor) 
    {
        for (int floor = (current_floor != -1) ? current_floor + 1 : 0; floor < target_floor; floor++) 
        {
            if (status[floor][BUTTON_HALL_UP] || status[floor][BUTTON_HALL_DOWN] || status[floor][BUTTON_CAB]) 
            {
                return floor;
            }
        }
    }

    /* Moving down */
    else if (current_floor > target_floor) 
    {
        for (int floor = (current_floor != -1) ? current_floor - 1 : N_FLOORS - 1; floor >= target_floor; floor--) 
        {
            if (status[floor][BUTTON_HALL_UP] || status[floor][BUTTON_HALL_DOWN] || status[floor][BUTTON_CAB]) 
            {
                return floor;
            }
        }
    }

    if (target_floor >= 0 && target_floor < N_FLOORS) 
    {
        return target_floor;
    }

    /* Last resort, find any call */
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        for (int button = 0; button < N_BUTTONS; button++)
        {
            if ((floor == 0 && button == BUTTON_HALL_DOWN) || 
                (floor == N_FLOORS - 1 && button == BUTTON_HALL_UP)) 
            {
                continue;
            }

            if (status[floor][button]) 
            {
                return floor;
            }
        }
    }

    return -1;
}
