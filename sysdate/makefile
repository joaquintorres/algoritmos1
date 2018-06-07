CFLAGS=-ansi -pedantic -Wall
CC=gcc
all: sysdate
sysdate: main.o formats.o io.o sysdate.o
	$(CC) $(CFLAGS) -o sysdate main.o formats.o sysdate.o
main.o: main.c types.h formats.h sysdate.h io.h
	$(CC) $(CFLAGS) -o main.o -c main.c
formats.o: formats.c types.h formats.h
	$(CC) $(CFLAGS) -o formats.o -c formats.c 
sysdate.o: sysdate.c sysdate.h types.h formats.h
	$(CC) $(CFLAGS) -o sysdate.o -c sysdate.c
io.o: io.c io.h types.h formats.h
	$(CC) $(CFLAGS) -o io.o -c io.c
clean:
	rm *.o