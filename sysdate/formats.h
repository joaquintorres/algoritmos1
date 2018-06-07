/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
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

#define FMT_DAY_MO_YR "DDMMAAAA" 
#define FMT_YR_DAY "AAAADDD" /*Día (sobre los 365) del año.*/
#define FMT_YR_MO_DAY "AAAAMMDD"
#define FMT_YR_MO_DAY_HR_MIN_SEC "AAAAMMDDHHmmSS" /*El día del mes.*/
#define FMT_YR_DAY_HR_MIN_SEC "AAAADDDHHmmSS" /*El día del año.*/

status_t print_as_day_month_year(struct tm * time);
status_t print_as_year_day(struct tm * time);
status_t print_as_year_month_day(struct tm * time);
status_t print_as_year_month_day_hours_minutes_seconds(struct tm * time);
status_t print_as_yearday_hours_minutes_seconds(struct tm * time);


#endif