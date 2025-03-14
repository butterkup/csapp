#include <iostream>

typedef unsigned long ulong;
template <typename T> T add(T, T);

template <> ulong add<ulong>(ulong, ulong);
template <> int add<int>(int, int);

int main() {
  unsigned long a = 100;
  int b = 200;
  std::cout << add(a, a) << '\n' << add(b, b) << '\n';
}
