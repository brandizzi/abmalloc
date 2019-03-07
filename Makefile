main: main.o person.o linked_list.o
%.o: %.c %.h
clean:
	rm *.o main
