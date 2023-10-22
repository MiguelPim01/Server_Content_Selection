#include "../../headers/vertex.h"

struct Vertex{
    int numVertex;
    struct Vertex *pai;
    double distancia;
};

Vertex *vertex_construct(int numVertex, Vertex *pai, double distancia){

    Vertex *vertex = (Vertex*) malloc(sizeof(Vertex));

    vertex->numVertex = numVertex;
    vertex->pai = pai;
    vertex->distancia = distancia;

    return vertex;
}

void vertex_atualiza_distancia(Vertex *vertex, double distancia){
    vertex->distancia = distancia;
}

void vertex_destroy(Vertex *vertex){
    free(vertex);
}

int vertex_get_numVertex(Vertex *vertex){
    return vertex->numVertex;
}