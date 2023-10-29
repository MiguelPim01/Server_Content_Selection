#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct Vertex Vertex;

struct Vertex{
    int numVertex;
    double distancia;
};

int vertex_get_numVertex(Vertex *vertex);

double vertex_get_distancia(Vertex *v);

#endif