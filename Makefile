CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -std=gnu11

OBJS = execute.o myheap.o prompt.o string.o token.o

all: mysh

mysh: mysh.o $(OBJS)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJS)

tokentest: tokenizer_test.o $(OBJS)
	$(CC) $(CFLAGS) -o tokentest tokenizer_test.o $(OBJS)

mysh.o: mysh.c string.h jobs.h execute.h prompt.h
	$(CC) $(CFLAGS) -c mysh.c

tokenizer_test.o: tokenizer_test.c prompt.h token.h
	$(CC) $(CFLAGS) -c tokenizer_test.c

execute.o: execute.c execute.h jobs.h string.h
	$(CC) $(CFLAGS) -c execute.c

myheap.o: myheap.c myheap.h
	$(CC) $(CFLAGS) -c myheap.c

prompt.o: prompt.c prompt.h jobs.h string.h token.h myheap.h
	$(CC) $(CFLAGS) -c prompt.c

string.o: string.c string.h
	$(CC) $(CFLAGS) -c string.c

token.o: token.c token.h string.h myheap.h
	$(CC) $(CFLAGS) -c token.c

clean:
	rm -f mysh tokentest *.o

.PHONY: all clean
