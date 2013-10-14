#ifndef __VECTOR_H__

#define __VECTOR_H__

#include "stdlib.h"

const static size_t DEFAULT_VECTOR_SIZE = 20;

typedef struct vector {
  unsigned long total_size;
  unsigned long current_size;
  void ** container;
} vector;

struct vector* vector_new(void);

void vector_free(struct vector* v, void freeFunc(void*));

void vector_push_back(struct vector* vector, void* element);

void grow_vector(struct vector* v);

#endif
