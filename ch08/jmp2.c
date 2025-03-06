#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

sigjmp_buf env;

void handler(int sig) {
  switch (sig) {
  case SIGINT:
    siglongjmp(env, 1);
  case SIGQUIT:
    siglongjmp(env, 2);
  }
}

int main() {
  switch (sigsetjmp(env, 0)) {
  case 0:
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    puts("Starting application...");
    break;
  case 1:
    puts("Restarting application...");
    break;
  case 2:
    puts("Shutting down...");
    return 0;
  }
  while (1) {
    sleep(1);
    puts("Processing data...");
  }
}
