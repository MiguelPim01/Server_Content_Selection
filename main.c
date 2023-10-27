#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"
#include "headers/algorithms.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    // EXECUÇÃO DOS ALGORITMOS:

    graph_show(g);

    double **matriz_resultado = rtt_algorithm(g);

/*
*/
    int qtdVertices = graph_get_server_size(g) + graph_get_client_size(g);
    for(int i = 0; i < qtdVertices; i++){
        for(int j = qtdVertices + 1; j < qtdVertices; j++){
            // printf("%.2lf ", matriz_resultado[i][j]);
        }
        free(matriz_resultado[i]);
        // printf("\n");
    }
    free(matriz_resultado);
    
    graph_destroy(g);

    return 0;
}