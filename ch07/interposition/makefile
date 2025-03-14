CC=gcc
CFLAGS=-Og -g

all: main lmain cmain rmain

# original program to interposition
main: main.o

# for runtime interpositioning
libruntime.so: runtime.c
	$(CC) $(CFLAGS) -shared -fpic -o $@ $^

# runtime interpositioning
rmain: libruntime.so
	echo >$@ $$'#!/bin/env sh\nLD_PRELOAD=./libruntime.so ./main\n'
	chmod u+x $@

# linktime interpositioning
lmain: main.o linktime.o
	$(CC) $(CFLAGS) -Wl,--wrap,malloc -Wl,--wrap,free -o $@ $^

# compiletime interpositioning
cmain: compiletime.c
	$(CC) $(CFLAGS) -DINTERPOSITION -o $@ $^

# cleanup
.PHONY+=clean
clean:
	rm -rfv *.o libruntime.so {r,l,c,}main
