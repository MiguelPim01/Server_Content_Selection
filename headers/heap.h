#ifndef HEAP_H
#define HEAP_H

#include "vertex.h"

typedef Vertex* data_type;
typedef struct Heap Heap;

#define key(A) vertex_get_distancia(A)
#define exch(A, B) { data_type d; d = A; A = B; B = d; }
#define less(A, B) (key(A) < key(B))
#define equals(A, B) (key(A) == key(B))

Heap *heap_construct(int qtd_vertices, int (*fptr_key)(Vertex*));

void heap_insert(Heap *h, data_type data);

data_type heap_remove(Heap *h);

void heap_destroy(Heap *h);

int heap_is_empty(Heap *heap);

#endif