#include "../headers/exportData.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 1 - Exporta um arquivo CSV com a quantidade de arestas + todas as arestas do grafo
void exportGraph(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");

  fprintf(file, "%d\n", graph->qtdEdges);

  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    for (int j = 0; j < currentVertex->deg; j++)
      fprintf(file, "%d, %d\n", currentVertex->id, currentVertex->edges[j]->id);
  }

  fclose(file);
}

// 2 - Exporta um arquivo CSV com todas as distâncias (normalizadas ou não) entre cada vértice
void exportDistances(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");

  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    for (int j = 0; j < currentVertex->qtdDistances; j++) {
      Distance *currentDistance = currentVertex->distances[j];
      fprintf(file, "%d, %d: %.6lf\n", currentVertex->id, currentDistance->v->id, currentDistance->value);
    }
  }

  fclose(file);
}

// 3 - Exporta um arquivo CSV com os graus de cada vértice
void exportDegrees(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");

  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    fprintf(file, "%d: %d\n", currentVertex->id, currentVertex->deg);
  }

  fclose(file);
}

// 4 - Exporta todos os componentes do grafo
void exportComponents(char *fileName, Graph *graph) {
  FILE *file = fopen(fileName, "wt");
  Vertex **vertices = malloc(graph->qtdVertices * sizeof(Vertex*));

  memcpy(vertices, graph->vertices, graph->qtdVertices * sizeof(Vertex*));

  // Algoritmo Insertion Sort
  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    int key = currentVertex->idComponent;
    int j = i - 1;

    while (j >= 0 && vertices[j]->idComponent > key) {
      vertices[j + 1] = vertices[j];
      j--;
    }

    vertices[j + 1] = currentVertex;
  }

  for (int i = 0; i < graph->qtdVertices; i++) {
    fprintf(file, "%d: %d\n", vertices[i]->id, vertices[i]->idComponent);
  }

  fclose(file);
}