#include <stdio.h>

void *__real_malloc(unsigned long size);
void __real_free(void *slab);

void *__wrap_malloc(unsigned long size) {
  void *slab = __real_malloc(size);
  printf("malloc(%lu) = %p\n", size, slab);
  return slab;
}

void __wrap_free(void *slab) {
  printf("free(%p)\n", slab);
  __real_free(slab);
}

