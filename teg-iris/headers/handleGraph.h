#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

// Distância entre dois vértices, dados seus parâmetros
typedef struct distance {
  int v1;
  int v2;
  double value;
  struct distance *next;
} Distance;

// Lista de distâncias
typedef struct distancesList {
  Distance *firstDistance;
  int qtdDistances;
} DistancesList;

// Vértice do grafo, com todos os seus parâmetros
typedef struct vertex {
  int id;
  int deg;
  double a1;
  double a2;
  double a3;
  double a4;
  struct vertex *next;
} Vertex;

// Aresta entre dois vértices
typedef struct edge {
  int v1;
  int v2;
  struct edge *next;
} Edge;

typedef struct graph {
  Vertex *firstVertex;
  Edge *firstEdge;
  int qtdVertices;
  int qtdEdges;
} Graph;

Graph *createGraph(char *fileName);
DistancesList *getEuclidianDistances(Graph *graph, double *min, double *max);
void normalizeDistances(DistancesList *distancesList, double min, double max);
void setEdges(Graph *graph, DistancesList *normalizedDistances, double lim);

#endif