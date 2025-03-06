
#include <stdio.h>
#include <unistd.h>

int main() {
  char *const argv[] = {"Argument One", "Two", "Arg Three", "4",
                        "5.0",          "six", NULL};
  char *const envp[] = {
      "name=John Doe",          "favorite_shell=/bin/bash", "age=22",
      "leisure=binge watching", "reading=computer systems", NULL};
  if (execve("./args", argv, envp) < 0) {
    puts("Compile args.c to executable args then "
         "run this program, could not resolve ./args");
  }
  return 2;
}
