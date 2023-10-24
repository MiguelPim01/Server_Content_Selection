#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct Vertex Vertex;

Vertex *vertex_construct(int numVertex);

void vertex_destroy(Vertex *vertex);

void vertex_atualiza_distancia(Vertex *vertex, double distancia);

void vertex_atualiza_pai(Vertex *v, Vertex *pai);

int vertex_get_numVertex(Vertex *vertex);

double vertex_get_distancia(Vertex *v);

void vertex_print(Vertex *v);

#endif