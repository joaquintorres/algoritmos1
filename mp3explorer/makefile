CFLAGS=-ansi -pedantic -Wall
CC=gcc
all: mp3explorer
mp3explorer: main.o
	$(CC) $(CFLAGS) -o mp3explorer main.o
main.o: main.c main.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c