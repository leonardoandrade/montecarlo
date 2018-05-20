#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    printf("WebAssembly module loaded\n");
}

int CALL_COUNTER = 0;

int EMSCRIPTEN_KEEPALIVE random_number() {
    //srand ( time(NULL) );
    CALL_COUNTER ++;
    printf("random_number called. %d.\n", CALL_COUNTER);
    int ret = rand() % 1000 + 1;
    return ret;
}
