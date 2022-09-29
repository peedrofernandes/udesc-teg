#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "handleGraph.h"

#define bufferLength 255
#define qtdVertices 150
#define qtdAdjacencies qtdVertices * qtdVertices - qtdVertices
#define lim 0.1

#define datasetFile "./files/iris-dataset.csv"
#define euclidianFile "./files/euclidian-adj.csv"
#define normalizedFile "./files/normalized-adj.csv"
#define edgesFile "./files/graph-edges.csv"

int main() {
  double max, min;

  Vertex *vertices = getVertices(datasetFile, qtdVertices);
  Adjacency *adjacencies = getEuclidianAdjacencies(vertices, qtdVertices, &max, &min);
  Adjacency *normalizedAdjacencies = getNormalizedAdjacencies(adjacencies, qtdVertices, max, min);

  exportAdjacencies(euclidianFile, adjacencies, qtdVertices);
  exportAdjacencies(normalizedFile, normalizedAdjacencies, qtdVertices);

  EdgeList *list = getGraphEdges(normalizedAdjacencies, qtdVertices, lim);

  exportGraphEdges(edgesFile, list);
}