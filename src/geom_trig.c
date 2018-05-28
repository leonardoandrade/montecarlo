#include "model.h"
#include <stdbool.h>
#include <math.h>

bool isInside(Point point, int canvas_side) {
  double distance_from_center = sqrt((point.x * point.x) + (point.y * point.y));
  return distance_from_center < canvas_side;
}

double computePI(int totalInside, int totalOutside) {
  if((totalInside + totalOutside) > 0) {
   
  double ret = 1.0;
  ret =  4.0 * ((totalInside) / (totalInside + totalOutside));
  return ret;
  }
}
