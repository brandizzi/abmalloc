main: main.o person.o linked_list.o
%.o: %.c %.h
clean:
	make -C tests clean
	rm *.o main
test:
	make -C tests test
