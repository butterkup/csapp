#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    int errno = atoi(argv[i]);
    printf("%d - %s\n", errno, strerror(errno));
  }
}
