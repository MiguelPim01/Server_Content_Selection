#include <stdio.h>
#include <stdlib.h>

#include "../headers/output.h"
#include "../headers/algorithms.h"

void output_print_results(Graph *graph, double **matriz_resultado)
{
    FILE *arq = fopen("Outputs/output.txt", "w");

    if(arq == NULL){
        printf("ERRO AO CRIAR O ARQUIVO DE OUTPUT!\n");
        exit(1);
    }

    for(int i = 0; i < graph_get_server_size(graph); i++){
        int idx = graph_get_element_util(graph, i);
        for(int j = graph_get_server_size(graph); j < graph_get_client_size(graph) + graph_get_server_size(graph); j++){
            int idx2 = graph_get_element_util(graph, j);
            double inflacao = calcula_inflacao_rtt(matriz_resultado, i, j, graph);

            fprintf(arq, "%d %d %lf\n", idx, idx2, inflacao);
        }
    }

    fclose(arq);

    // O output devera ser (< a > < b > < RTT(a, b)/RTT*(a, b) >)
    // Onde "a" é Servidor e "b" é Cliente
}