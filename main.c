#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"
#include "headers/algorithms.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    // EXECUÇÃO DOS ALGORITMOS:

    double **matriz_resultado = rtt_algorithm(g);

    graph_destroy(g);

    return 0;
}