/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: date.c
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "formats.h"
#include "io.h"

status_t print_date_DDMMAAAA(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%02d %02d %04d\n", time -> tm_mday, (time -> tm_mon) +1, (time ->tm_year) + 1900);
	return OK;
}

status_t print_date_AAAADDD(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%04d %02d\n", (time -> tm_year) + 1900, (time -> tm_yday) + 1);
	return OK;
}

status_t print_date_AAAAMMDD(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%04d %02d %02d\n", (time -> tm_year) + 1900, (time -> tm_mon) + 1, time -> tm_mday);
	return OK;
}

status_t print_date_AAAAMMDDHHmmSS(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%04d %02d %02d %02d:%02d:%02d\n", (time -> tm_year) + 1900, (time -> tm_mon) + 1, time -> tm_mday, time -> tm_hour, time -> tm_min, time -> tm_sec);
	return OK;
}

status_t print_date_AAAADDDHHmmSS(struct tm * time)
{
	if (time == NULL)
		return ERROR_NULL_POINTER;
	printf("%04d %02d %02d:%02d:%02d\n", (time -> tm_year) + 1900, (time -> tm_yday) + 1, time -> tm_hour, time -> tm_min, time -> tm_sec);
	return OK;
}