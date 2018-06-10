#include "model.h"
#include <stdlib.h>
#include <stdio.h>

#define PRIME_X 5
#define PRIME_Y 17

Point pseudo_random_point(int max) { 
    Point ret;
    ret.x = rand() % max;
    ret.y = rand() % max;
    return ret;
}

float van_der_corput_number(int n, int prime_base) {
  float ret =  0.0;
  float denom = 1.0;
  while(n > 0) {
    denom = denom * prime_base;
    float rem = n % prime_base;
    n = n / prime_base;
    ret = ret + (rem / denom);
  }
  return ret;
}

Point quasi_random_point(int max, int seq) {
  Point ret;
  ret.x = (double)van_der_corput_number(seq, PRIME_X) * (double)max;
  ret.y = (double)van_der_corput_number(seq, PRIME_Y) * (double)max;
  return ret;
}

#ifdef MONTECARLO_PI
int main() {
  printf("Quasi-random\n");
  for(int i=0; i<10; i++) {
    Point p1 = quasi_random_point(300, i);
    printf("p%d = (%d, %d)\n", i, p1.x, p1.y);
  }

  printf("\n");
  printf("Pseudo-random\n");
  for(int i=0; i<10; i++) {
    Point p1 = pseudo_random_point(300);
    printf("p%d = (%d, %d)\n", i, p1.x, p1.y);
  }
}
#endif
