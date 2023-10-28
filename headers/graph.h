#ifndef _GRPH_H_
#define _GRPH_H_

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

int graph_get_num_vertices(Graph *g);

List *graph_get_list(Graph *g, int idx);

char graph_get_vertex_type(Graph *g, int numVertex);

int graph_get_server_size(Graph *g);

int graph_get_client_size(Graph *g);

int graph_get_monitor_size(Graph *g);

int *graph_get_server(Graph *g);

int *graph_get_client(Graph *g);

int *graph_get_monitor(Graph *g);

int *graph_get_uteis(Graph *g);

int graph_get_uteis_size(Graph *g);

int graph_get_element_util(Graph *g, int idx);

double adjacencies_get_edge_weight(Adjacencies *adj);

int adjacencies_get_vertex(Adjacencies *adj);

AdjacenciesIterator *adjacencies_front_iterator(List *list);

Adjacencies *adjacencies_iterator_next(AdjacenciesIterator *it);

int adjacencies_iterator_is_over(AdjacenciesIterator *it);

void adjacencies_iterator_destroy(AdjacenciesIterator *it);

#endif