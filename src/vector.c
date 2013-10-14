#include "stdlib.h"
#include "stdio.h"

#include "vector.h"

vector* vector_new() {
  vector* new_vector = malloc(sizeof(vector));
  new_vector->total_size = DEFAULT_VECTOR_SIZE;
  new_vector->container = malloc(sizeof(void*) * DEFAULT_VECTOR_SIZE);
  new_vector->current_size = 0;
  
  return new_vector;
}

void vector_free(vector* v, void freeFunc(void*)) {
  // If no function was supplied, call free on each ptr
  // contained in our vector.
  if(freeFunc == NULL) {
    for(unsigned long i = 0; i < v->current_size; ++i) {
      free(v->container[i]);
    }
  }
  // Otherwise, call the user supplied function.
  else {
    for(unsigned long i = 0; i < v->current_size; ++i) {
      freeFunc(v->container[i]);
    }
  }
  free(v->container);
  free(v);
}

void grow_vector(vector* v) {
  v->total_size = v->total_size * 2;
  void* ptr = realloc(v->container, sizeof(void*) * v->total_size);
  if(ptr == NULL) {
    printf("Call to realloc failed.");
  }
  v->container = ptr;
}

void vector_push_back(vector* v, void* element) {
  if(v->current_size == v->total_size) {
    grow_vector(v);
  }
  v->container[v->current_size++] = element;
}
