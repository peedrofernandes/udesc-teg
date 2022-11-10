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
    newVertex->a1 = atof(strtok(string, ","));
    newVertex->a2 = atof(strtok(NULL, ","));
    newVertex->a3 = atof(strtok(NULL, ","));
    newVertex->a4 = atof(strtok(NULL, ","));

    push(vertexStack, newVertex);
  }

  Vertex *vertices = malloc(graph->qtdVertices * sizeof(Vertex));
  for (int i = 0; i < graph->qtdVertices; i++) {
    Vertex *vertex = pop(vertexStack);
    vertices[i] = *vertex;
  }

  destroyStack(vertexStack);
  fclose(data);
  return graph;
}

// 2 - A partir dos vértices, obtém todas as distâncias euclidianas entre cada par de vértices
Distance *getEuclidianDistances(Graph *graph, double *min, double *max, int *qtdDistances) {
  Stack *distancesStack = createStack();
  for (int i = 0; i < graph->qtdVertices; i++) {
    for (int j = i + 1; j < graph->qtdVertices; j++) {
      Distance *distance = malloc(sizeof(Distance));

      Vertex *v1 = &graph->vertices[i];
      Vertex *v2 = &graph->vertices[j];
      distance->v1 = v1;
      distance->v2 = v2;

      double v = sqrt(pow(v1->a1 - v2->a1, 2) + pow(v1->a2 - v2->a2, 2) + pow(v1->a3 - v2->a3, 2) + pow(v1->a4 - v2->a4, 2));
      distance->value = v;

      if (!min || v < (*min))
        *min = v;
      if (!max || v > (*max))
        *max = v;

      push(distancesStack, distance);
    }
  }

  *qtdDistances = distancesStack->qtdNodes;

  Distance *distances = malloc(*qtdDistances * sizeof(Distance));
  for (int i = 0; i < *qtdDistances; i++) {
    Distance *distance = pop(distancesStack);
    distances[i] = *distance;
  }

  return distances;
}

// 3 - Normaliza todas as distâncias
void normalizeDistances(Distance *distances, double min, double max, int qtdDistances) {
  for (int i = 0; i < qtdDistances; i++)
    distances[i].value = (distances[i].value - min) / (max - min);
}

// 4 - Determina as arestas do grafo a partir das distâncias normalizadas e um limiar
void setEdges(Graph *graph, double lim, Distance *normalizedDistances, int qtdDistances) {
  for (int i = 0; i < graph->qtdVertices; i++) {
    for (int j = 0; j < qtdDistances; j++) {
      
    }
  }
}

  // while (currentDistance != NULL) {
  //   if (currentDistance->value <= lim) {
  //     graph->qtdEdges++;

  //     if (graph->qtdEdges == 1) {
  //       graph->firstEdge = malloc(sizeof(Edge));
  //       currentEdge = graph->firstEdge;
  //     } else {
  //       currentEdge->next = malloc(sizeof(Edge));
  //       currentEdge = currentEdge->next;
  //     }

  //     currentEdge->v1 = currentDistance->v1;
  //     currentEdge->v2 = currentDistance->v2;

  //     Vertex *v1 = getVertexById(graph, currentEdge->v1);
  //     Vertex *v2 = getVertexById(graph, currentEdge->v2);
  //     v1->deg++;
  //     v2->deg++;
  //   }
  //   currentDistance = currentDistance->next;
  // }
}