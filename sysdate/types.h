/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: types.h
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>
#include <time.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_NUMBER_OF_ARGS,
	ERROR_INVALID_ARG,
	ERROR_INVALID_FLAG,
	ERROR_CLOCK
} status_t;

typedef enum {
	SERIOUSNESS_TRIVIAL,
	SERIOUSNESS_WARNING,
	SERIOUSNESS_ERROR,
	SERIOUSNESS_FATAL_ERROR
} error_seriousness_t;

typedef enum{
	FMT_DAY_MO_YR,
	FMT_YR_DAY,
	FMT_YR_MO_DAY,
	FMT_YR_MO_DAY_HR_MIN_SEC,
	FMT_YR_DAY_HR_MIN_SEC
} format_t;

typedef struct {
	status_t id;
	char * message;
} error_t;

typedef struct {
	error_seriousness_t id;
	char * message;
} seriousness_t;

typedef struct {
	format_t id;
	char * argument;
} arg_format_t;

#endif