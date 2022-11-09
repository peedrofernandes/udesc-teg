// Por: Pedro Fernandes e André Fidelis
// Teoria dos Grafos - UDESC CCT 2022/02
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "handleGraph.h"

#define bufferLength 255
#define qtdVertices 150
#define qtdDistances qtdVertices * qtdVertices - qtdVertices
#define lim 0.3

#define datasetFile "iris-dataset.csv"
#define euclidianFile "./files/euclidian-distances.csv"
#define normalizedFile "./files/normalized-distances.csv"
#define graphFile "./files/graph.csv"
#define degreesFile "./files/degrees.csv"

int main() {
  double max, min;

  Graph *graph = createGraph(datasetFile);
  DistancesList *distances = getEuclidianDistances(graph, &min, &max);

  printf("Min: %.4lf, Max: %.4lf\n", min, max);

  exportDistances(euclidianFile, distances);

  normalizeDistances(distances, min, max);

  exportDistances(normalizedFile, distances);

  setEdges(graph, distances, lim);

  exportGraph(graphFile, graph);
  exportDegrees(degreesFile, graph);
}
