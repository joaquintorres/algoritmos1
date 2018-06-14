/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: sysdate.c
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "types.h"
#include "formats.h"

printer_format_t printer_dictionary[MAX_FORMATS]={
	{FMT_DAY_MO_YR, print_date_DDMMAAAA},
	{FMT_YR_DAY, print_date_AAAADDD},
	{FMT_YR_MO_DAY, print_date_AAAAMMDD},
	{FMT_YR_MO_DAY_HR_MIN_SEC, print_date_AAAAMMDDHHmmSS},
	{FMT_YR_DAY_HR_MIN_SEC, print_date_AAAADDDHHmmSS}
};

status_t sysdate(format_t format)
{
	time_t raw_time;
	struct tm * calendar_time;
	status_t st;
	size_t i;

	if ((raw_time = time(NULL)) == -1)
		return ERROR_CLOCK;
	if ((calendar_time = localtime(&raw_time)) == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < MAX_FORMATS; i++)
	{
		if (format == printer_dictionary[i].id)
		{
			if ((st = printer_dictionary[i].printer(calendar_time)) != OK)
				return st;
			return OK;
		}
	}
	return OK;
}