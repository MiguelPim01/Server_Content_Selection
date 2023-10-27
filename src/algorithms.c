#include <stdio.h>
#include <stdlib.h>

#include "../headers/algorithms.h"

/* ====================== ALGORITMO DE DIJKSTRA ====================== */

void _inicializa_dijkstra(Graph *graph, int numInicialVertex, Vertex **vertices, Heap *heap){

    int numVertices = graph_get_num_vertices(graph);
    
    for(int i = 0; i < numVertices; i++){
        vertex_atualiza_distancia(vertices[i], INFINITO);
        vertex_atualiza_pai(vertices[i], NULL);
        heap_insert(heap, vertices[i]);
    }
    
    vertex_atualiza_distancia(vertices[numInicialVertex], 0);
}

// Se a distancia no vértice b for maior que a distancia do a + peso da aresta entao atualiza a distancia e o pai de b
//
void _relaxa_aresta(Vertex *a, Vertex *b, double weight, Heap *heap){
    
    if(vertex_get_distancia(a) + weight < vertex_get_distancia(b)){

        // Atualiza o vértice b
        vertex_atualiza_distancia(b, vertex_get_distancia(a) + weight);
        vertex_atualiza_pai(b, a);

        // Ajeita o heap com a nova prioridade de b
        heap_insert(heap, b);
    }
}

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex **vertices, Heap *heap){

    // Inicializa os vértices com infinito e NULL, exceto o inicial que recebe distancia 0
    _inicializa_dijkstra(graph, numInicialVertex, vertices, heap);

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
            _relaxa_aresta(min, vertices[idxVertex], adjacencies_get_edge_weight(data), heap);
        }

        adjacencies_iterator_destroy(it);
    }
}


/* ====================== CALCULOS DOS ROUND TRIP TIME (RTT) ====================== */

double **_aloca_matriz(int qtdVertices)
{
    double **m = (double **)malloc(sizeof(double *) * qtdVertices);

    for (int i = 0; i < qtdVertices; i++)
        m[i] = (double *)calloc(qtdVertices, sizeof(double));
    
    return m;
}

// TODO: Essa função deverá calcular os menores caminhos para os vértices: MONITORES, SERVIDORES e CLIENTES
//       Todos os RTT's deverão ser armazenados na matriz de double
//
int *_define_array(Graph *g, int *vertices, int *limite, int *diferenca){
    if( *limite == graph_get_server_size(g) ){
        vertices = graph_get_client(g);
        *diferenca = *limite;
        *limite += graph_get_client_size(g);
        
    } else if( *limite == graph_get_server_size(g) + graph_get_client_size(g) ){
        vertices = graph_get_monitor(g);
        *diferenca = *limite;
    }

    return vertices;
}
#include <stdio.h>
double **rtt_algorithm(Graph *graph)
{
    int qtdVertices = graph_get_num_vertices(graph),
        totalSize = graph_get_server_size(graph) + graph_get_client_size(graph) + graph_get_monitor_size(graph),
        *verticesUteis = graph_get_server(graph),
        limite = graph_get_server_size(graph),
        diferenca = 0;

    double **matriz = _aloca_matriz(totalSize);
    Vertex **vertices = (Vertex **)malloc(sizeof(Vertex *) * qtdVertices);
    Heap *heap = heap_construct(qtdVertices, vertex_get_numVertex);

    for (int i = 0; i < qtdVertices; i++){
        vertices[i] = vertex_construct(i);
    }
    
    // Essa parte muito provavelmente devera ser otimizada depois:
    for(int i = 0; i < totalSize; i++){
        verticesUteis = (i == limite) ? _define_array(graph, verticesUteis, &limite, &diferenca) : verticesUteis;

        dijkstra_algorithm(graph, verticesUteis[i - diferenca], vertices, heap);

        int limite2 = graph_get_server_size(graph), diferenca2 = 0,
            *uteis = graph_get_server(graph);
        for(int j = 0; j < totalSize; j++){
            uteis = ( j == limite2 ) ? _define_array(graph, uteis, &limite2, &diferenca2) : uteis;

            if( i - j )
                matriz[matrixSMC_get_index(graph, verticesUteis[i - diferenca])][matrixSMC_get_index(graph, uteis[j - diferenca2])] = 
                vertex_get_distancia(vertices[uteis[j - diferenca2]]);
        }
    }

    for (int i = 0; i < qtdVertices; i++)
        vertex_destroy(vertices[i]);
    free(vertices);

    heap_destroy(heap);
    return matriz;
}

void matriz_destroy(double ** matriz, int size){
    for(int i = 0; i < size; i++)
        free(matriz[i]);
    free(matriz);
}