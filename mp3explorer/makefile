CFLAGS=-ansi -pedantic -Wall
CC=gcc
all: mp3explorer
mp3explorer: main.o mp3.o vector.o mp3explorer.o
	$(CC) $(CFLAGS) -o mp3explorer main.o mp3.o vector.o mp3explorer.o
main.o: main.c main.h types.h mp3explorer.h
	$(CC) $(CFLAGS) -o main.o -c main.c
mp3.o: mp3.c mp3.h types.h
	$(CC) $(CFLAGS) -o mp3.o -c mp3.c
vector.o: vector.c vector.h types.h
	$(CC) $(CFLAGS) -o vector.o -c vector.c
mp3explorer.o: mp3explorer.c types.h mp3.h vector.h mp3explorer.h
	$(CC) $(CFLAGS) -o mp3explorer.o -c mp3explorer.c
clean:
	rm *.o