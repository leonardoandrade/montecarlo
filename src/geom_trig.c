#include "model.h"
#include <stdbool.h>
#include <math.h>

bool isInside(Point point, int canvas_side) {
  double distance_from_center = sqrt((point.x * point.x) + (point.y * point.y));
  return distance_from_center < canvas_side;
}