#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "handleGraph.h"

#define bufferLength 255

Vertex *getVertices(char *fileName) {
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


Distance *getEuclidianDistances(Vertex *vertices, int qtdVertices, double *max, double *min) {
  size_t qtdDistances = qtdVertices * qtdVertices - qtdVertices;

  Distance *distances = malloc(qtdDistances * sizeof(Distance));

  int currentDistance = 0;
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

      if (!max || ed > *(max)) {
        *max = ed;
      } else if (!min || ed < *(min)) {
        *min = ed;
      }

      Distance d;
      d.v1 = i + 1;
      d.v2 = j + 1;
      d.value = ed;
      distances[currentDistance] = d;
      currentDistance++;
    }
  }

  printf("max: %.6lf, min: %.6lf\n", *max, *min);

  return distances;
}


void printDistances(Distance *distances, int qtdVertices) {
  int qtdDistances = qtdVertices * qtdVertices - qtdVertices;
    for (int i = 0; i < qtdDistances; i++) {
      printf("%d %d %.2lf\n", distances[i].v1, distances[i].v2, distances[i].value);
    }
}


void exportDistances(char *fileName, Distance *distances, int qtdVertices) {
  int qtdDistances = qtdVertices * qtdVertices - qtdVertices;

  FILE *exportFile = fopen(fileName, "wt");
  if (!exportFile) {
    printf("There was an error trying to open %s file!\n", fileName);
    return;
  }

  for (int i = 0; i < qtdDistances; i++) {
    fprintf(exportFile, "%d,%d,%.6lf\n", distances[i].v1, distances[i].v2, distances[i].value);
  }

  fclose(exportFile);
}


Distance *getNormalizedDistances(Distance *distances, int qtdVertices, double max, double min) {

  double normalize(double max, double min, double value) {
    return (value - min) / (max - min);
  };

  int qtdDistances = qtdVertices * qtdVertices - qtdVertices;

  Distance *normalizedDistances = malloc(qtdDistances * sizeof(Distance));

  for (int i = 0; i < qtdDistances; i++) {
    Distance d = {
      v1 : distances[i].v1,
      v2 : distances[i].v2,
      value : normalize(max, min, distances[i].value)
    };

    normalizedDistances[i] = d;
  }

  return normalizedDistances;
}


Graph *createGraph(int qtdVertices, Distance *normalizedDistances, int qtdDistances, double lim) {
  Graph *graph = malloc(sizeof(Graph));
  Edge *currentEdge;
  graph->qtdEdges = 0;

  for (int i = 0; i < qtdDistances; i++) {
    if (normalizedDistances[i].value > lim)
      continue;
    graph->qtdEdges++;

    if (graph->qtdEdges == 1) {
      graph->firstEdge = malloc(sizeof(Edge));
      currentEdge = graph->firstEdge;
    } else {
      currentEdge->next = malloc(sizeof(Edge));
      currentEdge = currentEdge->next;
    }

    currentEdge->v1 = normalizedDistances[i].v1;
    currentEdge->v2 = normalizedDistances[i].v2;
  }

  return graph;
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


void exportGraphviz(char *fileName, EdgeList *list) {
  FILE *exportFile = fopen(fileName, "wt");

  if (!exportFile) {
    printf("There was an error trying to open %s file!\n", fileName);
    return;
  }

  Edge *aux = list->first;
  char string[bufferLength];

  fprintf(exportFile, "graph G {\n");
  while (aux != NULL) {
    fprintf(exportFile, "  %d -- %d\n", aux->v1, aux->v2);
    aux = aux->next;
  }
  fprintf(exportFile, "}\n");
}