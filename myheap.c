#include "myheap.h"

#define HEAP_SIZE 10000     /* adjust as necessary */

static char heap[HEAP_SIZE];
static char *freep = heap;


char *alloc(unsigned int size)
{
  if (size == 0 || size > HEAP_SIZE) {
      return 0;
  } else if (freep + size > heap + HEAP_SIZE) {
      return 0;
  } else {
  char *next_available = freep;
  freep += size;
  return next_available;
  }
}

void free_all()
{
  freep = heap;
}
