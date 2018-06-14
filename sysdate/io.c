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

error_t error_dictionary[MAX_ERRORS]={
	{OK, ERR_MSG_OK},
	{ERROR_NULL_POINTER, ERR_MSG_NULL_POINTER},
	{ERROR_INVALID_NUMBER_OF_ARGS, ERR_MSG_NUMBER_OF_ARGS},
	{ERROR_INVALID_ARG, ERR_MSG_INVALID_ARGUMENT},
	{ERROR_INVALID_FLAG, ERR_MSG_FLAG}	
};

seriousness_t error_seriousness_dictionary[MAX_SERIOUSNESS]={
	{SERIOUSNESS_TRIVIAL,ERR_SERIOUSNESS_TRIVIAL_MSG},
	{SERIOUSNESS_WARNING, ERR_SERIOUSNESS_WARNING_MSG},
	{SERIOUSNESS_ERROR, ERR_SERIOUSNESS_ERROR_MSG},
	{SERIOUSNESS_FATAL_ERROR, ERR_SERIOUSNESS_FATAL_ERROR_MSG}
};

void print_error_message(error_seriousness_t seriousness, status_t status)
{
	
	size_t i;
	
	if (seriousness != SERIOUSNESS_TRIVIAL)
	{
		for (i = 0; i < MAX_SERIOUSNESS; i++)
		{
			if (seriousness == error_seriousness_dictionary[i].id)
			{
				fprintf(stderr, "%s", error_seriousness_dictionary[i].message);
			}
		}
	} 


	if (status != OK)
	{
		for(i = 0; i < MAX_ERRORS; i++)
		{
			if (status == error_dictionary[i].id)
			{
				fprintf(stderr, "%s\n", error_dictionary[i].message);
			}
		}
	}
}