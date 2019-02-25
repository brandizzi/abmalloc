#include "abmalloc.h"
#include <unistd.h>

void *abmalloc(size_t size) {
  return sbrk(size);
}

void abfree(void *ptr) {
}


