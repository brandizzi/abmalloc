CFLAGS=-I..
test: abmalloc-test
	./abmalloc-test

# Executable

abmalloc-test: AllTests.o CuTest.o linked_list_test.o linked_list.o abmalloc.o abmalloc_test.o
	cc $(CCFLAGS) -o $@ $^

# Test framework

AllTests.o: AllTests.c CuTest.h linked_list_test.h abmalloc_test.h
	cc $(CCFLAGS) -I.. -c -o $@ $<
CuTest.o: CuTest.c CuTest.h ../abmalloc.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Tests

linked_list_test.o: linked_list_test.c linked_list_test.h linked_list.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

abmalloc_test.o: abmalloc_test.c abmalloc_test.h ../abmalloc.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Tested code

abmalloc.o: ../abmalloc.c ../abmalloc.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

linked_list.o: linked_list.c linked_list.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Cleanup

clean:
	rm *.o
	make -C tests clean
