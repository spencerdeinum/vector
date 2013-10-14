#include "stdio.h"
#include "vector.c"

struct testStruct {
  int* i;
} testStruct;

void test_realloc() {
  struct vector* vector = vector_new();

  for( int i = 0; i < 100; ++i ) {
    int* testData = malloc(sizeof(int));
    *testData = i;
    vector_push_back(vector, testData);
  }

  vector_free(vector, NULL);
}

void free_test_struct(void* ptr) {
  struct testStruct* testStruct = (struct testStruct*)(ptr);
  free(testStruct->i);
  free(testStruct);
}

void test_user_supplied_free() {
  //printf("Creating vector\n");
  struct vector* vector = vector_new();

  for( int i = 0; i < 10; ++i ) {
    struct testStruct* testData = malloc(sizeof(testStruct));
    testData->i = malloc(sizeof(int));
    *testData->i = i;
    vector_push_back(vector, testData);
  }

  vector_free(vector, free_test_struct);
}

int main(int argc, char* argv[])
{
  test_realloc();

  test_user_supplied_free();

  return 0;
}
