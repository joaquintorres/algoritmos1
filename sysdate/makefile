CFLAGS=-ansi -pedantic -Wall
CC=gcc
all: sysdate
sysdate: formats.o sysdate.o
	$(CC) $(CFLAGS) -o sysdate formats.o sysdate.o
formats.o: formats.c types.h formats.h
	$(CC) $(CFLAGS) -o formats.o formats.c 
sysdate.o: sysdate.c main.c sysdate.h types.h formats.h
	$(CC) $(CFLAGS) -o sysdate.o sysdate.c main.c
clean:
	rm *.o