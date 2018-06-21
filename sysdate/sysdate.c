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

typedef status_t (*printer_t)(time_t raw_time);

printer_t print_format[MAX_FORMATS]={
	print_date_DDMMAAAA,
	print_date_AAAADDD,
	print_date_AAAAMMDD,
	print_date_AAAAMMDDHHmmSS,
	print_date_AAAADDDHHmmSS
};

status_t sysdate(format_t format)
{
	status_t st;
	time_t raw_time;

	if ((raw_time = time(NULL)) == -1)
		return ERROR_CLOCK;
	
	if ((st = print_format[format](raw_time)) != OK)
		return st;

	return OK;
}