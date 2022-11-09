#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../headers/handleGraph.h"

#define bufferLength 255

// Tarefas
// 1 - Criar um grafo vazio e Ler o arquivo original, obtendo todos os vértices
// 2 - A partir dos vértices, obter todas as distâncias euclidianas entre ele
// 2.1 - Exportar todas as distâncias euclidianas para um arquivo CSV
// 3 - Normalizar todas as distâncias
// 3.1 - Exportar todas as distâncias euclidianas normalizadas para um arquivo CSV
// 4 - Determinar as arestas do grafo a partir das distâncias normalizadas e um limiar
// 5 - Exportar um arquivo CSV com a quantidade de arestas e as arestas do grafo
// 6 - Exportar um arquivo CSV com os graus de cada vértice

Vertex *getVertexById(Graph *graph, int id) {
  Vertex *currentVertex = graph->firstVertex;

  while (currentVertex != NULL) {
    if (currentVertex->id == id)
      break;
    currentVertex = currentVertex->next;
  }

  return currentVertex;
}

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

  Vertex *currentVertex;
  // fscanf(data, "%*[^\n]"); // Descartar a primeira linha
  string = fgets(string, bufferLength, data); // Descartar a primeira linha
  while (!feof(data)) {
    string = fgets(string, bufferLength, data);

    graph->qtdVertices++;

    if (graph->qtdVertices == 1) {
      graph->firstVertex = malloc(sizeof(Vertex));
      currentVertex = graph->firstVertex;
    } else {
      currentVertex->next = malloc(sizeof(Vertex));
      currentVertex = currentVertex->next;
    }

    currentVertex->id = graph->qtdVertices;
    currentVertex->a1 = atof(strtok(string, ","));
    currentVertex->a2 = atof(strtok(NULL, ","));
    currentVertex->a3 = atof(strtok(NULL, ","));
    currentVertex->a4 = atof(strtok(NULL, ","));
  }

  fclose(data);
  return graph;
}

DistancesList *getEuclidianDistances(Graph *graph, double *min, double *max) {
  DistancesList *list = malloc(sizeof(DistancesList));
  list->qtdDistances = 0;
  Distance *currentDistance;

  Vertex *v1 = graph->firstVertex;
  Vertex *v2 = graph->firstVertex;

  while (v1 != NULL) {
    v2 = v1->next;
    while (v2 != NULL) {
      list->qtdDistances++;

      if (list->qtdDistances == 1) {
        list->firstDistance = malloc(sizeof(Distance));
        currentDistance = list->firstDistance;
      } else {
        currentDistance->next = malloc(sizeof(Distance));
        currentDistance = currentDistance->next;
      }

      double d = sqrt(pow(v1->a1 - v2->a1, 2) + pow(v1->a2 - v2->a2, 2) + pow(v1->a3 - v2->a3, 2) + pow(v1->a4 - v2->a4, 2));

      if (!min || d < (*min))
        *min = d;
      if (!max || d > (*max))
        *max = d;

      currentDistance->v1 = v1->id;
      currentDistance->v2 = v2->id;
      currentDistance->value = d;
      v2 = v2->next;
    }
    v1 = v1->next;
  }

  return list;
}

void normalizeDistances(DistancesList *list, double min, double max) {
  Distance *currentDistance = list->firstDistance;

  while (currentDistance != NULL) {
    currentDistance->value = (currentDistance->value - min) / (max - min);
    currentDistance = currentDistance->next;
  }
}

void setEdges(Graph *graph, DistancesList *normalizedDistances, double lim) {
  Edge *currentEdge;
  graph->qtdEdges = 0;

  Distance *currentDistance = normalizedDistances->firstDistance;

  while (currentDistance != NULL) {
    if (currentDistance->value <= lim) {
      graph->qtdEdges++;

      if (graph->qtdEdges == 1) {
        graph->firstEdge = malloc(sizeof(Edge));
        currentEdge = graph->firstEdge;
      } else {
        currentEdge->next = malloc(sizeof(Edge));
        currentEdge = currentEdge->next;
      }

      currentEdge->v1 = currentDistance->v1;
      currentEdge->v2 = currentDistance->v2;

      Vertex *v1 = getVertexById(graph, currentEdge->v1);
      Vertex *v2 = getVertexById(graph, currentEdge->v2);
      v1->deg++;
      v2->deg++;
    }
    currentDistance = currentDistance->next;
  }


}