#include "model.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>


bool isInside(Point point, int canvas_side) {
  float distance_from_center = sqrt((point.x * point.x) + (point.y * point.y));
  return distance_from_center < (canvas_side - 0.5);
}

double computePI(int totalInside, int totalOutside) {
  double ret = 1.0;
  if((totalInside + totalOutside) > 0) {
    ret =  4.0 * (((double)totalInside) / ((double)totalInside + (double)totalOutside));
  }
  return ret;
  
}
