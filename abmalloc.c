#include "abmalloc.h"
#include <unistd.h>
#include <stdbool.h>

typedef struct Header {
  struct Header *previous, *next;
  size_t size;
  bool available;
} Header;

Header *first = NULL;
Header *last = NULL;

Header *header_new(Header *previous, size_t size, bool available);

void *abmalloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  if (first == NULL) {
     first = last = header_new(NULL, size, false);
     return first + 1;
  }
  Header *header = first;
  while (header != NULL) {
    if (header->available && (header->size >= size)) {
      header->available = false;
      return header + 1;
    }
    header = header->next;
  }
  last = header_new(last, size, false);
  last->previous->next = last;
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
    last->next = NULL;
    brk(header);
  } else {
    header->available = true;
  }
}

Header *header_new(Header *previous, size_t size, bool available) {
  Header *header = sbrk(sizeof(Header) + size);
  header->previous = previous;
  header->next = NULL;
  header->size = size;
  header->available = false;
  return header;
}
