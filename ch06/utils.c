#include "utils.h"

clock_t task_timer(Task task) {
  clock_t start = clock();
  task.function(task.argument);
  return clock() - start;
}

struct __shared_stream stream = {0};

FILE *open_null_stream() {
  if (stream.users) {
    stream.users++;
    return stream.stream;
  }
  stream.stream = fopen("/dev/null", "rw+");
  stream.users++;
  return stream.stream;
}

void close_null_stream() {
  if (stream.users && --stream.users == 0) {
    fclose(stream.stream);
    stream.stream = NULL;
  }
}

double task_average_timer(Task init, Task task, size_t avgcnt) {
  double total = 0.0;
  debug("Average timer: %lu rounds\n", avgcnt);
  for (size_t cnt = 1; cnt <= avgcnt; cnt++) {
    debug("> Round: %lu/%lu\n", cnt, avgcnt);
    init.function(init.argument);
    double lapse = task_timer(task);
    debug("  > Took: %lf\n", lapse);
    total += lapse;
  }
  double average = total / avgcnt;
  debug("> Stats[%lfms]: %lf/%lu\n", average / 1000, total, avgcnt);
  return average;
}
