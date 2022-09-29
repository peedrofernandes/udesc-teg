#ifndef HANDLE_GRAPH_H
#define HANDLE_GRAPH_H

typedef struct vertex {
  int id;
  double a1;
  double a2;
  double a3;
  double a4;
} Vertex;

typedef struct adjacency {
  int v1;
  int v2;
  double distance;
} Adjacency;

typedef struct edge {
  int v1;
  int v2;
  struct edge *next;
} Edge;

typedef struct edgeList {
  Edge *first;
  int qtdEdges;
} EdgeList;

Vertex *
getVertices(char *fileName, int qtdVertices);

void printVertices(Vertex *vertices, int qtdVertices);

Adjacency *getEuclidianAdjacencies(Vertex *vertices, int qtdVertices, double *max, double *min);

Adjacency *getNormalizedAdjacencies(Adjacency *adjacencies, int qtdVertices, double max, double min);

void printAdjacencies(Adjacency *adjacencies, int qtdVertices);

void exportAdjacencies(char *fileName, Adjacency *adjacencies, int qtdVertices);

EdgeList *getGraphEdges(Adjacency *normalizedAdjacencies, int qtdVertices, double lim);

void printGraphEdges(EdgeList *list);

void exportGraphEdges(char *fileName, EdgeList *list);

#endif