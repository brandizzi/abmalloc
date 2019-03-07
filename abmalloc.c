#include "abmalloc.h"
#include <unistd.h>
#include <stdbool.h>

typedef struct Header {
  struct Header *previous;
  size_t size;
  bool available;
} Header;

Header *last = NULL;

void *abmalloc(size_t size) {
  Header *header = sbrk(sizeof(Header) + size);
  header->previous = last;
  header->size = size;
  header->available = false;
  last = header;
  return last + 1;
}

void abfree(void *ptr) {
  Header *header = (Header*) ptr - 1;

  if (header == last) {
    last = header->previous;
    brk(header);
  } else {
    header->available = true;
  }
}
