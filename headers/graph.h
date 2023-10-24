#ifndef _GRPH_H_
#define _GRPH_H_

#include <stdlib.h>
#include <stdio.h>

#define INITIAL_SIZE_ADJACENCY 10
#define GROWTH_RATE_ADJACENCY 2

#define CLIENT 'c'
#define SERVER 's'
#define MONITOR 'm'

typedef struct Graph Graph;
typedef struct Adjacencies Adjacencies;
typedef struct List List;
typedef struct AdjacenciesIterator AdjacenciesIterator;

Graph *graph_construct(int v, int e);

Graph *graph_read_file(char *file_name);

void graph_add_edge(Graph *g, int v1, int v2, double weight);

void graph_show(Graph *g);

void graph_destroy(Graph *g);

int get_num_vertexes(Graph *g);

List *graph_get_list(Graph *g, int idx);

double graph_get_edge_weight(Adjacencies *adj);

int graph_get_vertex(Adjacencies *adj);

AdjacenciesIterator *Adjacencies_front_iterator(List *list);

Adjacencies *Adjacencies_iterator_next(AdjacenciesIterator *it);

int Adjacencies_iterator_is_over(AdjacenciesIterator *it);

void Adjacencies_iterator_destroy(AdjacenciesIterator *it);

#endif