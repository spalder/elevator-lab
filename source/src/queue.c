#include <queue.h>


void clear_temp() {
    for (int j = 0; j < 3; j++) {
        temp_up[j] = NULL;
        temp_down[j] = NULL;
}



void queue_iterate() {
    for (int j = 0; j < 4; j++) {
        queue[0][j] = queue[1][j];
        queue[1][j] = queue[2][j];
        queue[2][j] = queue[3][j];
        queue[3][j] = 0;
    }
    queue[3][0] = NULL;
};



void queue_append(int[3] floor) {
    for (int j = 0; j < 4; j++) {
        if (queue[j][0] == floor[0]) {
            queue[j][1] = queue[j][1] || floor[1];
            queue[j][2] = queue[j][2] || floor[2];
        return;
        }
    
    bool a = true;
    int i = -1;
    while (a) {
        i++;
        if (queue[i][0] == NULL) {
            a = false;
        }
    }
    queue[i][0] = floor[0];
    queue[i][1] = floor[1];
    queue[i][2] = floor[2];
};


//tror jeg goofa litt på de siste to her, hvertfall ikke ferdig
void queue_sort_up() {
    clear_temp();
    int i = 0

    for (int j = 1; j < 4; j++) {
        if (queue[j][1]) {
            temp_up[i][0] = queue[j][0];
            temp_up[i][1] = queue[j][1];
            temp_up[i][2] = queue[j][2];
            i++;
        }
};



void queue_sort_down() {
    clear_temp();
    int i = 0

    for (int j = 1; j < 4; j++) {
        if (queue[j][2]) {
            temp_down[i][0] = queue[j][0];
            temp_down[i][1] = queue[j][1];
            temp_down[i][2] = queue[j][2];
            i++;
        }   
};








      
