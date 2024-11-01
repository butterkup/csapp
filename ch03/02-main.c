#include <stdio.h>

int main(int argc, char **argv) {
  signed short sshrt;
  unsigned short ushrt;
  long slng = sshrt;
  unsigned long ulng = ushrt;
  printf("\n", sshrt, ushrt, slng, ulng);
}

