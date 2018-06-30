/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: types.h
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/
#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_NUMBER_OF_ARGS,
	ERROR_INVALID_ARG,
	ERROR_INVALID_FLAG,
	ERROR_OUT_OF_BOUNDS,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_MEMORY,
	ERROR_DISK_SPACE
} status_t;

typedef enum {
	FMT_CSV,
	FMT_XML
} format_t;

typedef enum {
	SORT_NAME,
	SORT_ARTIST,
	SORT_GENRE
} sort_t;

typedef enum {
	FALSE,
	TRUE
} bool_t;

#endif