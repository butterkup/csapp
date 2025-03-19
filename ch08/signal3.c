#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

void atomic_function() {
  puts("--- Doing one thing.");
  Sleep(1);
  puts("--- Doing another thing.");
  Sleep(2);
  puts("--- Hehe, you cannot interrupt me");
  Sleep(1);
  puts("--- Seriously, try harder!");
  Sleep(3);
  puts("--- I can take all the time in the world.");
  Sleep(5);
  puts("--- Peace (as the mic drops)!");
}

void handler(int sig) {
#define SIGNAL(sig)                                                            \
  case sig:                                                                    \
    puts("Interrupted with " #sig);                                            \
    break;
  switch (sig) {
#include "signals.h"
  default:
    printf("Unexpected signal %d\n", sig);
  }
#undef SIGNAL
}

int main() {
#define SIGNAL(sig) signal(sig, handler);
#include "signals.h"
#undef SIGNAL
  sigset_t mask, prev;
  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, &prev);
  atomic_function();
  sigprocmask(SIG_SETMASK, &prev, NULL);
  atomic_function();
}
