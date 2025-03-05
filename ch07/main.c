#include <stdio.h>
#include <unistd.h>

int sum(int n, int array[n]);

int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
extern char longarray[];

void iota() {
  char v = 0;
  for (int i = 0; i < 1024*1024*1024; i++) {
    longarray[i] = v++;
  }
}

int main() {
  int result = sum(9, array);
  iota();
  printf("result = %d\naddress = %p\n", result, longarray);
  sleep(2);
  return result;
}
