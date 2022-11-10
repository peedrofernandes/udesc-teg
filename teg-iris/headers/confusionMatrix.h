#include "handleGraph.h"

#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

typedef struct vertexComponent {
  int idVertex;
  int idComponent;
} VertexComponent;

typedef struct component {
  int id;
  Vertex *vertices;
} Component;

#endif