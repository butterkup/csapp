#include <stdio.h>

void multstore2(long, long, long*);
void multstore3(int, int, int*);
void multstore4(short, short, short*);

int main(int argc, char**argv) {
  long d2;
  int d3;
  short d4;
  multstore2(4, 8, &d2);
  multstore3(4, 8, &d3);
  multstore4(4, 8, &d4);
  printf("4 * 8 --> %d\n", (int)d2);
  printf("4 * 8 --> %d\n", d3);
  printf("4 * 8 --> %d\n", d4);
  return 0;
}

long mult2(long a, long b) {
  long s = a * b;
  return s;
}

int mult3(int a, int b) {
  int s = a * b;
  return s;
}

short mult4(short a, short b) {
  short s = a * b;
  return s;
}

