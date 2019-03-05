#include "abmalloc.h"
#include <unistd.h>

typedef struct Header {
  struct Header *previous;
} Header;

Header *last = NULL;

void *abmalloc(size_t size) {
  Header *header = sbrk(sizeof(Header) + size);
  header->previous = last;
  last = header;
  return last + 1;
}

void abfree(void *ptr) {
  Header *header = (Header*) ptr - 1;

  if (header == last) {
    last = header->previous;
    brk(header);
  }
}
