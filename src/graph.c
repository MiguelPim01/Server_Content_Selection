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

    // Info sobre os vertices uteis (Servidor, Cliente, Monitor):
    int qtdServer;
    int qtdClient;
    int qtdMonitor;
    int *uteis;
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

    g->qtdServer = s;
    g->qtdClient = c;
    g->qtdMonitor = m;
    int qtd = 0;

    g->uteis  = malloc(sizeof(int) * (s + c + m));

    int tam = s + m + c;
    for(int i = 0; i < tam; i++){
        fscanf(arq, "%d", &v1);
        if( s ){
            g->vertex_types[v1] = SERVER;

            g->uteis[qtd++] = v1;
            s--;

        } else if( c ){
            g->vertex_types[v1] = CLIENT;
            
            g->uteis[qtd++] = v1;
            c--;

        } else {
            g->vertex_types[v1] = MONITOR;
            g->uteis[qtd++] = v1;
            
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

    Adjacencies *adj = malloc(sizeof(Adjacencies));
    adj->vertex = v2;
    adj->weight = weight;
    adj->next = NULL;

    // Adição nao ordenada:

    // adj->next = g->adjacencies[v1].head;
    // g->adjacencies[v1].head = adj;

    // Adicionando ordenado na lista de adjacencias:

    Adjacencies *atual = g->adjacencies[v1].head, *prev = NULL;

    // Insere na cabeça da lista
    if (atual != NULL)
    {
        if (atual->vertex >= v2)
        {
            g->adjacencies[v1].head = adj;
            adj->next = atual;
            return;
        }
    }
    else
    {
        g->adjacencies[v1].head = adj;
        return;
    }

    // Insere no meio da lista
    while (atual != NULL)
    {
        if (atual->vertex < v2)
        {
            prev = atual;
            atual = atual->next;
        }
        else
        {
            prev->next = adj;
            adj->next = atual;
            return;
        }
    }

    // Insere no fim da lista
    prev->next = adj;
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

void graph_print_adjacencies_lists(Graph *g)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%d: ", i+1);

        Adjacencies *adj = g->adjacencies[i].head;

        while (adj != NULL)
        {
            printf("%d ", adj->vertex);
            adj = adj->next;
        }
        printf("\n");
    }
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
    free(g->uteis);
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

int *graph_get_uteis(Graph *g){
    return g->uteis;
}

int graph_get_uteis_size(Graph *g){
    return (g->qtdServer + g->qtdClient + g->qtdMonitor);
}

double adjacencies_get_edge_weight(Adjacencies *adj){
    return adj->weight;
}

int adjacencies_get_vertex(Adjacencies *adj){
    return adj->vertex;
}

int graph_get_element_util(Graph *g, int idx){
    return g->uteis[idx];
}

int _binary_search(int value, int size, int *a){
    int e = -1, d = size;
    while( e < d-1 ){
        int m = (e + d) / 2;
        if( a[m] < value ) e = m;
        else d = m;
    }
    return d;
}

/* ====================== ITERADOR PARA UMA LISTA DE ADJACENCIA ====================== */

AdjacenciesIterator *adjacencies_front_iterator(){

    AdjacenciesIterator *it = (AdjacenciesIterator*) malloc(sizeof(AdjacenciesIterator));

    return it;
}

void adjacencies_iterator_refresh(AdjacenciesIterator *it, List *list)
{
    it->current = list->head;
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