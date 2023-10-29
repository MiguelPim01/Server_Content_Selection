#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/algorithms.h"

/* ====================== ALGORITMO DE DIJKSTRA ====================== */

void _inicializa_dijkstra(Graph *graph, int numInicialVertex, Vertex *vertices, Heap *heap){

    int numVertices = graph_get_num_vertices(graph);
    
    for(int i = 0; i < numVertices; i++){

        vertices[i].distancia = INFINITO;

        heap_insert(heap, &vertices[i]);
    }
    
    vertices[numInicialVertex].distancia = 0;
}

// Se a distancia no vértice b for maior que a distancia do a + peso da aresta entao atualiza a distancia e o pai de b
//
void _relaxa_aresta(Vertex *a, Vertex *b, double weight, Heap *heap){
    
    if(a->distancia + weight < b->distancia){

        // Atualiza o vértice b
        b->distancia = a->distancia + weight;

        // Ajeita o heap com a nova prioridade de b
        heap_insert(heap, b);
    }
}

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex *vertices, Heap *heap){

    // Inicializa os vértices com infinito e NULL, exceto o inicial que recebe distancia 0
    _inicializa_dijkstra(graph, numInicialVertex, vertices, heap);

    AdjacenciesIterator *it = adjacencies_front_iterator();
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

        adjacencies_iterator_refresh(it, graph_get_list(graph, vertex_get_numVertex(min)));

        while (!adjacencies_iterator_is_over(it)) {
            data = adjacencies_iterator_next(it);

            idxVertex = adjacencies_get_vertex(data);

            /* Economiza nas chamadas de função (para o caso 700.000, reduz em 2seg o tempo de execução) */
                // weight = adjacencies_get_edge_weight(data);
                // v = &vertices[idxVertex];
                // if (min->distancia + weight < v->distancia)
                // {
                //     v->distancia = min->distancia + weight;

                //     heap_insert(heap, v);
                // }

            _relaxa_aresta(min, &vertices[idxVertex], adjacencies_get_edge_weight(data), heap);
        }
    }

    adjacencies_iterator_destroy(it);
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
//       Todos os caminhos mínimos deverão ser armazenados na matriz de double
//
double **rtt_algorithm(Graph *graph)
{
    /* INICIALIZAÇÃO */

    int qtdVertices = graph_get_num_vertices(graph),
        totalSize = graph_get_uteis_size(graph),
        *verticesUteis = graph_get_uteis(graph);

    double **matriz = _aloca_matriz(totalSize);

    Vertex *vertices = (Vertex *)malloc(sizeof(Vertex) * qtdVertices);
    
    Heap *heap = heap_construct(qtdVertices);

    for (int i = 0; i < qtdVertices; i++){
        vertices[i].numVertex = i;
    }

    /* USANDO DIJKSTRA */

    clock_t start, end;
    double total = 0;
    
    for(int i = 0; i < totalSize; i++){
    
        start = clock();
        dijkstra_algorithm(graph, verticesUteis[i], vertices, heap);
        end = clock();

        total += (double)(end - start)/CLOCKS_PER_SEC;

        for(int j = 0; j < totalSize; j++){

            if( i - j )
                matriz[i][j] = vertex_get_distancia(&vertices[verticesUteis[j]]);
        }
    }

    printf("Tempo total de execução do Dijkstra: %.4lf\n", total);
    printf("Tempo medio de execução do Dijkstra: %.4lf\n", total/totalSize);


    /* LIBERANDO MEMORIA */

    free(vertices);
    heap_destroy(heap);

    return matriz;
}

double calcula_rtt(double **matriz, int idx1, int idx2){
    return matriz[idx1][idx2] + matriz[idx2][idx1];
}

double calcula_rtt_asterisco(double **matriz, int idxServer, int idxCliente, Graph *g){

    int numMonitores = graph_get_monitor_size(g);
    int numVertices = graph_get_client_size(g) + graph_get_server_size(g);

    double current = 0.0;
    double min = INFINITO;

    for(int i=0; i < numMonitores; i++){
        current = calcula_rtt(matriz, idxServer, numVertices+i) + calcula_rtt(matriz, idxCliente, numVertices+i);

        if(min > current) min = current;
    }

    return min;
}

double calcula_inflacao_rtt(double **matriz, int idxServer, int idxCliente, Graph *g){
    
    double rtt = calcula_rtt(matriz, idxServer, idxCliente);
    double rtt_asterisco = calcula_rtt_asterisco(matriz, idxServer, idxCliente, g);

    return rtt_asterisco/rtt;
}

void matriz_destroy(double ** matriz, int size){
    for(int i = 0; i < size; i++)
        free(matriz[i]);
    free(matriz);
}