#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef long data_t;

typedef struct tensor {
  size_t x, y, z;
  data_t *data;
} Tensor;

#define TENSOR_FUNC_NAME(x, y, z) tensor_sum_##x##y##z
#define XTOSTR(name) #name
#define TOSTR(name) XTOSTR(name)

#define TENSOR_SUM_IMPL(X, Y, Z)                                               \
  ssize_t TENSOR_FUNC_NAME(X, Y, Z)(const Tensor *t) {                         \
    ssize_t sum = 0;                                                           \
    for (size_t X = 0; X < t->X; X++) {                                        \
      for (size_t Y = 0; Y < t->Y; Y++) {                                      \
        for (size_t Z = 0; Z < t->Z; Z++) {                                    \
          sum += t->data[X * t->Y * t->Z + Y * t->Z + Z];                      \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    return sum;                                                                \
  }

ssize_t tensor_sum_linear(const Tensor *t) {
  ssize_t sum = 0;
  for (size_t idx = 0; idx < t->x * t->y * t->z; idx++) {
    sum += t->data[idx];
  }
  return sum;
}

#define GENERATE_PERMS(MACRO)                                                  \
  MACRO(x, y, z, 0)                                                            \
  MACRO(x, z, y, 1)                                                            \
  MACRO(y, x, z, 2)                                                            \
  MACRO(y, z, x, 3)                                                            \
  MACRO(z, x, y, 4)                                                            \
  MACRO(z, y, x, 5)

#define TENSOR_SUM_IMPLS(MACRO)                                                \
  GENERATE_PERMS(MACRO)                                                        \
  MACRO(li, ne, ar, 6)

#define MACRO(x, y, z, i) TENSOR_SUM_IMPL(x, y, z)
GENERATE_PERMS(MACRO)
#undef MACRO

#ifndef DIM_X
#define DIM_X 100
#endif

#ifndef DIM_Y
#define DIM_Y 80
#endif

#ifndef DIM_Z
#define DIM_Z 90
#endif

void iota(size_t len, data_t data[len], data_t start) {
  for (size_t idx = 0; idx < len; idx++, start++) {
    data[idx] = start;
  }
}

struct tensor_sum_args {
  const char *name;
  const Tensor *tensor;
  data_t (*tensor_sum)(const Tensor *);
  data_t result;
};

void tensor_sum_func(void *arg) {
  struct tensor_sum_args *args = arg;
  args->result = args->tensor_sum(args->tensor);
}

const size_t x = DIM_X, y = DIM_Y, z = DIM_Z, arena_size = x * y * z;

#ifndef AVGCNT
#define AVGCNT 100
#endif

int main() {
#ifdef ALLOCATE_ARENA
  data_t *arena = calloc(arena_size, sizeof(data_t));
#else
  data_t arena[arena_size];
#endif

  iota(arena_size, arena, 1);
  const size_t expected_result = (arena_size * (arena_size + 1)) >> 1;
  Tensor tensor = (Tensor){.x = x, .y = y, .z = z, .data = arena};
  struct tensor_sum_args args[] = {
#define MACRO(x, y, z, i)                                                      \
  [i] = (struct tensor_sum_args){.name = TOSTR(TENSOR_FUNC_NAME(x, y, z)),     \
                                 .tensor = &tensor,                            \
                                 .tensor_sum = TENSOR_FUNC_NAME(x, y, z),      \
                                 .result = -1},
      TENSOR_SUM_IMPLS(MACRO)};
#undef MACRO
  Task tasks[] = {
#define MACRO(x, y, z, i)                                                      \
  [i] = (Task){.function = tensor_sum_func, .argument = &args[i]},
      TENSOR_SUM_IMPLS(MACRO)};
#undef MACRO

  printf("Expected result: %lu\n", expected_result);
  for (size_t i = 0; i < (sizeof(tasks) / sizeof(Task)); i++) {
    double avg_time = task_average_timer(NULLTASK, tasks[i], AVGCNT);
    printf("Average time for (name='%s', %s\e[0m, result=%lf): %lf\n",
           args[i].name,
           (size_t)args[i].result == expected_result ? "\e[32mpass"
                                                     : "\e[31mfail",
           (double)args[i].result, avg_time);
  }

#ifdef ALLOCATE_ARENA
  free(arena);
#endif
}
