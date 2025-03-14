#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SPRINTFBUFSIZ 100
#define RESOLVE_MALLOC_ERROR 1
#define RESOLVE_FREE_ERROR 2
#define SPRINTF_BUFFER_OVERFLOW 3

/*
 * After hundreds of hours tying to get this working, it turns out
 * that printf allocates which leads to an infinite recursion of
 * malloc calling printf and printf calling malloc back, the dance
 * goes on to the end of the world (stack, hehe) and wala, your
 * process earns a segfault badge of honor, you run well.
 * To fix that, we print into a small buffer that is allocated on
 * the stack which is perfect for the job, hopefully char[SPRINTFBUFSIZ]
 * is enough.
 */
#define print(...)                                                             \
  {                                                                            \
    char buffer[SPRINTFBUFSIZ] = {0};                                          \
    int length = sprintf(buffer, __VA_ARGS__);                                 \
    if (length > SPRINTFBUFSIZ) {                                              \
      eprint("sprintf buffer overflow");                                       \
      exit(SPRINTF_BUFFER_OVERFLOW);                                           \
    }                                                                          \
    write(1, buffer, length);                                                  \
  }

#define eprint(msg)                                                            \
  {                                                                            \
    write(2, msg, strlen(msg));                                                \
    fflush(stderr);                                                            \
  }

static void exit_on_error(int code) {
  const char *error;
  if ((error = dlerror()) != NULL) {
    eprint(error);
    exit(code);
  }
}

void *malloc(unsigned long size) {
  char buffer[100];
  static void *(*malloc_fn)(unsigned long) = NULL;
  if (malloc_fn == NULL)
    malloc_fn = dlsym(RTLD_NEXT, "malloc");
  exit_on_error(RESOLVE_MALLOC_ERROR);
  void *slab = malloc_fn(size);
  print("malloc(%lu) = %p\n", size, slab);
  return slab;
}

void free(void *slab) {
  static void (*free_fn)(void *) = NULL;
  if (free_fn == NULL)
    free_fn = dlsym(RTLD_NEXT, "free");
  exit_on_error(RESOLVE_FREE_ERROR);
  print("free(%p)\n", slab);
  free_fn(slab);
}
