/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: utils.h
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/

#ifndef UTILS__H
#define UTILS__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define INIT_CHOP 20
#define CHOP_SIZE 5


/*PROTOTIPOS*/
status_t read_line_from_file(FILE * file, char del, char ** s, bool_t * eof);
status_t strdupl(const char * s, char ** t);
status_t split(const char * s,char *** fields, char del, size_t * l);
status_t destroy_string_array(char *** p, size_t l);
status_t make_record_from_string_array(record_t * record, char ** string_array);
status_t read_record_from_CSV_file(record_t * record, FILE * file, char field_del, char line_del, bool_t * eof);
status_t export_record_to_CSV_file(record_t record,FILE * target_file,char field_del);


#endif