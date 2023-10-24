#include "../headers/algorithms.h"

void _inicializa_dijkstra(Graph *graph, int numVertexStart, Vertex **vertices){

    int numVertices = graph_get_num_vertices(graph);
    
    for(int i=0; i < numVertices; i++){
        vertex_atualiza_distancia(vertices[i], INFINITO);
        vertex_atualiza_pai(vertices[i], NULL);
    }
    
    vertex_atualiza_distancia(vertices[numVertexStart], 0);
}

void dikstra(Graph *graph, int numVertexStart, Vertex **vertices){

    // Inicializa os vértices com infinito e NULL, exceto o inicial que recebe distancia 0
    _inicializa_dijkstra(graph, numVertexStart, vertices);

    // Constroi o Heap e insere todos os vértices do grafo nele
    Heap *heap = heap_construct(graph_get_num_vertices(graph), vertex_get_numVertex);

    for (int i = 0; i < graph_get_num_vertices(graph); i++)
        heap_insert(heap, vertices[i]);
    

    AdjacenciesIterator *it;
    Vertex *min;
    Adjacencies *data;
    int idxVertex;

    // Looping principal: Enquanto o Heap nao estiver vazio
    //                    Remova o vertice mais prioritario (com a menor distancia)
    //                    Inicializa o iterador para andar sobre os vertices adjacentes ao min
    //                    
    //                    Looping interno: Acesse o proximo item na lista de adjacencia
    //                                     Relaxa a aresta

    while (!heap_is_empty(heap)) {
        min = heap_remove(heap);

        it = adjacencies_front_iterator(graph_get_list(graph, vertex_get_numVertex(min)));

        while (!adjacencies_iterator_is_over(it)) {
            data = adjacencies_iterator_next(it);

            idxVertex = adjacencies_get_vertex(data);
            relaxa(min, vertices[idxVertex], adjacencies_get_edge_weight(data), heap);
        }

        adjacencies_iterator_destroy(it);
    }

    heap_destroy(heap);
}

// Se a distancia no vértice b for maior que a distancia do a + peso da aresta entao atualiza a distancia e o pai de b
//
void relaxa(Vertex *a, Vertex *b, double weight, Heap *heap){
    
    if(vertex_get_distancia(a) + weight < vertex_get_distancia(b)){

        // Atualiza o vértice b
        vertex_atualiza_distancia(b, vertex_get_distancia(a) + weight);
        vertex_atualiza_pai(b, a);

        // Ajeita o heap com a nova prioridade de b
        heap_insert(heap, b);
    }
}

