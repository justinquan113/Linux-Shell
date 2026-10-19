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

#test-job: test_files/test_job.c jobs.c
#$(CC) $(CFLAGS)  -I. $^ -o test_job
	
#Need to add test for jobs.c
test: test-string test-heap test-tokenizer test-parser
	./test_string
	./test_heap
	./test_tokenizer
	./test_parser

tokentest: tokenizer_test.o $(OBJS)
	$(CC) $(CFLAGS) -o tokentest tokenizer_test.o $(OBJS)

stringtest: string_test.o $(OBJS)
	$(CC) $(CFLAGS) -o stringtest string_test.o $(OBJS)

jobtest: jobs_test.o $(OBJS)
	$(CC) $(CFLAGS) -o jobtest jobs_test.o $(OBJS)

mysh.o: mysh.c mystring.h jobs.h execute.h prompt.h
	$(CC) $(CFLAGS) -c mysh.c

tokenizer_test.o: tokenizer_test.c prompt.h token.h
	$(CC) $(CFLAGS) -c tokenizer_test.c

string_test.o: mystring.h mystring.c string_test.c
	$(CC) $(CFLAGS) -c string_test.c

jobs_test.o: jobs.h jobs.c jobs_test.c
	$(CC) $(CFLAGS) -c jobs_test.c

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
	rm -f mysh test_string test_heap test_tokenizer test_parser tokentest stringtest jobtest *.o

.PHONY: all clean
