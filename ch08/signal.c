
#include "header.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int reaped = 0;

void handler(int signal) {
  if (signal == SIGCHLD) {
    reaped += 1;
    int status, pid;
    if ((pid = wait(&status)) > 0) {
      if (WIFSIGNALED(status)) {
        printf("Child [%d] received signal %d\n", pid, WTERMSIG(status));
      } else if (WIFEXITED(status)) {
        printf("Child [%d] child exited with %d\n", pid, WEXITSTATUS(status));
      } else {
        printf("Child [%d] behaved abnormally\n", pid);
      }
    } else {
      printf("Child reaping was unsuccessful, the signal was a fake!\n");
    }
  }
}

int main() {
  Signal(SIGCHLD, handler);

  if (Fork() == 0) {
    printf("[%d]: should exit with 23\n", getpid());
    exit(23);
  }

  if (Fork() == 0) {
    printf("[%d]: should be signaled code 8\n", getpid());
    Sleep(1);
    raise(SIGFPE);
    return 100;
  }

  if (Fork() == 0) {
    printf("[%d]: should exit with 15\n", getpid());
    Sleep(2);
    return 15;
  }

  if (Fork() == 0) {
    printf("[%d]: should be signaled code 10\n", getpid());
    Sleep(3);
    raise(SIGUSR1);
    return 100;
  }

  if (Fork() == 0) {
    printf(
        "[%d]: send some signal to this process to see if it exits with it\n",
        getpid());
    // Wait for the signal!
    pause();
    // If ignored, then exit successfully.
    return EXIT_SUCCESS;
  }

  while (reaped < 5) {
    pause();
  }
}
