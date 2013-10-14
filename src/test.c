#include "stdio.h"
#include "vector.h"

vector* create_test_vector(void);
void test_realloc(void);
void free_test_struct(void* ptr);
void test_user_supplied_free(void);
void test_at(void);
void test_front_and_back(void);
void test_vector_copy(void);
void test_vector_reserve(void);
void test_empty(void);

int main()
{
  test_realloc();

  test_user_supplied_free();

  test_at();

  test_front_and_back();

  //test_vector_copy();
  
  test_vector_reserve();

  test_empty();

  return 0;
}

vector* create_test_vector(void) {
  vector* new_vector = vector_new();

  for( int i = 0; i < 50; ++i ) {
    int* testData = malloc(sizeof(int));
    *testData = i;
    vector_push_back(new_vector, testData);
  }

  return new_vector;
}

typedef struct testStruct {
  int* i;
} testStruct;

void test_realloc() {
  vector* v = vector_new();

  for( int i = 0; i < 100; ++i ) {
    int* testData = malloc(sizeof(int));
    *testData = i;
    vector_push_back(v, testData);
  }

  vector_free(v, NULL);
}

void free_test_struct(void* ptr) {
  testStruct* t = (testStruct*)(ptr);
  free(t->i);
  free(t);
}

void test_user_supplied_free() {
  vector* v = vector_new();

  for( int i = 0; i < 10; ++i ) {
    testStruct* testData = malloc(sizeof(testStruct));
    testData->i = malloc(sizeof(int));
    *testData->i = i;
    vector_push_back(v, testData);
  }

  vector_free(v, free_test_struct);
}

void test_at() {
  vector* v = create_test_vector();

  //int* element = (int*)vector_at(v, 9);

  //void* nullPtr = vector_at(v, 100);
  //int* intPtr = (int*)nullPtr;

  //printf("Element at [5] = %i\n", *element);
  //printf("Element at [100] = %p\n", intPtr);

  vector_free(v, NULL);
}

void test_front_and_back() {
  vector* v = create_test_vector();


  int* first_element = (int*)vector_front(v);
  int* last_element = (int*)vector_back(v);

  printf("First element = %i\n", *first_element);

  printf("Last element = %i\n", *last_element);

  vector_free(v, NULL);
}

void test_vector_copy() {
  vector* v = create_test_vector();
  vector* copy = vector_copy(v);

  int* v_element =  (int*)vector_at(v, 5);
  int* copy_element =  (int*)vector_at(copy, 5);

  printf("v[5] = %i at %p\n", *v_element, v_element);
  printf("v[5] = %i at %p\n", *copy_element, copy_element);

  vector_free(v, NULL);
}

void test_vector_reserve(void) {
  vector* v = vector_new();

  printf("vector size = %lu\n", vector_size(v));
  printf("vector capacity = %lu\n", vector_capacity(v));

  vector_reserve(v, 50);

  for(int i = 0; i < 100; ++i) {
    int* data = malloc(sizeof(int));
    *data = i;
    vector_push_back(v, data);
  }

  printf("vector size = %lu\n", vector_size(v));
  printf("vector capacity = %lu\n", vector_capacity(v));

  vector_free(v, NULL);
}

void test_empty() {
  vector* v = create_test_vector();

  printf("Is v empty? %d\n", vector_empty(v));

  vector* empty = vector_new();

  printf("Is empty empty? %d\n", vector_empty(empty));
}
