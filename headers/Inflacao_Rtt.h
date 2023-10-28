#ifndef _INFLACAO_RTT_H_
#define _INFLACAO_RTT_H_

typedef struct Inflacao_Rtt Inflacao_Rtt;

Inflacao_Rtt *inflacao_rtt_construct();

void inflacao_rtt_destroy(Inflacao_Rtt *inflacao);

int compara_inflacao(const void *infla1, const void *infla2);

int inflacao_rtt_get_cliente(Inflacao_Rtt *i);
int inflacao_rtt_get_server(Inflacao_Rtt *i);
double inflacao_rtt_get_inflacao(Inflacao_Rtt *i);

#endif