#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "graph.h"

typedef struct Vertex Vertex;

Vertex *vertex_construct(int numVertex, Vertex *pai, double distancia);

#endif