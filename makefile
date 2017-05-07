CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra -Werror -c

all: solution

debug: CFLAGS += -g
debug: solution-dbg solution

solution-dbg: solution.o tree.o list.o
	$(CC) -o solution.dbg solution.o tree.o list.o

solution: solution.o tree.o list.o
	$(CC) -o solution solution.o tree.o list.o
list.o: list.c list.h
	$(CC) $(CFLAGS) list.c
tree.o: tree.c tree.h list.h
	$(CC) $(CFLAGS) tree.c
solution.o: solution.c tree.h list.h
	$(CC) $(CFLAGS) solution.c
.c.o:
	$(CC) $(CFLAGS) $<

clean:
	rm solution solution.dbg *.o

.PHONY: clean
