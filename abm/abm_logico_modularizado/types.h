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

#define FIELD_POSITION_FOR_ID 0
#define FIELD_POSITION_FOR_BARCODE 1
#define FIELD_POSITION_FOR_DESCRIPTION 2

#define EAN_BARCODE_LEN 13

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INVALID_KEY,
	ERROR_DUPLICATED_KEY,
	ERROR_INVALID_BARCODE,
	ERROR_NONEXISTENT_RECORD,
	ERROR_INVENTORY_FILE,
	ERROR_ADDITIONS_FILE,
	ERROR_NUMBER_OF_FIELDS,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

typedef struct {
	size_t id;
	char barcode[EAN_BARCODE_LEN + 1];
	char * description; 
} record_t;

#endif