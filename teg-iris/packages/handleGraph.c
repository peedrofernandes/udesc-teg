#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../headers/handleGraph.h"

#define bufferLength 255

// 1 - Cria um grafo vazio e lê o arquivo original, definindo todos os vértices
Graph *createGraph(char *fileName) {
  Graph *graph = malloc(sizeof(Graph));
  graph->qtdEdges = 0;
  graph->qtdVertices = 0;

  FILE *data = fopen(fileName, "rt");

  if (data == NULL) {
    printf("There was an error trying to open the file '%s'!\n", fileName);
    return 0;
  }

  char *string = malloc(bufferLength * sizeof(char));

  Stack *vertexStack = createStack();

  string = fgets(string, bufferLength, data); // Descartar a primeira linha
  while (!feof(data)) {
    string = fgets(string, bufferLength, data);
    graph->qtdVertices++;

    Vertex *newVertex = malloc(sizeof(Vertex));
    newVertex->id = graph->qtdVertices;
    newVertex->idComponent = -1;
    newVertex->a1 = atof(strtok(string, ","));
    newVertex->a2 = atof(strtok(NULL, ","));
    newVertex->a3 = atof(strtok(NULL, ","));
    newVertex->a4 = atof(strtok(NULL, ","));
    push(vertexStack, newVertex);
  }

  Vertex **vertices = malloc(graph->qtdVertices * sizeof(Vertex*));
  for (int i = graph->qtdVertices - 1; i >= 0; i--) {
    Vertex *vertex = pop(vertexStack);
    vertices[i] = vertex;
  }

  graph->vertices = vertices;
  destroyStack(vertexStack);
  fclose(data);
  return graph;
}

// 2 - A partir dos vértices, obtém todas as distâncias euclidianas entre cada par de vértices
void *setEuclidianDistances(Graph *graph, double *min, double *max) {
  for (int i = 0; i < graph->qtdVertices; i++) {
    Stack *distancesStack = createStack();
    Vertex *currentVertex = graph->vertices[i];
    currentVertex->qtdDistances = 0;

    for (int j = 0; j < graph->qtdVertices; j++) {
      if (i == j)
        continue;
      
      Distance *distance = malloc(sizeof(Distance));

      Vertex *v = graph->vertices[j];
      distance->v = v;

      double value = sqrt(pow(currentVertex->a1 - v->a1, 2) + pow(currentVertex->a2 - v->a2, 2) + pow(currentVertex->a3 - v->a3, 2) + pow(currentVertex->a4 - v->a4, 2));

      distance->value = value;

      if (!min || value < (*min))
        *min = value;
      if (!max || value > (*max))
        *max = value;

      push(distancesStack, distance);
      currentVertex->qtdDistances++;
    }

    Distance **distances = malloc(currentVertex->qtdDistances * sizeof(Distance*));
    for (int k = currentVertex->qtdDistances - 1; k >= 0; k--) {
      Distance *distance = pop(distancesStack);
      distances[k] = distance;
    }

    currentVertex->distances = distances;
    destroyStack(distancesStack);
  }
}

// 3 - Normaliza todas as distâncias
void normalizeDistances(Graph *graph, double min, double max) {
  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *currentVertex = graph->vertices[i];
    for (int j = 0; j < currentVertex->qtdDistances; j++) {
      Distance *currentDistance = currentVertex->distances[j];
      currentDistance->value = (currentDistance->value - min) / (max - min);
    }
  }
}

// 4 - Determina as arestas do grafo a partir das distâncias normalizadas e um limiar
void setEdges(Graph *graph, double lim) {
  graph->qtdEdges = 0;
  for (int i = 0; i < graph->qtdVertices; i++) {
    Stack *edgesStack = createStack();
    Vertex *currentVertex = graph->vertices[i];
    currentVertex->deg = 0;

    for (int j = 0; j < currentVertex->qtdDistances; j++) {
      Distance *currentDistance = currentVertex->distances[j];
      if (currentDistance->value > lim)
        continue;

      graph->qtdEdges++;
      currentVertex->deg++;
      Vertex *v = currentDistance->v;
      push(edgesStack, v);
    }

    Vertex **edges = malloc(currentVertex->deg * sizeof(Vertex*));
    for (int k = 1; k <= currentVertex->deg; k++) {
      Vertex *edge = pop(edgesStack);
      edges[currentVertex->deg - k] = edge;
    }
    currentVertex->edges = edges;
    destroyStack(edgesStack);
  }
}