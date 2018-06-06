/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: types.h
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/

#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

typedef struct {
	size_t id;
	char * barcode; /*Lo dejo como arreglo no estático por coherencia con los argumentos de strdupl, un código de barras puede*/
	char * description; /*expresarse como un arreglo estático char barcode[13+1]*/
} record_t;

#endif