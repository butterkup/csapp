#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <threads.h>
#include "header.h"

/*
The only uncatchable signals are SIGKILL and SIGSTOP
*/

void handler(int sig) {
  switch (sig) {
#define SIGNAL(signal)                                                         \
  case signal:                                                                 \
    puts("Caught " #signal);                                                   \
    break;
#include "signals.h"
#undef SIGNAL
  default:
    printf("Unexpected signal %d\n", sig);
  }
}

void signal_self(int sec_delay) {
#define RAISESIGNAL(sig)                                                       \
  raise(sig);                                                                  \
  Sleep(sec_delay)
#define ISCATCHABLE(sig) (sig != SIGKILL && sig != SIGSTOP)
#define SIGNAL(sig)                                                            \
  if (ISCATCHABLE(sig)) {                                                      \
    RAISESIGNAL(sig);                                                          \
  }
#include "signals.h"
  // To end this process
  raise(SIGKILL);
#undef SIGNAL
#undef ISCATCHABLE
#undef RAISESIGNAL
}

int thread_task(void *sec_delay) {
  signal_self(*(int *)sec_delay);
  return thrd_success;
}

int main() {
#define SIGNAL(sig) signal(sig, handler);
#include "signals.h"
#undef SIGNAL
  
#ifdef THRDRAISE
  int delay = 1;
  thrd_t raiser;
  if (thrd_create(&raiser, thread_task, &delay) != 0) {
    panic("could not create thread\n");
  }
#endif

  while (1) {
    puts("Waiting for signals...");
    // Busy waiting is mad expensive!
    pause();
  }
}
