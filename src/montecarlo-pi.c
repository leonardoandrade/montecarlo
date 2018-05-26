#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "web_interface.h"

int COUNTER = 0;

void pseudo_random_point(int xmax, int ymax) { 
    int x = rand() % xmax;
    int y = rand() % ymax;
    int* ret = malloc(sizeof(int) * 2);
    ret[0] = x;
    ret[1] = y;
    updateCanvas(x,y);
}

void EMSCRIPTEN_KEEPALIVE reset() {
    emscripten_cancel_main_loop();
    resetCanvas();
    COUNTER=0;
    updateCounter(COUNTER);
}

void EMSCRIPTEN_KEEPALIVE stop() {
    emscripten_cancel_main_loop();
}

void loop() {
    pseudo_random_point(300, 300);
    COUNTER ++;
    updateCounter(COUNTER);    
}

void EMSCRIPTEN_KEEPALIVE start() {
    emscripten_set_main_loop(loop, 1000, 1);
}

int main(int argc, char ** argv) {
    resetCanvas();
    printf("WebAssembly module loaded\n");
}
