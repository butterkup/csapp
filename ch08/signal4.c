#include <signal.h>
#include <stdio.h>
#include <stdint.h>

/*
This function will never finish since the OS
also relies on the SIGSEGV to load pages from
memory when the CPU tries to access virtual
memory that is not loaded, that means after 
a SEGFAULT signal, the instruction that caused
it is re-executed assuming now the appropriate
pages are loaded, the address is now valid and
the instruction will be successfull, but here,
we are not doing much to fix the issue leading
to the infinite recursion.
*/

int exit_status = 0;

void handler(int sig) {
  // puts("SIGSEGV received");
  exit_status ++;
}

int main() {
  signal(SIGSEGV, handler);
  for (int cnt = 1; cnt < 100; cnt++) {
    printf("Try %d\n", cnt);
    fflush(stdout);
    // Try writing to null!
    *(volatile int *)0 = 0;
  }
  puts("");
  return exit_status;
}
