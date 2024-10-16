#include <stdio.h>

int add2(int);

int main(int, char **) {
  int new = 5050;
  printf("new = %d\n", new);
  new = add2(new);
  printf("new = %d\n", new);
}

