#include <stdlib.h>
#include <stdio.h>

#include "../headers/vertex.h"

int vertex_get_numVertex(Vertex *vertex){
    return vertex->numVertex;
}

double vertex_get_distancia(Vertex *v){
    return v->distancia;
}