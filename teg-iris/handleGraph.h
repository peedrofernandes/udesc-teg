#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

// Vértice do grafo, com todos os seus parâmetros
typedef struct vertex {
  int id;
  double a1;
  double a2;
  double a3;
  double a4;
} Vertex;

// Distância entre dois vértices, dados seus parâmetros
typedef struct distance {
  int v1;
  int v2;
  double value;
} Distance;

// Aresta entre dois vértices
typedef struct edge {
  int v1;
  int v2;
  struct edge *next;
} Edge;

// Lista de arestas de um grafo
typedef struct edgeList {
  Edge *first;
  int qtdEdges;
} EdgeList;

// Funções relacionadas à Vértices
Vertex *getVertices(char *fileName, int qtdVertices);
void printVertices(Vertex *vertices, int qtdVertices);

// Funções relacionadas às distâncias euclidianas e normalizadas
Distance *getEuclidianDistances(Vertex *vertices, int qtdVertices, double *max, double *min);
Distance *getNormalizedDistances(Distance *distances, int qtdVertices, double max, double min);
void printDistances(Distance *distances, int qtdVertices);
void exportDistances(char *fileName, Distance *distances, int qtdVertices);

// Funções relacionadas à obtenção dos grafos
EdgeList *getGraphEdges(Distance *normalizedDistances, int qtdVertices, double lim);
void printGraphEdges(EdgeList *list);
void exportGraphEdges(char *fileName, EdgeList *list);
void exportGraphviz(char *fileName, EdgeList *list);

#endif