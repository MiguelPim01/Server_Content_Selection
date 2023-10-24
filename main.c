#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"
#include "headers/algorithms.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    Vertex **vertices = (Vertex**) malloc(sizeof(Vertex*) * graph_get_num_vertices(g));

    for(int i=0; i < graph_get_num_vertices(g); i++){
        vertices[i] = vertex_construct(i); 
    }
    printf("Infinito : %d\n", INFINITO);
    dikstra(g, 0, vertices);

    
    for(int i=0; i < graph_get_num_vertices(g); i++){
        vertex_print(vertices[i]);
    }
    
    graph_show(g);

    for(int i=0; i < graph_get_num_vertices(g); i++){
        vertex_destroy(vertices[i]);
    }
    free(vertices);
    graph_destroy(g);

    return 0;
}