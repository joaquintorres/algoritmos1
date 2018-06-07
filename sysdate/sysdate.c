/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
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

status_t sysdate(char * format)
{
	time_t raw_time;
	struct tm * calendar_time;
	status_t st;
	if (format == NULL)
		return ERROR_NULL_POINTER;
	if ((raw_time = time(NULL)) == -1)
		return ERROR_CLOCK;
	if ((calendar_time = localtime(&raw_time)) == NULL)
		return ERROR_NULL_POINTER;
	
	if (!strcmp(format,FMT_DAY_MO_YR))
	{
		if ((st = print_as_day_month_year(calendar_time)) != OK)
			return st;
		return OK;
	}

	if (!strcmp(format,FMT_YR_DAY))
	{
		if ((st = print_as_year_day(calendar_time)) != OK)
			return st;
		return OK;
	}
	
	if (!strcmp(format,FMT_YR_MO_DAY))
	{
		if ((st = print_as_year_month_day(calendar_time)) != OK)
			return st;
		return OK;
	}

	if (!strcmp(format,FMT_YR_MO_DAY_HR_MIN_SEC))
	{
		if ((st = print_as_year_month_day_hours_minutes_seconds(calendar_time)) != OK)
			return st;
		return OK;
	}

	if (!strcmp(format,FMT_YR_DAY_HR_MIN_SEC))
	{
		if ((st = print_as_yearday_hours_minutes_seconds(calendar_time)) != OK)
			return st;
		return OK;
	}
	return OK;
}