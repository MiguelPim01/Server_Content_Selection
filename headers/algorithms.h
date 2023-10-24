#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#include <limits.h>

#include "graph.h"
#include "vertex.h"

#define INFINITO (INT_MAX/2)

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex **vertices);

double **rtt_algorithm(Graph *graph);

#endif