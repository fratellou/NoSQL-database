CFLAGS=-Wall -Wextra -Werror
STRUCT=./structures/
EXIT=$(STRUCT)objects/

all:server client

server: database.o hash.o stack.o array.o list.o tree.o queue.o hash.o double_list.o set.o
	gcc $(CFLAGS) $(EXIT)database.o $(EXIT)hash.o $(EXIT)array.o $(EXIT)tree.o $(EXIT)stack.o $(EXIT)list.o $(EXIT)queue.o $(EXIT)double_list.o $(EXIT)set.o -o server

client: client.o
	gcc $(CFLAGS) $(EXIT)client.o -o dbms

client.o: 
	gcc $(CFLAGS) -c client.c -o $(EXIT)client.o

database.o: 
	gcc $(CFLAGS) -c database.c -o $(EXIT)database.o

hash.o: 
	gcc $(CFLAGS) -c $(STRUCT)hash.c -o $(EXIT)hash.o

stack.o: 
	gcc $(CFLAGS) -c $(STRUCT)stack.c -o $(EXIT)stack.o

list.o: 
	gcc $(CFLAGS) -c $(STRUCT)list.c -o $(EXIT)list.o

double_list.o:
	gcc $(CFLAGS) -c $(STRUCT)double_list.c -o $(EXIT)double_list.o

set.o: 
	gcc $(CFLAGS) -c $(STRUCT)set.c -o $(EXIT)set.o

queue.o: 
	gcc $(CFLAGS) -c $(STRUCT)queue.c -o $(EXIT)queue.o

array.o: 
	gcc $(CFLAGS) -c $(STRUCT)array.c -o $(EXIT)array.o

tree.o:
	gcc $(CFLAGS) -c $(STRUCT)tree.c -o $(EXIT)tree.o

clean: 
	rm -rf $(EXIT)*.o dbms server

rebuild:clean all