#ifndef MODEL_H
#define MODEL_H

typedef struct {
  double x;
  double y;
} Point;

typedef struct {
  int canvasSide;
  int totalInsideQuasi;
  int totalOutsideQuasi;
  int totalInsidePseudo;
  int totalOutsidePseudo;
} DOMState;

#endif