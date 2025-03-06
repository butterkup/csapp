
#include <stddef.h>
#include <stdio.h>

void nulltermarr(const char *heading, const char *prefix, const char **arr) {
  size_t index = 0;
  puts(heading);
  while (*arr != NULL) {
    printf("%s[%lu]: \e[3m%s\e[0m\n", prefix, index++, *arr++);
  }
}

int main(int argc, const char **argv, const char **envp) {
  nulltermarr("\e[4mCommand line arguments\e[0m", "\targ", argv);
  nulltermarr("\e[4mEnvironment variables\e[0m",  "\tenv", envp);
}
