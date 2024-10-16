CC=clang -w -O0

all: 07-main 01 link 04-main 03-main 02-main.s 05-main 06-main

link: link.c link.s
	$(CC) -o $@ $^

01: 01.c 01-main.c

04-main: 04-main.c
	$(CC) -S $^
	$(CC) -o $@ $^

03-main: 03-main.c
	$(CC) -S $^
	$(CC) -o $@ $^

02-main.s: 02-main.c
	$(CC) -S $^

05-main: 05-main.c 
	$(CC) -S $^
	$(CC) -o $@ $^

07-main: 07-main.c 
	$(CC) -S $^
	$(CC) -o $@ $^

06-main: 06-main.c
	$(CC) -S $^
	$(CC) -o $@ $^

.PHONY+=clean
clean:
	rm -fv 06-main.s 06-main 01 05-main 05-main.s\
		04-main 04-main.s 02-main.s 03-main 03-main.s\
		07-main 07-main.s link

