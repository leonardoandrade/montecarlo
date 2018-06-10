#ifndef MODEL_H
#define MODEL_H

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int canvasSide;
  int totalInsideQuasi;
  int totalOutsideQuasi;
  int totalInsidePseudo;
  int totalOutsidePseudo;
} DOMState;

#endif