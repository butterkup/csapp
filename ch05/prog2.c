#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef DATA_T
#define DATA_T short
#endif

typedef DATA_T data_t;

void minmax1(data_t *restrict a, data_t *restrict b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] > b[i]) {
      data_t tmp = a[i];
      a[i] = b[i];
      b[i] = tmp;
    }
  }
}

void minmax2(data_t *restrict a, data_t *restrict b, size_t n) {
  for (long i = 0; i < n; i++) {
    data_t min = a[i] < b[i] ? a[i] : b[i];
    data_t max = a[i] > b[i] ? a[i] : b[i];
    a[i] = min;
    b[i] = max;
  }
}

void merge1(const data_t *restrict a, const data_t *restrict b,
            data_t *restrict c, size_t n) {
  size_t ia = 0, ib = 0, ic = 0;
  while (ia < n && ib < n) {
    c[ic] = a[ia] < b[ib] ? a[ia++] : b[ib++];
    /*
    if (a[ia] < b[ib]) {
      c[ic++] = a[ia++];
    } else {
      c[ic++] = b[ib++];
    }
    */
  }
  while (ia < n) {
    c[ic++] = a[ia++];
  }
  while (ib < n) {
    c[ic++] = b[ib++];
  }
}

void merge2(const data_t *restrict a, const data_t *restrict b,
            data_t *restrict c, size_t n) {
  size_t ia = 0, ib = 0, ic = 0;
  while (ia < n && ib < n) {
    const data_t va = a[ia], vb = b[ib];
    int take_a = va < vb;
    c[ic] = take_a ? va : vb;
    ia += take_a;
    ib += (1 - take_a);
    ++ic;
  }
  while (ia < n) {
    c[ic++] = a[ia++];
  }
  while (ib < n) {
    c[ic++] = b[ib++];
  }
}

struct merge_args {
  void (*merge)(const data_t *, const data_t *, data_t *, size_t);
  size_t n;
  data_t *a, *b, *c;
};

struct minmax_args {
  void (*minmax)(data_t *, data_t *, size_t);
  size_t n;
  data_t *a, *b;
};

void minmax_func(void *args) {
  struct minmax_args *mmargs = (struct minmax_args *)args;
  mmargs->minmax(mmargs->a, mmargs->b, mmargs->n);
}

void merge_func(void *args) {
  struct merge_args *margs = (struct merge_args *)args;
  margs->merge(margs->a, margs->b, margs->c, margs->n);
}

void randomize(data_t arr[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    arr[i] = rand();
  }
}

void randomize2(long seed, data_t *restrict arr1, data_t *arr2, size_t n) {
  srand(seed);
  randomize(arr1, n);
  randomize(arr2, n);
}

struct task {
  void (*function)(void *);
  void *argument;
};

clock_t timer(struct task t) {
  clock_t start = clock();
  t.function(t.argument);
  return clock() - start;
}

double average_timer(struct task work, struct task init, size_t n) {
  double lapse = 0;
  for (long i = 0; i < n; i++) {
    init.function(init.argument);
    lapse += timer(work);
  }
  return lapse / n;
}

struct init_args {
  time_t seed;
  data_t *a, *b;
  size_t n;
  int randomized;
};

void init_func(void *arg) {
  struct init_args *args = (struct init_args *)arg;
// Predictable compile time flag only randomizes the data once and the rest will
// be sorted, now it will simply be highly predictable as just noop over 90%
// of the time the CPU will be correct.
#ifdef PREDICTABLE
  if (!args->randomized) {
    randomize2(args->seed, args->a, args->b, args->n);
#ifdef MERGING
    minmax2(args->a, args->b, args->n);
#endif
    args->randomized = 1;
  }
#ifdef MERGING
  else {
    minmax2(args->a, args->b, args->n);
  }
#endif
#else
  randomize2(args->seed, args->a, args->b, args->n);
#ifdef MERGING
  minmax2(args->a, args->b, args->n);
#endif
#endif
}

#ifndef AVGCNT
#define AVGCNT 128
#endif

#ifndef DATALEN
#define DATALEN BUFSIZ
#endif

int main() {
  // Compile time constant; the compiler will not use VLAs for declarations like
  // `data_t a[n];`
  const size_t n = DATALEN;
  // Allocate data_t buffers for our tests
  data_t *a = (data_t *)calloc(sizeof(data_t), n);
  data_t *b = (data_t *)calloc(sizeof(data_t), n);
  // A place to store the average times
  double avg_times[2];
  // Initialize init
  struct init_args initargs = (struct init_args){
      .seed = time(NULL), .a = a, .b = b, .n = n, .randomized = 0};
  struct task init_task =
      (struct task){.function = init_func, .argument = &initargs};
#ifdef MERGING
  data_t *c = (data_t *)calloc(sizeof(data_t), 2 * n);
  struct merge_args mergeargs =
      (struct merge_args){.merge = NULL, .a = a, .b = b, .c = c, .n = n};
  struct task merge_task =
      (struct task){.function = merge_func, .argument = &mergeargs};
  mergeargs.merge = merge1;
  avg_times[0] = average_timer(merge_task, init_task, AVGCNT);
  mergeargs.merge = merge2;
  avg_times[1] = average_timer(merge_task, init_task, AVGCNT);
  printf("merge1=%lf\nmerge2=%lf\n", avg_times[0], avg_times[1]);
  free(c);
#else
  // Setup tasks and args for testing
  // Start out as null, be weary, must be initialized before call
  struct minmax_args minmaxargs =
      (struct minmax_args){.minmax = NULL, .n = n, .a = a, .b = b};
  struct task minmax_task =
      (struct task){.function = minmax_func, .argument = &minmaxargs};
  // Setup (initialize from NULL) and call average timer
  minmaxargs.minmax = minmax1;
  avg_times[0] = average_timer(minmax_task, init_task, AVGCNT);
  minmaxargs.minmax = minmax2;
  avg_times[1] = average_timer(minmax_task, init_task, AVGCNT);
  // Report statistics
  printf("minmax1=%lf\nminmax2=%lf\n", avg_times[0], avg_times[1]);
#endif
  // Free allocated data_t buffers
  free(a);
  free(b);
}
