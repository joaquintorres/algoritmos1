/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "formats.h"
#include "sysdate.h"
#include "io.h"


/*PROTOTIPOS*/
status_t validate_arguments(size_t argc, char * argv[], char ** format);
/************/

int main(int argc, char * argv[])
{
	char * format;
	status_t st;

	if ((st = validate_arguments(argc,argv,&format)) != OK)
		return st;
	printf("%s\n", format);
	if ((st = sysdate(format)) != OK)
		return st;
	show_error_message(SERIOUSNESS_WARNING,ERROR_INVALID_ARG);
	return OK;
}

status_t validate_arguments(size_t argc, char * argv[], char ** format)
{
	char * arg_value_fmt;
	arg_value_fmt = argv[CMD_ARG_FORMAT_TOKEN_VALUE];
	if (argv == NULL || format == NULL)
	{
		show_error_message(SERIOUSNESS_FATAL_ERROR,ERROR_NULL_POINTER);
		return ERROR_NULL_POINTER;
	}
	if (argc < MIN_NUMBER_OF_ARGS || argc > MAX_NUMBER_OF_ARGS)
	{
		show_error_message(SERIOUSNESS_WARNING, ERROR_INVALID_NUMBER_OF_ARGS);
		return ERROR_INVALID_NUMBER_OF_ARGS;
	}
	if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_POSITION], CMD_ARG_FORMAT_FLAG))
	{
		show_error_message(SERIOUSNESS_WARNING, ERROR_INVALID_FLAG);
		return ERROR_INVALID_FLAG;
	}
	if (strcmp(arg_value_fmt, FMT_YR_DAY) && strcmp(arg_value_fmt, FMT_DAY_MO_YR) && strcmp(arg_value_fmt, FMT_YR_MO_DAY) && strcmp(arg_value_fmt, FMT_YR_DAY_HR_MIN_SEC) && strcmp(arg_value_fmt, FMT_YR_MO_DAY_HR_MIN_SEC))
	{
		show_error_message(SERIOUSNESS_WARNING, ERROR_INVALID_ARG);
		return ERROR_INVALID_ARG;	
	}
	*format = argv[CMD_ARG_FORMAT_TOKEN_VALUE];
	return OK;
}