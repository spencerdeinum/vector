#ifndef __VECTOR_H__

#define __VECTOR_H__

#include "stdlib.h"

const static size_t DEFAULT_VECTOR_SIZE = 20;

typedef struct vector {
  unsigned long total_size;
  unsigned long current_size;
  void ** container;
} vector;

vector* vector_new(void);

void vector_free(vector* v, void freeFunc(void*));

vector* vector_copy(vector* v);

void vector_push_back(vector* v, void* element);

void realloc_container(vector* v);

void grow_vector(vector* v);

void grow_vector_to_length(vector* v, unsigned long length);

void* vector_at(vector* v, unsigned long index);

void* vector_front(vector* v);

void* vector_back(vector* v);

unsigned long vector_size(vector* v);

unsigned long vector_capacity(vector* v);

void vector_reserve(vector* v, unsigned long length);

#endif
