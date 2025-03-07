#include "request_handler.h"

int request_handler(int current_floor, int target_floor) {
    if (current_floor >= N_FLOORS || target_floor >= N_FLOORS) {
        return -1;
    }
    if (current_floor == -1 || target_floor == -1) {
        return -1;
    }
    
    
    status_set(); // Oppdater status-matrise


    if (current_floor == target_floor) {
        for (int floor = current_floor; floor < N_FLOORS; floor++) {
            if (status[floor][0] || status[floor][2]) {
                return floor;                           
            }
        }
        for (int floor = current_floor; floor >= 0; floor--) {
            if (status[floor][1] || status[floor][2]) {
                return floor;
            }
        }
    }

    if (current_floor < target_floor) {
        for (int floor = current_floor; floor < N_FLOORS; floor++) {
            if (status[floor][0] || status[floor][2]) {
                return floor;
            }
        }
    }

    if (current_floor > target_floor) {
        for (int floor = current_floor; floor >= 0; floor--) {
            if (status[floor][1] || status[floor][2]) {
                return floor;
            }
        }
    }

    return -1;
}
