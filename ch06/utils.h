#ifndef CSAPP_CH06_UTILS_H
#define CSAPP_CH06_UTILS_H

#include <stddef.h>
#include <stdio.h>
#include <time.h>

#ifdef ndebug
#define debug(...)
#else
#define debug(...) printf("DEBUG: " __VA_ARGS__)
#endif

typedef struct task {
  void (*function)(void *);
  void *argument;
} Task;

static void task___noop(void *) {}

#define NULLTASK (Task){.function=task___noop, .argument=NULL}

clock_t task_timer(Task task);
double task_average_timer(Task init, Task task, size_t avgcnt);

struct __shared_stream {
  size_t users;
  FILE *stream;
};

// Flush content to /dev/null in unix and null for windows
extern struct __shared_stream stream;

FILE *open_null_stream();
void close_null_stream();

#endif
