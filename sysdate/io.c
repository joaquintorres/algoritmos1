/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
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

void show_error_message(error_seriousness_t seriousness, status_t status)
{
	char * error_messages[MAX_ERRORS];
	char * seriousness_messages[MAX_SERIOUSNESS];

	seriousness_messages[SERIOUSNESS_TRIVIAL] = ERR_SERIOUSNESS_TRIVIAL_MSG;
	seriousness_messages[SERIOUSNESS_WARNING] = ERR_SERIOUSNESS_WARNING_MSG;
	seriousness_messages[SERIOUSNESS_ERROR] = ERR_SERIOUSNESS_ERROR_MSG;
	seriousness_messages[SERIOUSNESS_FATAL_ERROR] = ERR_SERIOUSNESS_FATAL_ERROR_MSG;

	error_messages[OK] = ERR_MSG_OK;
	error_messages[ERROR_NULL_POINTER] = ERR_MSG_NULL_POINTER;
	error_messages[ERROR_INVALID_NUMBER_OF_ARGS] = ERR_MSG_NUMBER_OF_ARGS;
	error_messages[ERROR_INVALID_ARG] = ERR_MSG_FLAG;
	error_messages[ERROR_INVALID_FLAG] = ERR_MSG_INVALID_ARGUMENT;

	switch (seriousness) 
	{
		case SERIOUSNESS_TRIVIAL:
			break;
		case SERIOUSNESS_WARNING:
			fprintf(stderr, "%s", seriousness_messages[SERIOUSNESS_WARNING]);
			break;
		case SERIOUSNESS_ERROR:
			fprintf(stderr, "%s", seriousness_messages[SERIOUSNESS_ERROR]);
			break;
		case SERIOUSNESS_FATAL_ERROR:
			fprintf(stderr, "%s", seriousness_messages[SERIOUSNESS_FATAL_ERROR]);
			break;
		default:
			break;
	}

	switch (status)
	{
		case OK:
			break;
		case ERROR_NULL_POINTER:
			fprintf(stderr, "%s\n", error_messages[ERROR_NULL_POINTER]);
			break;
		case ERROR_INVALID_NUMBER_OF_ARGS:
			fprintf(stderr, "%s\n", error_messages[ERROR_INVALID_NUMBER_OF_ARGS]);
			fprintf(stderr, "%s\n", USR_MSG_USAGE);
			break;
		case ERROR_INVALID_FLAG:
			fprintf(stderr, "%s\n", error_messages[ERROR_INVALID_FLAG]);
			fprintf(stderr, "%s\n", USR_MSG_USAGE);
			break;
		case ERROR_INVALID_ARG:
			fprintf(stderr, "%s\n", error_messages[ERROR_INVALID_ARG]);
			fprintf(stderr, "%s\n %s\n %s\n %s\n %s\n %s\n",USR_MSG_USAGE_FMT, FMT_YR_DAY, FMT_DAY_MO_YR, FMT_YR_MO_DAY, FMT_YR_DAY_HR_MIN_SEC, FMT_YR_MO_DAY_HR_MIN_SEC);
			break;
		default:
			fprintf(stderr, "%s\n", ERR_MSG_UNKNOWN);
	}

}