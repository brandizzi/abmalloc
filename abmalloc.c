#include "abmalloc.h"
#include <unistd.h>
#include <stdbool.h>

#define _ABMALLOC_ALIGNMENT_SIZE 8

typedef struct Header {
  struct Header *previous, *next;
  size_t size;
  bool available;
} Header;

Header *first = NULL;
Header *last = NULL;

Header *header_new(Header *previous, size_t size, bool available);
void header_init(Header *header, size_t size, bool available);
void header_plug(Header *header, Header *previous, Header *next);
void *header_user_area(Header *header);
void *header_address_after_block(Header *header);
bool header_previous_available(Header* header);
bool header_next_available(Header* header);
Header *header_split(Header *header, size_t size);
Header *header_merge(Header *header);

void *abmalloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  size_t rest = size % _ABMALLOC_ALIGNMENT_SIZE;
  if (rest != 0) {
    size = size - rest + _ABMALLOC_ALIGNMENT_SIZE;
  }
  if (first == NULL) {
     first = last = header_new(NULL, size, false);
     return header_user_area(first);
  }
  Header *header = first;
  while (header != NULL) {
    if (header->available && (header->size >= size)) {
      header = header_split(header, size);
      header->available = false;
      return header_user_area(header);
    }
    header = header->next;
  }
  last = header_new(last, size, false);
  return header_user_area(last);
}

void abfree(void *ptr) {
  if (ptr == NULL) {
    return;
  }
  Header *header = (Header*) ptr - 1;

  header = header_merge(header);

  if (header == last) {
    while (header_previous_available(header)) {
      header = header->previous;
    }
    last = header->previous;
    if (last != NULL) {
      last->next = NULL;
    } else {
      first = NULL;
    }
    brk(header);
  } else {
    header->available = true;
  }
}

Header *header_new(Header *previous, size_t size, bool available) {
  Header *header = sbrk(sizeof(Header) + size);
  header_init(header, size, available);
  header_plug(header, previous, NULL);
  return header;
}

void header_init( Header *header, size_t size, bool available) {
  header->size = size;
  header->available = available;
}

void header_plug(Header *header, Header *previous, Header *next) {
  header->previous = previous;
  if (previous != NULL) {
    previous->next = header;
  }
  header->next = next;
  if (next != NULL) {
    next->previous = header;
  }
}

void *header_user_area(Header *header) {
  return header + 1;
}

void *header_address_after_block(Header *header) {
  return header_user_area(header) + header->size;
}

bool header_previous_available(Header *header) {
  return (header->previous != NULL) && header->previous->available;
}

bool header_next_available(Header *header) {
  return (header->next != NULL) && header->next->available;
}

Header *header_merge(Header *header) {
  Header *first_available = header;
  Header *last_available = header;

  if (header_previous_available(header)) {
    first_available = header->previous;
  }
  if (header_next_available(header)) {
    last_available = header->next;
  }

  if ((first_available == header) && (last_available == header)) {
    return header;
  }

  void *end = header_address_after_block(last_available);
  size_t size = end - header_user_area(first_available);
  header_init(first_available, size, true);

  Header *previous = first_available->previous;
  Header *next = last_available->next;
  header_plug(first_available, previous, next);

  if (last_available == last) {
    last = first_available;
  }

  return first_available;
}

Header *header_split(Header *header, size_t size) {
  size_t original_size = header->size;
  if (original_size > size + sizeof(Header)) {
    header->size = original_size - size - sizeof(Header);
    Header *new_header = header_address_after_block(header);
    header_init(new_header, size, true);
    header_plug(new_header, header, header->next);
    if (header == last) {
      last = new_header;
    }
    return new_header;
  } else {
    return header;
  }
}
