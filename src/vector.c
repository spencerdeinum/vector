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

vector* vector_copy(vector* v) {
  vector* new_vector = vector_new();

  for(unsigned long i = 0; i < v->current_size; ++i ) {
    vector_push_back(new_vector, vector_at(v, i));
  }

  return new_vector;
}

void realloc_container(vector* v) {
  void* ptr = realloc(v->container, sizeof(void*) * v->total_size);
  if(ptr == NULL) {
    printf("Call to realloc failed.");
  }
  v->container = ptr;
}

void grow_vector(vector* v) {
  v->total_size = v->total_size * 2;
  realloc_container(v);
}

void grow_vector_to_length(vector* v, unsigned long length) {
  v->total_size = length;
  realloc_container(v);
}

void vector_push_back(vector* v, void* element) {
  if(v->current_size == v->total_size) {
    grow_vector(v);
  }
  v->container[v->current_size++] = element;
}

void* vector_at(vector* v, unsigned long index) {
  void* ptr = NULL;
  if( index < v->total_size ) {
    ptr = v->container[index];
  }

  return ptr;
}

void* vector_front(vector* v) {
  return v->container[0];
}

void* vector_back(vector* v) {
  return v->container[v->current_size - 1];
}

unsigned long vector_size(vector* v) {
  return v->current_size;
}

unsigned long vector_capacity(vector* v) {
  return v->total_size;
}

void vector_reserve(vector* v, unsigned long length) {
  if( length > v->total_size ) {
    grow_vector_to_length(v, length);
  }
}

bool vector_empty(vector* v) {
  return v->current_size == 0;
}
