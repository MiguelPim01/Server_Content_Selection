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

    if(!arq) exit(printf("ERROR in open file (src/ed/graph.c/graph_read_file)\n"));

    int v, e, v1, v2, s, c, m;
    double weight;

    fscanf(arq, "%d %d", &v, &e);
    Graph *g = graph_construct(v, e);

    fscanf(arq, "%d %d %d", &s, &c, &m);

    int tam = s + m + c;
    for(int i = 0; i < tam; i++){
        fscanf(arq, "%d", &v1);
        if( s ){
            g->vertex_types[v1] = SERVER;
            s--;

        } else if( c ){
            g->vertex_types[v1] = CLIENT;
            c--;

        } else {
            g->vertex_types[v1] = MONITOR;

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


        
    free(g->vertex_types);
    free(g);
}

int graph_get_num_vertices(Graph *g){
    return g->num_vertices;
}

List *graph_get_list(Graph *g, int idx){
    return &g->adjacencies[idx];
}

double adjacencies_get_edge_weight(Adjacencies *adj){
    return adj->weight;
}

int adjacencies_get_vertex(Adjacencies *adj){
    return adj->vertex;
}

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