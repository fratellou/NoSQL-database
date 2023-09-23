CFLAGS=-Wall -Wextra -Werror

all:build

build: database.o hash.o stack.o set.o queue.o hash.o
	gcc $(CFLAGS) database.o hash.o stack.o set.o queue.o -o dbms

database.o: macro.h hash.h hash.c queue.c queue.h set.c set.h stack.h stack.c database.c
	gcc $(CFLAGS) -c database.c

hash.o: macro.h hash.h hash.c
	gcc $(CFLAGS) -c hash.c

stack.o: macro.h stack.h stack.c
	gcc $(CFLAGS) -c stack.c

set.o: macro.h set.h set.c
	gcc $(CFLAGS) -c set.c

queue.o: macro.h queue.h queue.c 
	gcc $(CFLAGS) -c queue.c

clean: 
	rm -rf *.o dbms

rebuild:clean all