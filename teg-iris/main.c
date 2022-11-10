// Por: Pedro Fernandes e André Fidelis
// Teoria dos Grafos - UDESC CCT 2022/02
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headers/handleGraph.h"
#include "headers/exportData.h"
#include "headers/confusionMatrix.h"

#define lim 0.3

#define datasetFile "iris-dataset.csv"
#define euclidianFile "./files/euclidian-distances.csv"
#define normalizedFile "./files/normalized-distances.csv"
#define graphFile "./files/graph.csv"
#define degreesFile "./files/degrees.csv"
#define componentsFile "./files/components.csv"

int main() {
  double max, min;
  Graph *graph = createGraph(datasetFile);

  setEuclidianDistances(graph, &min, &max);
  printf("Min: %.4lf, Max: %.4lf\n", min, max);
  exportDistances(euclidianFile, graph);

  normalizeDistances(graph, min, max);
  exportDistances(normalizedFile, graph);

  setEdges(graph, lim);
  
  exportGraph(graphFile, graph);
  exportDegrees(degreesFile, graph);

  markAllComponents(graph);
  
  exportComponents(componentsFile, graph);
}