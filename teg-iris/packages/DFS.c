#include <stdio.h>
#include "../headers/DFS.h"
#include "../headers/handleGraph.h"

void depthFirstSearch(Vertex *v, int idComponent) {
  if (v->idComponent == -1) {
    v->idComponent = idComponent;
    for (int i = 0; i < v->deg; i++) {
      Vertex *currentEdge = v->edges[i];
      depthFirstSearch(currentEdge, idComponent);
    }
  }
}

void markAllComponents(Graph *graph) {
  int idComponent = 1;
  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    if (currentVertex->idComponent != -1)
      continue;

    depthFirstSearch(currentVertex, idComponent);
    idComponent++;
  }
}

