#include "../headers/algorithms.h"

/* ====================== ALGORITMO DE DIJKSTRA ====================== */

void _inicializa_dijkstra(Graph *graph, int numInicialVertex, Vertex **vertices){

    int numVertices = graph_get_num_vertices(graph);
    
    for(int i=0; i < numVertices; i++){
        vertex_atualiza_distancia(vertices[i], INFINITO);
        vertex_atualiza_pai(vertices[i], NULL);
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

void dijkstra_algorithm(Graph *graph, int numInicialVertex, Vertex **vertices){

    // Inicializa os vértices com infinito e NULL, exceto o inicial que recebe distancia 0
    _inicializa_dijkstra(graph, numInicialVertex, vertices);

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


/* ====================== CALCULOS DOS ROUND TRIP TIME (RTT) ====================== */

double **_aloca_matriz(int qtdVertices)
{
    double **m = (double **)malloc(sizeof(double *) * qtdVertices);

    for (int i = 0; i < qtdVertices; i++)
        m[i] = (double *)malloc(sizeof(double) * qtdVertices);
    
    return m;
}

// TODO: Essa função deverá calcular os menores caminhos para os vértices: MONITORES, SERVIDORES e CLIENTES
//       Todos os RTT's deverão ser armazenados na matriz de double
//
double **rtt_algorithm(Graph *graph)
{
    int qtdVertices = graph_get_num_vertices(graph);

    double **matriz = _aloca_matriz(qtdVertices);
    Vertex **vertices = (Vertex **)malloc(sizeof(Vertex *) * qtdVertices);

    for (int i = 0; i < qtdVertices; i++)
        vertices[i] = vertex_construct(i);

    
    // Essa parte muito provavelmente devera ser otimizada depois:
    for (int i = 0; qtdVertices; i++)
    {
        switch (graph_get_vertex_type(graph, i))
        {
            // TODO: Fazer para cada vértice o algoritmo de dijkstra
            // Alocar na matriz todas as menores distancias encontradas para cada execução

            // Lembrando que cada execução do dijkstra preenche UMA linha da matriz

            case SERVER:
                break;
            case CLIENT:
                break;
            case MONITOR:
                break;
            default:
                // Nesse caso nao executa dijkstra
                break;
        }
    }

}