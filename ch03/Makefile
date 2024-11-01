CC=gcc -g -w -O0

all: 13.1 13-main glob 07-main 01 link 04-main 03-main 02-main.s 05-main 06-main 08-main 09-main 10-main 11-main

hello: hello.s
	$(CC) -o $@ $^

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

09-main: 09-main.c 09.s
	$(CC) -S $^
	$(CC) -o $@ $^

08-main: 08-main.c 08.s
	$(CC) -S $^
	$(CC) -o $@ $^

10-main: 10-main.c 10.s
	$(CC) -S $^
	$(CC) -o $@ $^

11-main: 11-main.c
	$(CC) -o $@ $^

12-main: 12-main.c
	$(CC) -o $@ $^

13-main: 13-main.c 
	$(CC) -o $@ $^
	$(CC) -S $^

13.1: 13.1.s
	$(CC) -o $@ $^

10.1: 10.1.s
	$(CC) -o $@ $^

glob: glob.c 
	$(CC) -S $^
	$(CC) -o $@ $^

.PHONY+=clean
clean:
	rm -fv 06-main.s 06-main 01 05-main 05-main.s\
		04-main 04-main.s 02-main.s 03-main 03-main.s\
		07-main 07-main.s link 08-main 08-main.s hello\
		10-main 10-main.s 09-main 09-main.s glob glob.s\
		10.1 13.1 11-main 12-main 13-main 13-main.s

