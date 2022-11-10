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
  Distance *distances;
  int qtdDistances;
  int idComponent;
} Vertex;

// Distância entre dois vértices, dados seus parâmetros
typedef struct distance {
  Vertex *v;
  double value;
} Distance;

// Grafo
typedef struct graph {
  Vertex *vertices;
  int qtdVertices;
  int qtdEdges;
} Graph;

Graph *createGraph(char *fileName);
void *setEuclidianDistances(Graph *graph, double *min, double *max);
void normalizeDistances(Graph *graph, double min, double max);
void setEdges(Graph *graph, double lim);

#endif