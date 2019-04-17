#include "abmalloc.h"
#include <unistd.h>
#include <stdbool.h>

typedef struct Header {
  struct Header *previous;
  size_t size;
  bool available;
} Header;

Header *last = NULL;

Header *header_new(Header *previous, size_t size, bool available);

void *abmalloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  Header *header = last;
  while (header != NULL) {
    if (header->available && (header->size >= size)) {
      header->available = false;
      return header + 1;
    }
    header = header->previous;
  }
  last = header_new(last, size, false);
  return last + 1;
}

void abfree(void *ptr) {
  if (ptr == NULL) {
    return;
  }
  Header *header = (Header*) ptr - 1;

  if (header == last) {
    while ((header->previous != NULL) && header->previous->available) {
      header = header->previous;
    }
    last = header->previous;
    brk(header);
  } else {
    header->available = true;
  }
}

Header *header_new(Header *previous, size_t size, bool available) {
  Header *header = sbrk(sizeof(Header) + size);
  header->previous = previous;
  header->size = size;
  header->available = false;
  return header;
}
