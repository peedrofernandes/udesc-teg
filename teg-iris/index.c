#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "handleGraph.h"

#define bufferLength 255
#define qtdVertices 150
#define qtdDistances qtdVertices * qtdVertices - qtdVertices
#define lim 0.03

#define datasetFile "./files/iris-dataset.csv"
#define euclidianFile "./files/euclidian-distances.csv"
#define normalizedFile "./files/normalized-distances.csv"
#define edgesFile "./files/graph-edges.csv"

int main() {
  double max, min;

  Vertex *vertices = getVertices(datasetFile, qtdVertices);
  Distance *distances = getEuclidianDistances(vertices, qtdVertices, &max, &min);
  Distance *normalizedDistances = getNormalizedDistances(distances, qtdVertices, max, min);

  exportDistances(euclidianFile, distances, qtdVertices);
  exportDistances(normalizedFile, normalizedDistances, qtdVertices);

  EdgeList *list = getGraphEdges(normalizedDistances, qtdVertices, lim);

  exportGraphEdges(edgesFile, list);
}