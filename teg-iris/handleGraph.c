#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "handleGraph.h"

#define bufferLength 255

Vertex *getVertices(char *fileName, int qtdVertices) {
  Vertex *vertices = malloc(qtdVertices * sizeof(Vertex));
  FILE *data = fopen(fileName, "rt");

  if (data == NULL) {
    printf("There was an error trying to open the file!\n");
    return 0;
  }

  char string[bufferLength];

  for (int i = 0; i < qtdVertices; i++) {
    fgets(string, bufferLength, data);
    double a1 = atof(strtok(string, ","));
    double a2 = atof(strtok(NULL, ","));
    double a3 = atof(strtok(NULL, ","));
    double a4 = atof(strtok(NULL, ","));
    Vertex v = {i+1, a1, a2, a3, a4};
    vertices[i] = v;
  }

  fclose(data);
  return vertices;
}


void printVertices(Vertex *vertices, int qtdVertices) {
  for (int i = 0; i < qtdVertices; i++) {
    printf("%d %.1lf %.1lf %.1lf %.1lf\n", vertices[i].id, vertices[i].a1, vertices[i].a2, vertices[i].a3, vertices[i].a4);
  }
} 


Adjacency *getEuclidianAdjacencies(Vertex *vertices, int qtdVertices, double *max, double *min) {
  size_t qtdAdjacencies = qtdVertices * qtdVertices - qtdVertices;

  Adjacency *adjacencies = malloc(qtdAdjacencies * sizeof(Adjacency));

  if (!max)
    max = 0;
  if (!min)
    min = 0;

  int currentAdj = 0;
  for (int i = 0; i < qtdVertices; i++) {
    for (int j = 0; j < qtdVertices; j++) {
      if (i == j)
        continue;
      double v1a1 = vertices[i].a1;
      double v1a2 = vertices[i].a2;
      double v1a3 = vertices[i].a3;
      double v1a4 = vertices[i].a4;
      double v2a1 = vertices[j].a1;
      double v2a2 = vertices[j].a2;
      double v2a3 = vertices[j].a3;
      double v2a4 = vertices[j].a4;

      double ed = sqrt(pow(v1a1 - v2a1, 2) + pow(v1a2 - v2a2, 2) + pow(v1a3 - v2a3, 2) + pow(v1a4 - v2a4, 2));

      if (ed > *(max))
        *max = ed;
      else if (ed < *(min))
        *min = ed;

      Adjacency a;
      a.v1 = i + 1;
      a.v2 = j + 1;
      a.distance = ed;
      adjacencies[currentAdj] = a;
      currentAdj++;
    }
  }

  return adjacencies;
}


void printAdjacencies(Adjacency *adjacencies, int qtdVertices) {
  int qtdAdjacencies = qtdVertices * qtdVertices - qtdVertices;
    for (int i = 0; i < qtdAdjacencies; i++) {
      printf("%d %d %.2lf\n", adjacencies[i].v1, adjacencies[i].v2, adjacencies[i].distance);
    }
}


void exportAdjacencies(char *fileName, Adjacency *adjacencies, int qtdVertices) {
  int qtdAdjacencies = qtdVertices * qtdVertices - qtdVertices;

  FILE *exportFile = fopen(fileName, "wt");
  if (!exportFile) {
    printf("There was an error trying to open %s file!\n", fileName);
    return;
  }

  for (int i = 0; i < qtdAdjacencies; i++) {
    fprintf(exportFile, "%d,%d,%.6lf\n", adjacencies[i].v1, adjacencies[i].v2, adjacencies[i].distance);
  }

  fclose(exportFile);
}


Adjacency *getNormalizedAdjacencies(Adjacency *adjacencies, int qtdVertices, double max, double min) {

  double normalize(double max, double min, double value) {
    return (value - min) / (max - min);
  };

  int qtdAdjacencies = qtdVertices * qtdVertices - qtdVertices;

  Adjacency *normalizedAdjacencies = malloc(qtdAdjacencies * sizeof(Adjacency));

  for (int i = 0; i < qtdAdjacencies; i++) {
    Adjacency a = {
      v1 : adjacencies[i].v1,
      v2 : adjacencies[i].v2,
      distance : normalize(max, min, adjacencies[i].distance)
    };

    normalizedAdjacencies[i] = a;
  }

  return normalizedAdjacencies;
}


EdgeList *getGraphEdges(Adjacency *normalizedAdjacencies, int qtdVertices, double lim) {
  EdgeList *list = malloc(sizeof(EdgeList));
  Edge *currentEdge;
  list->qtdEdges = 0;

  int qtdAdjacencies = qtdVertices * qtdVertices - qtdVertices;

  for (int i = 0; i < qtdAdjacencies; i++) {
    if (normalizedAdjacencies[i].distance > lim)
      continue;
    list->qtdEdges++;

    if (list->qtdEdges == 1) {
      list->first = malloc(sizeof(Edge));
      currentEdge = list->first;
    } else {
      currentEdge->next = malloc(sizeof(Edge));
      currentEdge = currentEdge->next;
    }

    currentEdge->v1 = normalizedAdjacencies[i].v1;
    currentEdge->v2 = normalizedAdjacencies[i].v2;
  }

  return list;
}


void printGraphEdges(EdgeList *list) {
  Edge *aux = list->first;

  printf("%d\n", list->qtdEdges);
  while (aux != NULL) {
    printf("%d, %d\n", aux->v1, aux->v2);
    aux = aux->next;
  }
}


void exportGraphEdges(char *fileName, EdgeList *list) {
  FILE *exportFile = fopen(fileName, "wt");

  if (!exportFile) {
    printf("There was an error trying to open %s file!\n", fileName);
    return;
  }

  Edge *aux = list->first;
  char string[bufferLength];

  fprintf(exportFile, "%d\n", list->qtdEdges);
  while (aux != NULL) {
    fprintf(exportFile, "%d, %d\n", aux->v1, aux->v2);
    aux = aux->next;
  }
}