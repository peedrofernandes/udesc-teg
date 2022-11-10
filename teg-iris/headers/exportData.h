#include "handleGraph.h"

#ifndef EXPORT_DATA_H
#define EXPORT_DATA_H

void exportGraph(char *fileName, Graph *graph);
void exportDistances(char *fileName, Graph *graph);
void exportDegrees(char *fileName, Graph *graph);
void exportComponents(char *fileName, Graph *graph);

#endif