#pragma once

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define panic(...)                                                             \
  fprintf(stderr, __VA_ARGS__);                                                \
  exit(errno || 1);

static pid_t Fork(void) {
  pid_t pid = fork();
  if (pid < 0) {
    panic("forking error: %s\n", strerror(errno));
  }
  return pid;
}

static void Sleep(unsigned int secs) {
  while (secs > 0) {
    secs = sleep(secs);
  }
}

static void Signal(int signum, __sighandler_t handler) {
  if (signal(signum, handler) == SIG_ERR) {
    panic("signal error: could not attach handler (%p) for signal %d\n",
          handler, signum);
  }
}
