#include "abmalloc.h"
#include <unistd.h>

void *last = NULL;

void *abmalloc(size_t size) {
  last = sbrk(size);
  return last;
}

void abfree(void *ptr) {
  if (ptr == last)
      brk(ptr);
}


