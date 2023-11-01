#include <stdio.h>
#include <stdlib.h>

#include "../headers/output.h"
#include "../headers/algorithms.h"
#include "../headers/Inflacao_Rtt.h"

void output_print_results(Graph *graph, double **matriz_resultado, char *filePath)
{
    FILE *arq = fopen(filePath, "w");

    if(arq == NULL){
        printf("ERRO AO CRIAR O ARQUIVO DE OUTPUT!\n");
        exit(1);
    }

    Inflacao_Rtt **inflacao = (Inflacao_Rtt**) malloc(sizeof(Inflacao_Rtt*)*graph_get_server_size(graph)*graph_get_client_size(graph));
    int k=0;

    int qtdServer = graph_get_server_size(graph), qtdClient = graph_get_client_size(graph);

    // Calcula todas as inflações e armazena na estrutura para depois ordena-la.
    for(int i = 0; i < qtdServer; i++){
        int idx = graph_get_element_util(graph, i);
        for(int j = qtdServer; j < qtdClient + qtdServer; j++){
            int idx2 = graph_get_element_util(graph, j);
            double inflacao_current = calcula_inflacao_rtt(matriz_resultado, i, j, graph);

            inflacao[k] = inflacao_rtt_construct(idx, idx2, inflacao_current);
            k++;
        }

    }

    // Ordena todos os dados a serem printados de acordo com a terceira coluna (inflação), assim como foi pedido na especificação do trabalho.
    qsort(inflacao, graph_get_server_size(graph)*graph_get_client_size(graph), sizeof(Inflacao_Rtt*), compara_inflacao);
    
    for(int i=0; i < graph_get_server_size(graph)*graph_get_client_size(graph); i++){
        fprintf(arq, "%d %d %.16lf\n", inflacao_rtt_get_server(inflacao[i]),inflacao_rtt_get_cliente(inflacao[i]), inflacao_rtt_get_inflacao(inflacao[i]));
        inflacao_rtt_destroy(inflacao[i]);
    }

    free(inflacao);

    fclose(arq);

}