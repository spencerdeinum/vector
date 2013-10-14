#include "stdio.h"
#include "vector.c"

int main(int argc, char* argv[])
{
  printf("Creating vector\n");
  struct vector* vector = vector_new();

  printf("Adding to vector\n");
  for( int i = 0; i < 10; ++i ) {
    int* testData = malloc(sizeof(int));
    *testData = i;
    printf("Adding element %i.\n", *testData);
    vector_push_back(vector, testData);
  }

  printf("Destroying vector\n");
  vector_free(vector);

  return 0;
}
