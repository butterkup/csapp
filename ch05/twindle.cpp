struct hey {
  int value;
  void swap(hey & __restrict o) {
    value = o.value + value;
    o.value = value - o.value;
    value = value - o.value;
  }
};

hey h1, h3;
hey &h2 = h1;
int main() {
  h1.swap(h2);
  return h2.value;
}
