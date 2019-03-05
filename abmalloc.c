#include "abmalloc.h"
#include <unistd.h>

typedef struct Header {
  struct Header *previous;
} Header;

Header *last = NULL;

void *abmalloc(size_t size) {
  last = sbrk(sizeof(Header) + size);
  return last + 1;
}

void abfree(void *ptr) {
  Header *header = (Header*) ptr - 1;

  if (header == last)
    brk(header);
}
