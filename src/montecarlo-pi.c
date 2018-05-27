#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "web_interface.h"
#include "model.h"
#include "geom_trig.h"

int COUNTER = 0;
DOMState dom; 

void initDom(int canvas_side) {
    dom.canvasSide = canvas_side;
    dom.totalInside  = 0;
    dom.totalOutside  = 0;
}

Point pseudo_random_point(int max) { 
    Point ret;
    ret.x = rand() % max;
    ret.y = rand() % max;
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
    dom.lastPoint = pseudo_random_point(dom.canvasSide);

    if (isInside(dom.lastPoint, dom.canvasSide)) {
        dom.totalInside++;
    } else {
        dom.totalOutside++;
    }
    update_webpage(dom); 
}

void EMSCRIPTEN_KEEPALIVE start() {
    emscripten_set_main_loop(loop, 10000, 1);
}

int main(int argc, char ** argv) {
    reset_webpage();
    printf("WebAssembly module loaded\n");
}
