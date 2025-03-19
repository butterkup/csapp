
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "header.h"

#ifndef CHILDREN
#define CHILDREN 5
#endif


int main() {
  for (int i = 0; i < CHILDREN; i++) {
    if (Fork() == 0) {
      printf("Process %d forked child %d\n", getppid(), getpid());
      exit(100 + i);
    }
  }

  int status;
  pid_t pid;
  // while ((pid = waitpid(-1, &status, 0)) > 0) {
  while ((pid = wait(&status)) > 0) {
    if (WIFEXITED(status)) {
      printf("child %d exited with status %d\n", pid, WEXITSTATUS(status));
    } else {
      printf("abnormal termination\n");
    }
  }

  if (errno != ECHILD) {
    panic("waitpid error: %s\n", strerror(errno));
  }
}
