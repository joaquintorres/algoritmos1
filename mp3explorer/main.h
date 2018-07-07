/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.h
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/
#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"

/*ARGUMENTOS*/
#define MIN_NUMBER_OF_ARGS 8

#define CMD_ARG_FORMAT_TOKEN_POSITION 1
#define CMD_ARG_FORMAT_TOKEN_VALUE 2
#define CMD_ARG_FORMAT_FLAG "-fmt"

#define CMD_ARG_SORT_CRITERION_TOKEN_POSITION 3
#define CMD_ARG_SORT_CRITERION_TOKEN_VALUE 4
#define CMD_ARG_SORT_CRITERION_FLAG "-sort"

#define CMD_ARG_OUTPUT_TOKEN_POSITION 5
#define CMD_ARG_OUTPUT_TOKEN_VALUE 6
#define CMD_ARG_OUTPUT_FLAG "-out"
/*FORMATOS DE SALIDA*/
#define MAX_FORMATS 2

#define ARG_FMT_CSV "csv"
#define ARG_FMT_XML "xml"

/*CRITERIOS DE ORDENAMIENTO*/
#define MAX_SORT_CRITERIA 3

#define CMD_ARG_SORT_BY_NAME "name"
#define CMD_ARG_SORT_BY_ARTIST "artist"
#define CMD_ARG_SORT_BY_GENRE "genre"

typedef struct {
	format_t format;
	sort_t sort;
	char * output_filename;
} config_t;

/*PROTOTIPOS*/
status_t validate_arguments(size_t argc, char * argv[], config_t * config, char ***input_files, size_t * len);
#endif