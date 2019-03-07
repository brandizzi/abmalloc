#ifndef _LINKED_LIST_H
# define _LINKED_LIST_H

typedef struct LinkedList {
  void *data;
  struct LinkedList *next;
} LinkedList;

typedef void (*DataFreer)(void *);

LinkedList *linked_list_new();
void *linked_list_get(LinkedList *linkedList, int index);
void linked_list_append(LinkedList *linkedList, void *data);
void *linked_list_remove(LinkedList *linkedList, int index);
void linked_list_free(LinkedList *linkedList, DataFreer dataFree);

#endif // _LINKED_LIST_H
