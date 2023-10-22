#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "graph.h"

typedef struct Vertex Vertex;

Vertex *vertex_construct(int numVertex, Vertex *pai, double distancia);

void vertex_destroy(Vertex *vertex);

void vertex_atualiza_distancia(Vertex *vertex, double distancia);

#endif