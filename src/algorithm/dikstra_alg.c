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

        AdjacenciesIterator *it = Adjacencies_front_iterator(graph_get_list(graph, vertex_get_numVertex(min)));

        while(!Adjacencies_iterator_is_over(it)){
            Adjacencies *data = Adjacencies_iterator_next(it);
        }
    }
}

void relaxa(Vertex *a, Vertex *b, double weight, Heap *heap){
    
    if(vertex_get_distancia(a) + weight < vertex_get_distancia(b)){
        vertex_atualiza_distancia(b, vertex_get_distancia(a) + weight);
        heap_insert(heap, b);
    }
}

