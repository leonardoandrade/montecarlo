#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>
#include "web_interface.h"
#include "model.h"
#include "geom_trig.h"
#include "random_numbers.h"
#include "montecarlo-pi.h"

int counter = 0;
DOMState dom; 

void initDom(int canvas_side) {
    dom.canvasSide = canvas_side;
    dom.totalInsideQuasi  = 0;
    dom.totalOutsideQuasi  = 0;
    dom.totalInsidePseudo  = 0;
    dom.totalOutsidePseudo  = 0;
}


void EMSCRIPTEN_KEEPALIVE reset() {
    emscripten_cancel_main_loop();
    reset_webpage(dom.canvasSide);
}

void EMSCRIPTEN_KEEPALIVE stop() {
    emscripten_cancel_main_loop();
}

void loop() {

    counter++;
    Point pointQuasi = quasi_random_point(dom.canvasSide, counter);
 
    if (isInside(pointQuasi, dom.canvasSide)) {
        dom.totalInsideQuasi++;
    } else {
        dom.totalOutsideQuasi++;
    }

    double pi_quasi = computePI(dom.totalInsideQuasi, dom.totalOutsideQuasi);

    Point pointPseudo = pseudo_random_point(dom.canvasSide);
 
    if (isInside(pointPseudo, dom.canvasSide)) {
        dom.totalInsidePseudo++;
    } else {
        dom.totalOutsidePseudo++;
    }

    double pi_pseudo = computePI(dom.totalInsidePseudo, dom.totalOutsidePseudo);

    update_webpage(
        pointQuasi.x, pointQuasi.y, dom.totalInsideQuasi, dom.totalOutsideQuasi, pi_quasi,
        pointPseudo.x, pointPseudo.y, dom.totalInsidePseudo, dom.totalOutsidePseudo, pi_pseudo
    ); 
}

void EMSCRIPTEN_KEEPALIVE start() {
    emscripten_set_main_loop(loop, 60, 1);
}

int main(int argc, char ** argv) {
    initDom(600);
    reset_webpage(dom.canvasSide);
    printf("WebAssembly module loaded\n");
}
