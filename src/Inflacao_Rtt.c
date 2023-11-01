#include "../headers/Inflacao_Rtt.h"
#include <stdlib.h>

// Struct específica para printar o output.

// Foi feita para fazermos a ordenação com o qsort dela.

struct Inflacao_Rtt{
    int server;
    int cliente;
    double inflacao_value;
};

Inflacao_Rtt *inflacao_rtt_construct(int server, int cliente, double inflacao_value){

    Inflacao_Rtt *inflacao = (Inflacao_Rtt*) malloc(sizeof(Inflacao_Rtt));

    inflacao->cliente = cliente;
    inflacao->server = server;
    inflacao->inflacao_value = inflacao_value;

    return inflacao;
}

void inflacao_rtt_destroy(Inflacao_Rtt *inflacao){
    free(inflacao);
}

int compara_inflacao(const void *infla1, const void *infla2){

    Inflacao_Rtt *inflacao1 = *(Inflacao_Rtt**) infla1;
    Inflacao_Rtt *inflacao2 = *(Inflacao_Rtt**) infla2;

    if(inflacao1->inflacao_value == inflacao2->inflacao_value) return 0;
    else if(inflacao1->inflacao_value < inflacao2->inflacao_value) return -1;
    else return 1;
}

int inflacao_rtt_get_cliente(Inflacao_Rtt *i){
    return i->cliente;
}

int inflacao_rtt_get_server(Inflacao_Rtt *i){
    return i->server;
}

double inflacao_rtt_get_inflacao(Inflacao_Rtt *i){
    return i->inflacao_value;
}