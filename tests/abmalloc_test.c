#include "../abmalloc.h"
#include <unistd.h>
#include <string.h>

#include "CuTest.h"

#define PTRSUB(p1,p2) ((long)p1 - (long)p2)

void test_abmalloc(CuTest *tc) {
  void *initial_top = sbrk(0);
  void *ptr = abmalloc(8);
  CuAssertPtrNotNull(tc, ptr);
  CuAssertTrue(tc, PTRSUB(sbrk(0), initial_top) >= 8);
  abfree(ptr);
}

void test_abfree_top(CuTest *tc) {
  void *initial_top = sbrk(0);
  void *ptr = abmalloc(8);
  abfree(ptr);
  CuAssertIntEquals(tc, 0, PTRSUB(sbrk(0), initial_top));
}

void test_abfree_top_twice(CuTest *tc) {
  void *initial_top = sbrk(0);
  void *ptr1 = abmalloc(8);
  void *ptr2 = abmalloc(8);
  abfree(ptr2);
  abfree(ptr1);
  CuAssertIntEquals(tc, 0, PTRSUB(sbrk(0), initial_top));
}

void test_abfree_bottom(CuTest *tc) {
  void *ptr1 = abmalloc(8);
  void *ptr2 = abmalloc(8);
  void *initial_top = sbrk(0);
  abfree(ptr1);
  void *ptr3 = abmalloc(8);
  CuAssertIntEquals(tc, 0, PTRSUB(sbrk(0), initial_top));
  abfree(ptr2);
  abfree(ptr3);
}

void test_abfree_bottom_available_block_smaller_than_size(CuTest *tc) {
  void *ptr1 = abmalloc(8);
  void *ptr2 = abmalloc(8);
  void *initial_top = sbrk(0);
  abfree(ptr1);
  void *ptr3 = abmalloc(16);
  CuAssertTrue(tc, PTRSUB(sbrk(0), initial_top) >= 16);
  abfree(ptr2);
  abfree(ptr3);
}

void test_abmalloc_abfree(CuTest *tc) {
  void *ptr1 = abmalloc(8);
  strncpy(ptr1, "abcd", 4);

  void *ptr2 = abmalloc(8);
  strncpy(ptr2, "efgh", 4);

  abfree(ptr1);

  void *ptr3 = abmalloc(8);
  strncpy(ptr3, "ijkl", 4);

  CuAssertStrEquals(tc, "efgh", ptr2);
  CuAssertStrEquals(tc, "ijkl", ptr3);
}

void test_abmalloc_zero(CuTest *tc) {
  void *ptr = abmalloc(0);
  CuAssertPtrEquals(tc, NULL, ptr);
}

void test_abfree_null(CuTest *tc) {
  abfree(NULL);
}

CuSuite* ABMallocGetSuite() {
  static CuSuite suite;
  CuSuiteInit(&suite);
  SUITE_ADD_TEST(&suite, test_abmalloc);
  SUITE_ADD_TEST(&suite, test_abfree_top);
  SUITE_ADD_TEST(&suite, test_abfree_top_twice);
  SUITE_ADD_TEST(&suite, test_abfree_bottom);
  SUITE_ADD_TEST(&suite, test_abfree_bottom_available_block_smaller_than_size);
  SUITE_ADD_TEST(&suite, test_abmalloc_abfree);
  SUITE_ADD_TEST(&suite, test_abmalloc_zero);
  SUITE_ADD_TEST(&suite, test_abfree_null);
  return &suite;
}
