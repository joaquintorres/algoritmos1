/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: formats.h
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/

#ifndef FORMATS__H
#define FORMATS__H

#include <stdio.h>
#include <time.h>

#define ARG_FMT_DAY_MO_YR "DDMMAAAA" 
#define ARG_FMT_YR_DAY "AAAADDD" /*Día (sobre los 365) del año.*/
#define ARG_FMT_YR_MO_DAY "AAAAMMDD"
#define ARG_FMT_YR_MO_DAY_HR_MIN_SEC "AAAAMMDDHHmmSS" /*El día del mes.*/
#define ARG_FMT_YR_DAY_HR_MIN_SEC "AAAADDDHHmmSS" /*El día del año.*/

#define MAX_FORMATS 5

status_t print_date_DDMMAAAA(time_t raw_time);
status_t print_date_AAAADDD(time_t raw_time);
status_t print_date_AAAAMMDD(time_t raw_time);
status_t print_date_AAAAMMDDHHmmSS(time_t raw_time);
status_t print_date_AAAADDDHHmmSS(time_t raw_time);


#endif