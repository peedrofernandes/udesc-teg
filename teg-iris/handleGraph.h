#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

// Distância entre dois vértices, dados seus parâmetros
typedef struct distance {
  int v1;
  int v2;
  double value;
} Distance;

typedef struct distancesList {
  Distance *first;
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

// // Lista de arestas de um grafo
// typedef struct edgeList {
//   Edge *first;
//   int qtdEdges;
// } EdgeList;

typedef struct graph {
  Vertex *firstVertex;
  Edge *firstEdge;
  int qtdVertices;
  int qtdEdges;
} Graph;

// // Funções relacionadas à Vértices
// Vertex *getVertices(char *fileName, int qtdVertices);
// void printVertices(Vertex *vertices, int qtdVertices);

// // Funções relacionadas às distâncias euclidianas e normalizadas
// Distance *getEuclidianDistances(Vertex *vertices, int qtdVertices, double *max, double *min);
// Distance *getNormalizedDistances(Distance *distances, int qtdVertices, double max, double min);
// void printDistances(Distance *distances, int qtdVertices);
// void exportDistances(char *fileName, Distance *distances, int qtdVertices);

// // Funções relacionadas à obtenção dos grafos
// Graph *createGraph(int qtdVertices, Distance *normalizedDistances, int qtdDistances, double lim);
// void printGraphEdges(Graph *graph);
// void exportGraphEdges(char *fileName, Graph *graph);
// void exportGraphviz(char *fileName, Graph *graph);

DistancesList getEuclidianDistances(char *fileName, int *min, int *max);
void normalizeDistances(DistancesList *distancesList, int min, int max);
Graph createGraph(DistancesList *normalizedDistances);

#endif