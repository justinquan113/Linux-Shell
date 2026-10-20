CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -std=gnu11 -I.

OBJS = execute.o myheap.o prompt.o mystring.o token.o jobs.o parser.o

TESTS = test_string test_heap test_tokenizer test_parser test_job test_execution test_run_job

all: mysh

mysh: mysh.o $(OBJS)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJS)

test: $(TESTS)
	./test_string
	./test_heap
	./test_tokenizer
	./test_parser
	./test_job
	./test_execution
	./test_run_job

test_string: test_string.o mystring.o
	$(CC) $(CFLAGS) -o test_string $^

test_heap: test_heap.o myheap.o
	$(CC) $(CFLAGS) -o test_heap $^

test_tokenizer: test_tokenizer.o token.o mystring.o myheap.o
	$(CC) $(CFLAGS) -o test_tokenizer $^

test_parser: test_parser.o jobs.o mystring.o parser.o prompt.o token.o myheap.o execute.o
	$(CC) $(CFLAGS) -o test_parser $^

test_job: test_job.o jobs.o mystring.o parser.o prompt.o token.o execute.o myheap.o
	$(CC) $(CFLAGS) -o test_job $^

test_execution: test_execution.o execute.o mystring.o myheap.o
	$(CC) $(CFLAGS) -o test_execution $^

test_run_job: test_run_job.o jobs.o mystring.o parser.o prompt.o token.o myheap.o execute.o
	$(CC) $(CFLAGS) -o test_run_job $^

test_string.o: test_files/test_string.c mystring.h
	$(CC) $(CFLAGS) -c test_files/test_string.c

test_heap.o: test_files/test_heap.c myheap.h
	$(CC) $(CFLAGS) -c test_files/test_heap.c

test_tokenizer.o: test_files/test_tokenizer.c mystring.h token.h myheap.h
	$(CC) $(CFLAGS) -c test_files/test_tokenizer.c

test_parser.o: test_files/test_parser.c mystring.h jobs.h parser.h
	$(CC) $(CFLAGS) -c test_files/test_parser.c

test_job.o: test_files/test_job.c jobs.h
	$(CC) $(CFLAGS) -c test_files/test_job.c

test_execution.o: test_files/test_execution.c execute.h mystring.h myheap.h
	$(CC) $(CFLAGS) -c test_files/test_execution.c

test_run_job.o: test_files/test_run_job.c mystring.h jobs.h
	$(CC) $(CFLAGS) -c test_files/test_run_job.c

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

test-string: test_string
test-heap: test_heap
test-tokenizer: test_tokenizer
test-parser: test_parser
test-job: test_job
test-execution: test_execution
test-run_job: test_run_job

clean:
	rm -rf *.dSYM
	rm -f mysh $(TESTS) *.o *.exe

.PHONY: all clean test \
	test-string test-heap test-tokenizer test-parser test-job test-execution test-run_job
