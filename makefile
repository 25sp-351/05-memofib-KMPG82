all: main

OBJS = main.o
CC = clang
CFLAGS = -g -Wall

main: $(OBJS)
	clang -o main $(CFLAGS) $(OBJS)

main.o: main.c

clean:
	rm -f main $(OBJS)
