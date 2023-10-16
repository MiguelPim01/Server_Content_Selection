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

Graph *graph_construct(int v, int e);

Graph *graph_read_file(char *file_name);

void graph_add_edge(Graph *g, int v1, int v2, double weight);

void graph_show(Graph *g);

void graph_destroy(Graph *g);

#endif