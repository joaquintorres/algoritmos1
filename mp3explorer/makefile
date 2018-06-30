############################################################################
#	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
#	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
#	Alumno: Joaquín Torres
#	Correo Electrónico: joaquintorres1997@gmail.com
#	Archivo: makefile
#	Descripción: Programa que ordena un número arbitrario de archivos MP3
#	por un criterio especificado por el usuario y los exporta ordenados en un 
#	formato también determinado por el usuario.
#############################################################################	
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