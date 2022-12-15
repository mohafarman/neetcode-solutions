CC = gcc
CFLAGS = -Wall -g

linked_list2: linked_list2.o
	@$(CC) $(CFLAGS) -o $@.o $@.c
	@./$@.o

.PHONY: clean
clean:
	rm -f linked_list2.o
