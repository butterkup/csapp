#include <stdio.h>

long scale(long x, long y, long z) { return x + 4 * y + 12 * z; }

int main(int, char **) {
  long x = 4, y = 7, z = 10;
  printf("scale(%ld, %ld, %ld) = %ld\n", x, y, z, scale(x, y, z));
}
