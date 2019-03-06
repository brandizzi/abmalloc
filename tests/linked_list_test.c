#include "linked_list.h"

#include "CuTest.h"

void testLinkedListAppend(CuTest *tc) {
  LinkedList *list = linked_list_new();
  linked_list_append(list, "test");
  char *name = linked_list_get(list, 0);
  CuAssertStrEquals(tc, name, "test");
}

void testLinkedListRemove(CuTest *tc) {
  LinkedList *list = linked_list_new();
  linked_list_append(list, "test0");
  linked_list_append(list, "test1");
  linked_list_remove(list, 0);
  char *name = linked_list_get(list, 0);
  CuAssertStrEquals(tc, name, "test1");
}

void testLinkedListRemoveLast(CuTest *tc) {
  LinkedList *list = linked_list_new();
  linked_list_append(list, "test0");
  linked_list_append(list, "test1");
  linked_list_remove(list, 1);
  char *name = linked_list_get(list, 0);
  CuAssertStrEquals(tc, "test0", name);
  name = linked_list_get(list, 1);
  CuAssertPtrEquals(tc, NULL, name);
}

void testLinkedListRemoveInexistent(CuTest *tc) {
  LinkedList *list = linked_list_new();
  linked_list_append(list, "test0");
  linked_list_append(list, "test1");
  linked_list_remove(list, 2);
  char *name = linked_list_get(list, 0);
  CuAssertStrEquals(tc, "test0", name);
  name = linked_list_get(list, 1);
  CuAssertPtrEquals(tc, "test1", name);
}

void testLinkedListAppendAfterRemove(CuTest *tc) {
  LinkedList *list = linked_list_new();
  linked_list_append(list, "test0");
  linked_list_append(list, "test1");
  linked_list_remove(list, 0);
  linked_list_append(list, "test2");
  CuAssertStrEquals(tc, linked_list_get(list, 0), "test1");
  CuAssertStrEquals(tc, linked_list_get(list, 1), "test2");
}

CuSuite* LinkedListGetSuite() {
  static CuSuite suite;
  CuSuiteInit(&suite);
  SUITE_ADD_TEST(&suite, testLinkedListAppend);
  SUITE_ADD_TEST(&suite, testLinkedListRemove);
  SUITE_ADD_TEST(&suite, testLinkedListRemoveLast);
  SUITE_ADD_TEST(&suite, testLinkedListRemoveInexistent);
  SUITE_ADD_TEST(&suite, testLinkedListAppendAfterRemove);
  return &suite;
}
