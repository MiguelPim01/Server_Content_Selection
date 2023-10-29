#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/graph.h"
#include "headers/algorithms.h"
#include "headers/output.h"


int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    
    /* INICIALIZAÇÃO */
    clock_t start = clock();
    Graph *g = graph_read_file(argv[1]);
    clock_t end = clock();

    printf("Tempo para ler e inicializar o grafo: %.4lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    /* CALCULO DOS CAMINHOS MINIMOS */
    start = clock();
    double **matriz_resultado = rtt_algorithm(g);
    end = clock();

    printf("Tempo para calcular caminhos minimos e armazenar na matriz: %.4lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    /* PROCESSA DADOS FINAIS E PRINTA */
    start = clock();
    output_print_results(g, matriz_resultado);
    end = clock();

    printf("Tempo para processar e printar output: %.4lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    int qtdVertices = graph_get_server_size(g) + graph_get_client_size(g) + graph_get_monitor_size(g);

    matriz_destroy(matriz_resultado, qtdVertices);
    graph_destroy(g);

    return 0;
}