#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#include <limits.h>

#define INFINITO (INT_MAX/2)

#include "heap.h"

void inicializa(Graph *graph, int numVertexStart, Vertex **vertexes);

void dikstra(Graph *graph, int numVertexStart, Vertex **vertexes);

void relaxa(Vertex *a, Vertex *b, double weight, Heap *heap);

#endif