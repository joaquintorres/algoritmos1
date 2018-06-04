CFLAGS=-ansi -pedantic -Wall
CC=gcc
all: sysdate
sysdate: main.o formats.o sysdate.o
	$(CC) $(CFLAGS) -o sysdate main.o formats.o sysdate.o
main.o: main.c types.h formats.h
	$(CC) $(CFLAGS) -o main.o main.c 
formats.o: formats.c types.h formats.h
	$(CC) $(CFLAGS) -o formats.o formats.c 
sysdate.o: sysdate.c sysdate.h types.h formats.h
	$(CC) $(CFLAGS) -o sysdate.o sysdate.c
clean:
	rm *.o