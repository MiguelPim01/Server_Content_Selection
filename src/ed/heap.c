#include <stdio.h>
#include <stdlib.h>

#include "../../headers/heap.h"

typedef struct HashTable {
    int *hash_table;
    int (*vertex_key)(Vertice *);
} HashTable;

struct Heap {
    data_type *pq;
    HashTable *hash;
    int size;
    int alocado;
};

HashTable *_hash_table_construct(int size, int (fptr_key)(Vertice *))
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));

    ht->hash_table = (int *)malloc(sizeof(int)*size);
    ht->vertex_key = fptr_key;

    for (int i = 0; i < size; i++)
        ht->hash_table[i] = -1;
    
    return ht;
}

void _hash_table_set(HashTable *ht, data_type data, int i)
{
    int index = ht->vertex_key(data);

    ht->hash_table[index] = i;
}

int _hash_table_get(HashTable *ht, data_type data)
{
    int index = ht->vertex_key(data);

    return ht->hash_table[index];
}

void _hash_table_destroy(HashTable *ht)
{
    free(ht->hash_table);
    free(ht);
}

Heap *heap_construct(int qtd_vertices, int (*fptr_key)(Vertice *))
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    h->pq = (data_type *)malloc(sizeof(data_type)*qtd_vertices);
    h->hash = _hash_table_construct(qtd_vertices, fptr_key);

    h->alocado = qtd_vertices;
    h->size = 0;

    return h;
}

void _heapfy_up(Heap *h, int i)
{
    // TODO: fazer correção de um item para cima

    int pai = (int)(i-1)/2;

    while (pai != i && less(h->pq[i], h->pq[pai]))
    {
        // Apos a troca dos valores atualiza eles na tabela hash
        _hash_table_set(h->hash, h->pq[i], pai);
        _hash_table_set(h->hash, h->pq[pai], i);

        exch(h->pq[i], h->pq[pai]);

        i = pai;
        pai = (int)(i-1)/2;
    }
}

void _heapfy_down(Heap *h, int i)
{
    // TODO: fazer correção de um item para baixo

    while (2*i+1 < h->size)
    {
        int filho = 2*i+1;

        if (filho + 1 < h->size && less(h->pq[filho+1], h->pq[filho]))
            filho++;
        
        if (less(h->pq[i], h->pq[filho]) || equals(h->pq[i], h->pq[filho]))
            break;

        // troca os valores e atualiza eles na tabela hash
        _hash_table_set(h->hash, h->pq[i], filho);
        _hash_table_set(h->hash, h->pq[filho], i);

        exch(h->pq[i], h->pq[filho]);

        i = filho;
    }
}

void heap_insert(Heap *h, data_type data)
{
    // Verificar se o vertice ja existe na fila com prioridade
    int index = _hash_table_get(h->hash, data);

    if (index == -1)
    {
        // Se nao estiver, inserir o vertice no heap

        h->pq[h->size] = data;
        _hash_table_set(h->hash, data, h->size);

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
    _hash_table_set(h->hash, h->pq[h->size-1], 0);
    _hash_table_set(h->hash, h->pq[0], -1);

    // Pega o valor do vertice de maior prioridade e troca com o de menor
    data_type rtn = h->pq[0];
    exch(h->pq[0], h->pq[h->size-1]);

    h->size--;
    _heapfy_down(h, 0);

    return rtn;
}

void heap_destroy(Heap *h)
{
    _hash_table_destroy(h->hash);
    free(h->pq);
    free(h);
}

int isHeapEmpty(Heap *heap){
    return heap->size;
}