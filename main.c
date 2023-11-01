#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/graph.h"
#include "headers/algorithms.h"
#include "headers/output.h"


int main(int argc, char *argv[])
{
    if(argc < 3) exit(printf("ERRO\nrun ./main <file_input> <file_output>\n"));
    
    
    /* INICIALIZAÇÃO */
    
    Graph *g = graph_read_file(argv[1]);

    /* CALCULO DOS CAMINHOS MINIMOS */

    double **matriz_resultado = rtt_algorithm(g);
    
    /* PROCESSA DADOS FINAIS E PRINTA */
    
    output_print_results(g, matriz_resultado, argv[2]);

    int qtdVertices = graph_get_server_size(g) + graph_get_client_size(g) + graph_get_monitor_size(g);

    matriz_destroy(matriz_resultado, qtdVertices);
    graph_destroy(g);

    return 0;
}