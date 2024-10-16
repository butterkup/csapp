#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#ifndef THREADS
# define THREADS 10
#endif

#ifndef BOUND
# define BOUND 10000
#endif

std::atomic_int acnt;
int cnt;

void f() {
  for (int n = 0; n < BOUND; ++n) {
    ++acnt;
    ++cnt;
    // Note: for this example, relaxed memory order
    // is sufficient, e.g. acnt.fetch_add(1, std::memory_order_relaxed);
  }
}

int main() {
  {
    std::vector<std::jthread> pool;
    for (int n = 0; n < THREADS; ++n)
      pool.emplace_back(f);
  }

  std::cout << "The atomic counter is " << acnt << ' ' 
            << std::boolalpha << (acnt == THREADS * BOUND) << '\n'
            << "The non-atomic counter is " << cnt <<' '
            << (cnt == THREADS * BOUND) << '\n';
}
