#include "stdio.h"
#include "vector.h"

void test_realloc(void);
void free_test_struct(void* ptr);
void test_user_supplied_free(void);

int main()
{
  test_realloc();

  test_user_supplied_free();

  return 0;
}

typedef struct testStruct {
  int* i;
} testStruct;

void test_realloc() {
  vector* vector = vector_new();

  for( int i = 0; i < 100; ++i ) {
    int* testData = malloc(sizeof(int));
    *testData = i;
    vector_push_back(vector, testData);
  }

  vector_free(vector, NULL);
}

void free_test_struct(void* ptr) {
  testStruct* t = (testStruct*)(ptr);
  free(t->i);
  free(t);
}

void test_user_supplied_free() {
  //printf("Creating vector\n");
  vector* vector = vector_new();

  for( int i = 0; i < 10; ++i ) {
    testStruct* testData = malloc(sizeof(testStruct));
    testData->i = malloc(sizeof(int));
    *testData->i = i;
    vector_push_back(vector, testData);
  }

  vector_free(vector, free_test_struct);
}
