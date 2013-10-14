#include "stdlib.h"
#include "stdio.h"

const size_t DEFAULT_VECTOR_SIZE = 20;

struct vector {
  int total_size;
  int current_size;
  void ** container;
} vector;

struct vector* vector_new() {
  struct vector* new_vector = malloc(sizeof(vector));
  new_vector->total_size = DEFAULT_VECTOR_SIZE;
  new_vector->container = malloc(sizeof(void*) * DEFAULT_VECTOR_SIZE);
  new_vector->current_size = 0;
  
  return new_vector;
}

void vector_free(struct vector* vector, void freeFunc(void*)) {
  // If no function was supplied, call free on each ptr
  // contained in our vector.
  if(freeFunc == NULL) {
    for(int i = 0; i < vector->current_size; ++i) {
      free(vector->container[i]);
    }
  }
  // Otherwise, call the user supplied function.
  else {
    for(int i = 0; i < vector->current_size; ++i) {
      freeFunc(vector->container[i]);
    }
  }
  free(vector->container);
  free(vector);
}

void grow_vector(struct vector* vector) {
  vector->total_size = vector->total_size * 2;
  void* ptr = realloc(vector->container, sizeof(void*) * vector->total_size);
  if(ptr == NULL) {
    printf("Call to realloc failed.");
  }
  vector->container = ptr;
}

void vector_push_back(struct vector* vector, void* element) {
  if(vector->current_size == vector->total_size) {
    grow_vector(vector);
  }
  vector->container[vector->current_size++] = element;
}
