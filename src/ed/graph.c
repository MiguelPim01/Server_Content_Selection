#include "../../headers/graph.h"

struct Adjacencies{
    int vertex;
    double weight;
};

struct Graph{
    char *vertex_types;
    int num_vertices;
    int num_edges;
    Adjacencies **adjacencies;
    int *size_adjacencies;
    int *capacity_adjacencies;
};

Graph *graph_construct(int v, int e){
    Graph *g = malloc(sizeof(Graph));

    g->num_vertices = v;
    g->num_edges = e;
    g->vertex_types = malloc(sizeof(char) * v);
    g->adjacencies = malloc(sizeof(Adjacencies*) * v);
    g->size_adjacencies = malloc(sizeof(int) * v);
    g->capacity_adjacencies = malloc(sizeof(int) * v);

    for(int i = 0; i < v; i++){
        g->adjacencies[i] = malloc(sizeof(Adjacencies) * INITIAL_SIZE_ADJACENCY);
        g->vertex_types[i] = 0;
        g->size_adjacencies[i] = 0;
        g->capacity_adjacencies[i] = INITIAL_SIZE_ADJACENCY;
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

    if( g->size_adjacencies[v1] >= g->capacity_adjacencies[v1] ){
        g->capacity_adjacencies[v1] *= GROWTH_RATE_ADJACENCY;
        g->adjacencies[v1] = realloc(g->adjacencies[v1], sizeof(Adjacencies) * g->capacity_adjacencies[v1]);
    }

    //add
    g->adjacencies[v1][g->size_adjacencies[v1]].vertex = v2;
    g->adjacencies[v1][g->size_adjacencies[v1]].weight = weight;
    g->size_adjacencies[v1]++;
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

        for(int j = 0; j < g->size_adjacencies[i]; j++){
            fprintf(arq, "%d -> %d [label = %c%.2lf%c];\n", i, g->adjacencies[i][j].vertex, '"', g->adjacencies[i][j].weight, '"');
            // printf("%d -> %d (%.2f)\n", i, g->adjacencies[i][j].vertex, g->adjacencies[i][j].weight);
        }
    }

    fprintf(arq, "}\n");

    system("dot -Tpng graph.dot -O &");

    fclose(arq);
}

void graph_destroy(Graph *g){

    int tam = g->num_vertices;
    for(int i = 0; i < tam; i++)
        free(g->adjacencies[i]);
    free(g->adjacencies);
    free(g->size_adjacencies);
    free(g->capacity_adjacencies);
    free(g->vertex_types);
    free(g);
}