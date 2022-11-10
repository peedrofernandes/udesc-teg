#include "structs.h"

#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

// Vértice do grafo, com todos os seus parâmetros
typedef struct vertex {
  int id;
  double a1;
  double a2;
  double a3;
  double a4;
  struct vertex *edges;
  int deg;
  int idComponent;
} Vertex;

// Distância entre dois vértices, dados seus parâmetros
typedef struct distance {
  Vertex *v1;
  Vertex *v2;
  double value;
} Distance;

// Grafo
typedef struct graph {
  Vertex *vertices;
  int qtdVertices;
  int qtdEdges;
} Graph;

Graph *createGraph(char *fileName);
Distance *getEuclidianDistances(Graph *graph, double *min, double *max, int *qtdDistances);
void normalizeDistances(Distance *distances, double min, double max, int qtdDistances);
void setEdges(Graph *graph, double lim, Distance *normalizedDistances, int qtdDistances);

#endif