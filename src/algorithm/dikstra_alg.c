#include "../../headers/dikstra_alg.h"

Vertex **inicializa(Graph graph, int numVertexStart){

    int numVertexes = get_num_vertexes(graph);
    Vertex **vertexes = (Vertex**) malloc(sizeof(Vertex*)*numVertexes);

    for(int i=0; i < numVertexes; i++)
        vertexes[i] = vertex_construct(i, NULL, INFINITO);
    
    vertex_atualiza_distancia(vertexes[numVertexStart], 0);

    return vertexes;
}

void dikstra(Graph graph, int numVertexStart){

    Vertex **vertexes = inicializa(graph, vertice);

    Heap *heap = heap_construct(get_num_vertexes(graph), vertex_get_numVertex);

    for(int i=0; i < get_num_vertexes(graph); i++)
        heap_insert(heap, vertexes[i]);
    
    while(!isHeapEmpty(heap)){
        Vertex *min = heap_remove(heap);
    }
}

