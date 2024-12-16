
void twindle1(long *restrict xp, long *restrict yp) {
  *xp += *yp;
  *xp += *yp;
}

void twindle2(long *restrict xp, long *restrict yp) { *xp += 2 * *yp; }

void swap(long *restrict a, long *b) {
  *a = *a + *b; // a+b
  *b = *a - *b; // b=(a+b)-b=a
  *a = *a - *b; // a=(a+b)-a=b
}

long f() { return 50; }

long summer() { return f() + f() + f() + f(); }

long by4() { return f() * 4; }

const char *value = "Simon", *name = "Nganga";

int main() { return summer() + by4(); }
