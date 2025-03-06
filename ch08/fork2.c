
#include "header.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
      Fork    Fork    Fork    process    label
  *----+-------+-------+---------(1)     parent
       |       |       |
       |       |       +---------(2)     child 3
       |       |
       |       +-------+---------(3)     child 2
       |               |
       |               +---------(4)     grandchild 3
       |
       +-------+-------+---------(5)     child 1
               |       |
               |       +---------(6)     grandchild 2
               |
               +-------+---------(7)     grandchild 1
                       |
                       +---------(8)     grandgrandchild
  */
  Fork();
  Fork();
  Fork();
  printf("This should appear 8 times!\n");
  // sleep(10); // jump into htop fast to see the processes
}
