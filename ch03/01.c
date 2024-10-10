
long mult2(long, long);
int mult3(int, int);
short mult4(short, short);

void multstore2(long x, long y, long *dest) {
	long t = mult2(x, y);
	*dest = t;
}

void multstore3(int x, int y, int *dest) {
	int t = mult3(x, y);
	*dest = t;
}

void multstore4(short x, short y, short *dest) {
	short t = mult4(x, y);
	*dest = t;
}
