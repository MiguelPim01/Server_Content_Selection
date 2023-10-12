#include <stdio.h>
#include <stdlib.h>
#include "src/ed/graph.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    graph_show(g);
    
    return 0;
}