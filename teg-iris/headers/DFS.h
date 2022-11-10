#include "handleGraph.h"

#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

typedef struct component Component;

struct component {
  int id;
  int *ids;
};

void depthFirstSearch(Vertex *v, int idComponent);
void markAllComponents(Graph *graph);

#endif