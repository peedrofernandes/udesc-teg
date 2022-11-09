#include "../headers/exportData.h"
#include <stdlib.h>
#include <stdio.h>

void exportGraph(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");

  fprintf(file, "%d\n", graph->qtdEdges);

  Edge *currentEdge = graph->firstEdge;
  while (currentEdge != NULL) {
    fprintf(file, "%d, %d\n", currentEdge->v1, currentEdge->v2);
    currentEdge = currentEdge->next;
  }

  fclose(file);
}

void exportDistances(char *fileName, DistancesList *list) {
  FILE *file = fopen(fileName, "wt");

  Distance *currentDistance = list->firstDistance;

  while (currentDistance != NULL) {
    fprintf(file, "%d, %d, %.8lf\n", currentDistance->v1, currentDistance->v2, currentDistance->value);
    currentDistance = currentDistance->next;
  }

  fclose(file);
}

void exportDegrees(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");

  Vertex *currentVertex = graph->firstVertex;

  while (currentVertex != NULL) {
    fprintf(file, "%d: %d\n", currentVertex->id, currentVertex->deg);
    currentVertex = currentVertex->next;
  }

  fclose(file);
}