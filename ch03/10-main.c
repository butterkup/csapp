#include <stdio.h>

long swap_add(long *, long *);
long caller(long, long);

int main(int argc, char **argv) {
  long a = 1024, b = 5052;
  printf("a = %ld, b = %ld\n", a, b);
  long result = swap_add(&a, &b);
  printf("a = %ld, b = %ld\n", a, b);
  printf("result = %ld\n", result);
  result = caller(45, 20);
  printf("caller_result: (x+y)*(y-x) = %ld\n", result);
}
