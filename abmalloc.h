#ifndef _ABMALLOC_H
# define _ABMALLOC_H

#include <stddef.h>

void *abmalloc(size_t size);
void abfree(void *ptr);

#define malloc abmalloc
#define free abfree

#define NULL ((void *)0)

#endif // _ABMALLOC_H
