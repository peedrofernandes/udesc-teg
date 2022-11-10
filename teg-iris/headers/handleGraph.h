#include "structs.h"

#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

typedef struct vertex Vertex;
typedef struct distance Distance;
typedef struct graph Graph;

// Grafo
struct graph {
  Vertex **vertices;
  int qtdVertices;
  int qtdEdges;
};

// Vértice do grafo, com todos os seus parâmetros
struct vertex {
  int id;
  double a1;
  double a2;
  double a3;
  double a4;
  struct vertex **edges;
  int deg;
  Distance **distances;
  int qtdDistances;
  int idComponent;
};

// Distância entre dois vértices, dados seus parâmetros
struct distance {
  Vertex *v;
  double value;
};

Graph *createGraph(char *fileName);
void *setEuclidianDistances(Graph *graph, double *min, double *max);
void normalizeDistances(Graph *graph, double min, double max);
void setEdges(Graph *graph, double lim);

#endif