#include <stdio.h>
#include <stdlib.h>

#include "../headers/graph.h"

struct Adjacencies{
    int vertex;
    double weight;
    struct Adjacencies *next;
};

struct List{
    Adjacencies *head;
};

struct Graph{
    char *vertex_types;
    int num_vertices;
    int num_edges;
    List *adjacencies;
    int qtdServer;
    int qtdClient;
    int qtdMonitor;
    int *server;
    int *client;
    int *monitor;
};

struct AdjacenciesIterator{
    Adjacencies *current;
};

Graph *graph_construct(int v, int e){
    Graph *g = malloc(sizeof(Graph));

    g->num_vertices = v;
    g->num_edges = e;
    g->vertex_types = malloc(sizeof(char) * v);
    g->adjacencies = malloc(sizeof(List) * v);

    for(int i = 0; i < v; i++){
        g->adjacencies[i].head = NULL;
        g->vertex_types[i] = 0;
    }

    return g;
}

Graph *graph_read_file(char *file_name){
    FILE *arq = fopen(file_name, "r");

    if(!arq) exit(printf("ERROR in open file (%s)\n", file_name));

    int v, e, v1, v2, s, c, m;
    double weight;

    fscanf(arq, "%d %d", &v, &e);
    Graph *g = graph_construct(v, e);

    fscanf(arq, "%d %d %d", &s, &c, &m);

    g->qtdServer = 0;
    g->qtdClient = 0;
    g->qtdMonitor = 0;

    g->server  = malloc(sizeof(int) * s);
    g->client  = malloc(sizeof(int) * c);
    g->monitor = malloc(sizeof(int) * m);

    int tam = s + m + c;
    for(int i = 0; i < tam; i++){
        fscanf(arq, "%d", &v1);
        if( s ){
            g->vertex_types[v1] = SERVER;
            g->server[g->qtdServer++] = v1;
            s--;

        } else if( c ){
            g->vertex_types[v1] = CLIENT;
            g->client[g->qtdClient++] = v1;
            c--;

        } else {
            g->vertex_types[v1] = MONITOR;
            g->monitor[g->qtdMonitor++] = v1;
        }
    }

    for(int i = 0; i < e; i++){
        fscanf(arq, "%d %d %lf", &v1, &v2, &weight);
        graph_add_edge(g, v1, v2, weight);
    }

    fclose(arq);
    return g;
}

void graph_add_edge(Graph *g, int v1, int v2, double weight){

    Adjacencies *adj = malloc(sizeof(Adjacencies)), *aux;
    adj->vertex = v2;
    adj->weight = weight;

    aux = g->adjacencies[v1].head;
    g->adjacencies[v1].head = adj;
    adj->next = aux;
    
}

void graph_show(Graph *g){
    FILE *arq = fopen("graph.dot", "w");
    fprintf(arq, "Digraph G{\nnode [style = filled];\n");

        for(int i = 0; i < g->num_vertices; i++){

        fprintf(arq, "%d [fillcolor =", i);
        switch( g->vertex_types[i] ){
            case CLIENT: fprintf(arq, "green"); break;
            case SERVER:  fprintf(arq, "gray"); break;
            case MONITOR: fprintf(arq, "blue"); break;
            default:     fprintf(arq, "white"); break;
        }
        fprintf(arq, "];\n");

            Adjacencies *adj = g->adjacencies[i].head;
            while(adj){
                fprintf(arq, "%d -> %d [label = %c%.2lf%c];\n", i, adj->vertex, '"', adj->weight, '"');
                adj = adj->next;
            }
        }

    fprintf(arq, "}\n");

    system("dot -Tpng graph.dot -O &");

    fclose(arq);
}

void graph_destroy(Graph *g){

    int tam = g->num_vertices;
    for(int i = 0; i < tam; i++){
        Adjacencies *adj = g->adjacencies[i].head, *aux;
        while(adj){
            aux = adj;
            adj = adj->next;
            free(aux);
        }

    }
    
    free(g->adjacencies);
    free(g->server);
    free(g->client);
    free(g->monitor);
    free(g->vertex_types);
    free(g);
}

int graph_get_num_vertices(Graph *g){
    return g->num_vertices;
}

List *graph_get_list(Graph *g, int idx){
    return &g->adjacencies[idx];
}

char graph_get_vertex_type(Graph *g, int numVertex)
{
    return g->vertex_types[numVertex];
}

int graph_get_server_size(Graph *g){
    return g->qtdServer;
}

int graph_get_client_size(Graph *g){
    return g->qtdClient;
}

int graph_get_monitor_size(Graph *g){
    return g->qtdMonitor;
}

int *graph_get_server(Graph *g){
    return g->server;
}

int *graph_get_client(Graph *g){
    return g->client;
}

int *graph_get_monitor(Graph *g){
    return g->monitor;
}

double adjacencies_get_edge_weight(Adjacencies *adj){
    return adj->weight;
}

int adjacencies_get_vertex(Adjacencies *adj){
    return adj->vertex;
}

int matrixSMC_get_index(Graph *g, int value){

    switch (graph_get_vertex_type(g, value)){
    case SERVER:
        for(int i = 0; i < g->qtdServer; i++)
            if( value == g->server[i] )
                return i;
        break;

    case CLIENT: 
        for(int i = 0; i < g->qtdClient; i++){
            if( value == g->client[i] )    
                return i + g->qtdServer;
        }
        break;

    case MONITOR: 
        for(int i = 0; i < g->qtdMonitor; i++){
            if( value == g->monitor[i] )    
                return i + g->qtdServer + g->qtdClient;
        }
        break;
    }
    return -1;
}


/* ====================== ITERADOR PARA UMA LISTA DE ADJACENCIA ====================== */

AdjacenciesIterator *adjacencies_front_iterator(List *list){

    AdjacenciesIterator *it = (AdjacenciesIterator*) malloc(sizeof(AdjacenciesIterator));

    it->current = list->head;

    return it;
}


Adjacencies *adjacencies_iterator_next(AdjacenciesIterator *it){

    Adjacencies *data = it->current;

    it->current = it->current->next;

    return data;
}

int adjacencies_iterator_is_over(AdjacenciesIterator *it)
{
    return (it->current == NULL) ? 1 : 0;
}

void adjacencies_iterator_destroy(AdjacenciesIterator *it)
{
    free(it);
}