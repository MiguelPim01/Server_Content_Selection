#include <stdio.h>
#include <stdlib.h>

#include "../headers/heap.h"

// Struct heap vista em sala de aula com algumas mudanças.

// Aqui consideramos o índice 0 do vetor.
// E também adicionamos uma "tabela hash", que nesse caso é um vetor de int apenas, com a propriedade de que
// a chave é o número do vértice e o valor naquele índice é o índice do vértice no heap

// Escolhemos essa tabela hash para que quando tivessemos que consertar um valor no heap que foi modificado pelo Dijkstra
// nós pudessemos acessar em tempo O(1).

struct Heap {
    data_type *pq;
    int *hash;
    int size;
    int alocado;
};

Heap *heap_construct(int qtd_vertices)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    h->pq = (data_type *)malloc(sizeof(data_type) * qtd_vertices);
    h->hash = (int *)malloc(sizeof(int) * qtd_vertices);

    for (int i = 0; i < qtd_vertices; i++)
        h->hash[i] = -1;

    h->alocado = qtd_vertices;
    h->size = 0;

    return h;
}

void _heapfy_up(Heap *h, int i)
{
    int pai = (int)(i-1)/2;

    while (pai != i && h->pq[i]->distancia < h->pq[pai]->distancia)
    {
        // Apos a troca dos valores atualiza eles na tabela hash
        h->hash[h->pq[i]->numVertex] = pai;
        h->hash[h->pq[pai]->numVertex] = i;

        exch(h->pq[i], h->pq[pai]);

        i = pai;
        pai = (int)(i-1)/2;
    }
}

void _heapfy_down(Heap *h, int i)
{
    while (2*i+1 < h->size)
    {
        int filho = 2*i+1;

        // less(h->pq[filho+1], h->pq[filho])
        if (filho + 1 < h->size && h->pq[filho+1]->distancia < h->pq[filho]->distancia)
            filho++;
        
        if (h->pq[i]->distancia <= h->pq[filho]->distancia)
            break;

        // troca os valores e atualiza eles na tabela hash
        h->hash[h->pq[i]->numVertex] = filho;
        h->hash[h->pq[filho]->numVertex] = i;

        exch(h->pq[i], h->pq[filho]);

        i = filho;
    }
}

// Essa função já trata os casos em que o vértice existe ou não no heap
//
void heap_insert(Heap *h, data_type data)
{
    // Verificar se o vertice ja existe na fila com prioridade
    int index = h->hash[data->numVertex];

    if (index == -1)
    {
        // Se nao estiver, inserir o vertice no heap

        h->pq[h->size] = data;
        h->hash[data->numVertex] = h->size;

        _heapfy_up(h, h->size);

        h->size++;
    }
    else
    {
        // Se ja estiver e a nova prioridade for menor aplicar heapfy_up

        _heapfy_up(h, index);
    }
}

data_type heap_remove(Heap *h)
{
    // Atualiza o primeiro para -1 (inexistente no heap) e o ultimo para 0
    h->hash[h->pq[h->size-1]->numVertex] = 0;
    h->hash[h->pq[0]->numVertex] = -1;

    // Pega o valor do vertice de maior prioridade e troca com o de menor
    data_type rtn = h->pq[0];
    exch(h->pq[0], h->pq[h->size-1]);

    h->size--;
    _heapfy_down(h, 0);

    return rtn;
}

void heap_destroy(Heap *h)
{
    free(h->hash);
    free(h->pq);
    free(h);
}

int heap_is_empty(Heap *heap) {
    return heap->size == 0;
}