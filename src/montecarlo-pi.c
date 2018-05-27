#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "web_interface.h"
#include "model.h"

int COUNTER = 0;
DOM dom; 

void initDom(int canvas_width, int canvas_height) {
    dom.canvas_width = canvas_width;
    dom.canvas_height = canvas_height;
    dom.total_inside  = 0;
    dom.total_outside  = 0;
}

int* pseudo_random_point(int xmax, int ymax) { 
    int x = rand() % xmax;
    int y = rand() % ymax;
    int* ret;//malloc(sizeof(int) * 2);
    ret[0] = x;
    ret[1] = y;
    return ret;
}


void EMSCRIPTEN_KEEPALIVE reset() {
    emscripten_cancel_main_loop();
    reset_webpage();
}

void EMSCRIPTEN_KEEPALIVE stop() {
    emscripten_cancel_main_loop();
}

void loop() {
    int* points = pseudo_random_point(300, 300);
    COUNTER ++;
    dom.total_inside++;

    update_webpage(points[0], points[1], COUNTER);    
}

void EMSCRIPTEN_KEEPALIVE start() {
    emscripten_set_main_loop(loop, 10000, 1);
}

int main(int argc, char ** argv) {
    reset_webpage();
    printf("WebAssembly module loaded\n");
}
