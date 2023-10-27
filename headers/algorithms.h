#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#include <limits.h>

#include "graph.h"
#include "vertex.h"
#include "heap.h"

#define INFINITO (INT_MAX/2)

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex **vertices, Heap *heap);

double **rtt_algorithm(Graph *graph);

void matriz_destroy(double **matriz, int size);

#endif