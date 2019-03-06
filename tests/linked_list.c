#include "linked_list.h"
//#include <stdlib.h>
#include "abmalloc.h"

LinkedList *linked_list_new() {
  LinkedList *linkedList = malloc(sizeof(LinkedList));
  linkedList->data = NULL;
  linkedList->next = NULL;
  return linkedList;
}

void *linked_list_get(LinkedList *linkedList, int index) {
  linkedList = linkedList->next;
  int i = 0;
  while (linkedList) {
    if (index == i) {
      return linkedList->data;
    }
    linkedList = linkedList->next;
    i++;
  }
  return NULL;
}

void linked_list_append(LinkedList *linkedList, void *data) {
  while (linkedList->next) {
    linkedList = linkedList->next;
  }
  linkedList->next = malloc(sizeof(LinkedList));
  linkedList->next->data = data;
  linkedList->next->next = NULL;
}

void *linked_list_remove(LinkedList *linkedList, int index) {
  int i = 0;
  void *data = NULL;
  while (linkedList && linkedList->next) {
    LinkedList* previous = linkedList;
    linkedList = linkedList->next;
    if (i == index) {
      previous->next = linkedList->next;
      data = linkedList->data;
      free(linkedList);
      break;
    }
    i++;
  }
  return data;
}

void linked_list_free(LinkedList *linkedList, DataFreer dataFree) {
  while (linkedList) {
    if (dataFree != NULL) {
      dataFree(linkedList->data);
    }
    LinkedList *next = linkedList->next;
    free(linkedList);
    linkedList = next;
  }
}
