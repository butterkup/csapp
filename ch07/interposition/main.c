#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int *i = malloc(sizeof(i));
  *i = 32;
  long *array = malloc(sizeof(long[3]));
  array[0] = 67;
  array[1] = 68;
  array[2] = 69;
  array[1] += *i;
  free(i);
  long *sum = malloc(sizeof(long));
  *sum = array[0] + array[1] + array[2];
  free(array);
  long *sqsum = malloc(sizeof(long));
  *sqsum = *sum * *sum;
  free(sum);
  printf("sqsum = %ld\n", *sqsum); // prints: sqsum = 55696
  free(sqsum);
}
