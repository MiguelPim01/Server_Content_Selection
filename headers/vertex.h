#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct Vertex Vertex;

// A struct Vertex que representa o vértice usado no algoritmo de Dijkstra é utilizada apenas no algoritmo
// sendo acessado constamente na execução do algoritmo de Dijkstra e pelo heap no vetor que tratamos como hash.

// Para obtermos uma melhor perfomace no tempo do trabalho, já que o algoritmo de Dijkstra é a parte que mais leva tempo
// Decidimos deixar a estrutura vísivel no vertex.h

struct Vertex{
    int numVertex;
    double distancia;
};

int vertex_get_numVertex(Vertex *vertex);

double vertex_get_distancia(Vertex *v);

#endif