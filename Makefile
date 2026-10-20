CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -std=gnu11

OBJS = execute.o myheap.o prompt.o mystring.o token.o jobs.o parser.o

all: mysh

mysh: mysh.o $(OBJS)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJS)

test-tokenizer: test_files/test_tokenizer.c token.c mystring.c myheap.c
	$(CC) $(CFLAGS)  -I. $^ -o test_tokenizer

test-string: test_files/test_string.c mystring.c
	$(CC) $(CFLAGS)  -I. $^ -o test_string

test-heap: test_files/test_heap.c myheap.c
	$(CC) $(CFLAGS)  -I. $^ -o test_heap

test-parser: test_files/test_parser.c jobs.c mystring.c parser.c prompt.c token.c myheap.c execute.c
	$(CC) $(CFLAGS)  -I. $^ -o test_parser

test-execution: test_files/test_execution.c execute.c mystring.c myheap.c
	$(CC) $(CFLAGS)	-I. $^ -o test_execution

test-job: test_files/test_job.c jobs.c mystring.c parser.c prompt.c token.c execute.c myheap.c
	$(CC) $(CFLAGS)  -I. $^ -o test_job
	
test: test-string test-heap test-tokenizer test-parser test-job test-execution test-run_job

test-run_job: test_files/test_run_job.c jobs.c mystring.c parser.c prompt.c token.c myheap.c execute.c
	$(CC) $(CFLAGS)  -I. $^ -o test_run_job
	
test: test-string test-heap test-tokenizer test-parser test-run_job
	./test_string
	./test_heap
	./test_tokenizer
	./test_parser
	./test_job
	./test_execution
	./test_run_job

mysh.o: mysh.c mystring.h jobs.h execute.h prompt.h
	$(CC) $(CFLAGS) -c mysh.c

jobs.o: jobs.c jobs.h mystring.h token.h prompt.h
	$(CC) $(CFLAGS) -c jobs.c

execute.o: execute.c execute.h jobs.h mystring.h
	$(CC) $(CFLAGS) -c execute.c

myheap.o: myheap.c myheap.h
	$(CC) $(CFLAGS) -c myheap.c

prompt.o: prompt.c prompt.h jobs.h mystring.h token.h myheap.h
	$(CC) $(CFLAGS) -c prompt.c

mystring.o: mystring.c mystring.h
	$(CC) $(CFLAGS) -c mystring.c

token.o: token.c token.h mystring.h myheap.h
	$(CC) $(CFLAGS) -c token.c

parser.o: parser.c parser.h jobs.h mystring.h
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -f mysh test_string test_heap test_tokenizer test_parser test_job test_execution test_run_job test *.o *.exe

.PHONY: all clean test run-job
