/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: io.c
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#include <stdio.h>
#include "io.h"
#include "types.h"
#include "formats.h"

char * error_dictionary[MAX_ERRORS]={
	ERR_MSG_OK,
	ERR_MSG_NULL_POINTER,
	ERR_MSG_NUMBER_OF_ARGS,
	ERR_MSG_INVALID_ARGUMENT,
	ERR_MSG_FLAG	
};

char * error_seriousness_dictionary[MAX_SERIOUSNESS]={
	ERR_SERIOUSNESS_TRIVIAL_MSG,
	ERR_SERIOUSNESS_WARNING_MSG,
	ERR_SERIOUSNESS_ERROR_MSG,
	ERR_SERIOUSNESS_FATAL_ERROR_MSG
};

void print_error_message(error_seriousness_t seriousness, status_t status)
{
	if (seriousness != SERIOUSNESS_TRIVIAL)
		fprintf(stderr, "%s", error_seriousness_dictionary[seriousness]);
	if (status != OK)
		fprintf(stderr, "%s\n", error_dictionary[status]);
}