#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"

int main(int argc, char *argv[])
{
    if(argc <= 1) exit(printf("ERRO\nrun ./main <file>\n"));
    
    Graph *g = graph_read_file(argv[1]);

    graph_show(g);

    graph_destroy(g);
    
    return 0;
}

/* Vector : 10,656 allocs, 10,656 frees, 2,096,296 bytes */

/* List :
    10000 : 39,999 allocs, 39,999 frees, 1,058,968 bytes | 0m0.176s
    1000  : 3,999 allocs,  3,999 frees,  113,968 bytes   | 0m0.018s
    100   : 399 allocs,    399 frees,    19,468 bytes    | 0m0.004s
    10    : 39 allocs,     39 frees,     10,018 bytes    | 0m0.003s
*/ 