
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
  pid_t pid;
  int x = 5;

  // Try to branch into two separate processes
  pid = fork();

  if (pid == 0) {
    // In the child process
    printf("child: x=%d\n", ++x);
    exit(EXIT_SUCCESS);
  } else if (pid < 0) {
    // Forking error occurred 
    printf("could not branch (fork error): %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    // In the parent process
    printf("parent: x=%d\n", --x);
    exit(EXIT_SUCCESS);
  }
}

