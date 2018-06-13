/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: records.h
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#ifndef RECORDS__H
#define RECORDS__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_FIELDS 3
#define MIN_FIELDS 3
/*PROTOTIPOS*/
status_t make_record_from_string_array(record_t * record, char ** string_array);
status_t read_record_from_CSV_file(record_t * record, FILE * file, char field_del, bool_t * eof);
status_t export_record_to_CSV_file(record_t record,FILE * target_file,char field_del);

#endif