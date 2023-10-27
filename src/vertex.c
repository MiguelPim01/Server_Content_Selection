#include <stdlib.h>
#include <stdio.h>

#include "../headers/vertex.h"

struct Vertex{
    int numVertex;
    struct Vertex *pai;
    double distancia;
};

Vertex *vertex_construct(int numVertex){

    Vertex *vertex = (Vertex*) malloc(sizeof(Vertex));

    vertex->numVertex = numVertex;
 
    return vertex;
}

int vertex_get_numVertex(Vertex *vertex){
    return vertex->numVertex;
}

double vertex_get_distancia(Vertex *v){
    return v->distancia;
}

void vertex_atualiza_distancia(Vertex *vertex, double distancia){
    vertex->distancia = distancia;
}

void vertex_atualiza_pai(Vertex *v, Vertex *pai){
    v->pai = pai;
}

void vertex_print(Vertex *v){

    printf("numVertice: %d\n", v->numVertex);
    printf("Distancia: %.2lf\n", v->distancia);
    if(v->pai != NULL)
        printf("Pai: %d\n", v->pai->numVertex);
    printf("\n");
}

void vertex_destroy(Vertex *vertex){
    free(vertex);
}