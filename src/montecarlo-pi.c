#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>

int COUNTER = 0;

char* CANVAS_ID = "canvas";

//function resetCanvas() 
EM_JS(void, resetCanvas, (), {
    const canvas  = document.getElementById("canvas");
    const context = canvas.getContext('2d');
    context.clearRect(0, 0, canvas.width, canvas.height);
    const centerX = canvas.width / 2;
    const centerY = canvas.height / 2;
    const radius  = canvas.height / 2;
  
    context.beginPath();
    context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
    context.fillStyle = '#ADD8E6';
    context.fill();
});

//function updateCounter() 
EM_JS(void, updateCounter, (int count), {
    const field = document.getElementById('iterations');
    field.innerHTML = "" + count;
});


//function updateCanvas(x,y)
EM_JS(void, updateCanvas, (int x, int y), {
    console.log("point = [%d, %d]", x, y);
    const ctx = document.getElementById("canvas").getContext("2d");
    ctx.fillStyle = "rgba(200, 100, 100, 0.5)";
    ctx.beginPath(); 
    ctx.arc(x, y, 1, 0, Math.PI * 2, true);
    ctx.fill(); 
});

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
