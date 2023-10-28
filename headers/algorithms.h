#ifndef _DIKSTRA_ALG_H_
#define _DIKSTRA_ALG_H_

#include <limits.h>

#include "graph.h"
#include "heap.h"
#include "vertex.h"

#define INFINITO (INT_MAX/2)

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex *vertices, Heap *heap);

double **rtt_algorithm(Graph *graph);

double calcula_rtt(double **matriz, int idx1, int idx2);

double calcula_rtt_asterisco(double **matriz, int idxServer, int idxCliente, Graph *g);

double calcula_inflacao_rtt(double **matriz, int idxServer, int idxCliente, Graph *g);

void matriz_destroy(double **matriz, int size);

#endif