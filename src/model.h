#ifndef MODEL_H
#define MODEL_H

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int canvasSide;
  int totalInside;
  int totalOutside;
  Point lastPoint;
} DOMState;

#endif