#ifndef HEAP_H
#define HEAP_H

#include "vertex.h"

typedef Vertex* data_type;
typedef struct Heap Heap;

#define exch(A, B) { data_type d; d = A; A = B; B = d; }

Heap *heap_construct(int qtd_vertices);

void heap_insert(Heap *h, data_type data);

data_type heap_remove(Heap *h);

void heap_destroy(Heap *h);

int heap_is_empty(Heap *heap);

#endif