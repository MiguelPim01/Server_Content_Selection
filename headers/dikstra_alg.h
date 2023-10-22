#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#define INFINITO 9999999;

#include "heap.h"

Vertex **inicializa(Graph graph, int numVertexStart);

void dikstra(Graph graph, int numVertexStart);

#endif