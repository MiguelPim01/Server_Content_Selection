#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#include <stdio.h>

#define INFINITO INT_MAX_/2;

#include "heap.h"

Vertex **inicializa(Graph graph, int numVertexStart);

void dikstra(Graph graph, int numVertexStart);

void relaxa(Vertex *a, Vertex *b, double weight, Heap *heap);

#endif