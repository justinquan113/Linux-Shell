CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -std=gnu11

OBJS = execute.o myheap.o prompt.o string.o token.o jobs.o

all: mysh

mysh: mysh.o $(OBJS)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJS)

test-tokenizer: test_files/test_tokenizer.c token.c string.c myheap.c
	$(CC) $(CFLAGS)  -I. $^ -o test_tokenizer

test-string: test_files/test_string.c string.c
	$(CC) $(CFLAGS)  -I. $^ -o test_string

test-heap: test_files/test_heap.c myheap.c
	$(CC) $(CFLAGS)  -I. $^ -o test_heap

#test-job: test_files/test_job.c jobs.c
#$(CC) $(CFLAGS)  -I. $^ -o test_job
	
#Need to add test for jobs.c
test: test-string test-heap test-tokenizer
	./test_string
	./test_heap
	./test_tokenizer

tokentest: tokenizer_test.o $(OBJS)
	$(CC) $(CFLAGS) -o tokentest tokenizer_test.o $(OBJS)

stringtest: string_test.o $(OBJS)
	$(CC) $(CFLAGS) -o stringtest string_test.o $(OBJS)

jobtest: jobs_test.o $(OBJS)
	$(CC) $(CFLAGS) -o jobtest jobs_test.o $(OBJS)

mysh.o: mysh.c string.h jobs.h execute.h prompt.h
	$(CC) $(CFLAGS) -c mysh.c

tokenizer_test.o: tokenizer_test.c prompt.h token.h
	$(CC) $(CFLAGS) -c tokenizer_test.c

string_test.o: string.h string.c string_test.c
	$(CC) $(CFLAGS) -c string_test.c

jobs_test.o: jobs.h jobs.c jobs_test.c
	$(CC) $(CFLAGS) -c jobs_test.c

jobs.o: jobs.c jobs.h string.h token.h prompt.h
	$(CC) $(CFLAGS) -c jobs.c

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
	rm -f mysh test_string test_heap test_tokenizer tokentest stringtest jobtest *.o

.PHONY: all clean
