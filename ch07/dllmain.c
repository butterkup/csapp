#include "dllhdr.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void check_dlerror(int code) {
  const char *error;
  if ((error = dlerror()) != NULL) {
    printf("Error: %s\n", error);
    exit(code);
  }
}

int main() {
  Person stranger = (Person){.name = "John Doe", .age = 43};
  void *handle;
  const char *error;
  void (*greeter)(FILE *, Person *);
  int (*timegone)(Person *, int);
  handle = dlopen("./libdll.so", RTLD_LAZY);
  check_dlerror(10);
  greeter = dlsym(handle, "person_greet");
  check_dlerror(11);
  timegone = dlsym(handle, "person_age_by");
  check_dlerror(12);
  greeter(stdout, &stranger);
  puts("Seven years later!");
  timegone(&stranger, 7);
  greeter(stdout, &stranger);
  dlclose(handle);
  check_dlerror(13);
}
