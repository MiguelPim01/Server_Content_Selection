#include "../../headers/dikstra_alg.h"

void inicializa(Graph *graph, int numVertexStart, Vertex **vertexes){

    int numVertexes = graph_get_num_vertexes(graph);
    
    for(int i=0; i < numVertexes; i++){
        vertex_atualiza_distancia(vertexes[i], INFINITO);
        vertex_atualiza_pai(vertexes[i], NULL);
    }
    
    vertex_atualiza_distancia(vertexes[numVertexStart], 0);
}

void dikstra(Graph *graph, int numVertexStart, Vertex **vertexes){

    inicializa(graph, numVertexStart, vertexes);

    Heap *heap = heap_construct(graph_get_num_vertexes(graph), vertex_get_numVertex);

    for(int i=0; i < graph_get_num_vertexes(graph); i++)
        heap_insert(heap, vertexes[i]);
    
    while(isHeapEmpty(heap)){
        Vertex *min = heap_remove(heap);

        AdjacenciesIterator *it = Adjacencies_front_iterator(graph_get_list(graph, vertex_get_numVertex(min)));

        while(!Adjacencies_iterator_is_over(it)){
            Adjacencies *data = Adjacencies_iterator_next(it);
            int idxVertex = adjacencies_get_vertex(data);

            relaxa(min, vertexes[idxVertex], adjacencies_get_edge_weight(data), heap);
        }

        Adjacencies_iterator_destroy(it);
    }

    heap_destroy(heap);
}

void relaxa(Vertex *a, Vertex *b, double weight, Heap *heap){
    
    if(vertex_get_distancia(a) + weight < vertex_get_distancia(b)){
        vertex_atualiza_distancia(b, vertex_get_distancia(a) + weight);
        heap_insert(heap, b);
        vertex_atualiza_pai(b, a);
    }
}

