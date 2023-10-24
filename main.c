#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"
#include "headers/dikstra_alg.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    Vertex **vertexes = (Vertex**) malloc(sizeof(Vertex*) * graph_get_num_vertexes(g));

    for(int i=0; i < graph_get_num_vertexes(g); i++){
        vertexes[i] = vertex_construct(i); 
    }
    printf("Infinito : %d\n", INFINITO);
    dikstra(g, 0, vertexes);

    
    for(int i=0; i < graph_get_num_vertexes(g); i++){
        vertex_print(vertexes[i]);
    }
    
    graph_show(g);

    for(int i=0; i < graph_get_num_vertexes(g); i++){
        vertex_destroy(vertexes[i]);
    }
    free(vertexes);
    graph_destroy(g);

    return 0;
}