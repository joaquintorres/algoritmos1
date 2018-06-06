/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: process_update_records.c
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

status_t process_update_records(FILE * old_file,FILE * mod_file, FILE * new_file, char line_del, char field_del)
{
	char * line;
	char * aux_line;
	bool_t eof;
	bool_t aux_eof;
	status_t st;
	record_t old_file_record;
	record_t mod_file_record;

	eof = FALSE;

	aux_eof = FALSE;
	while ((st = read_line_from_file(old_file, line_del, &line, &eof)) == OK && eof == FALSE)
	{
		if ((st = split(line,&old_file_record,field_del)) != OK)
			return st;
		while ((st = read_line_from_file(mod_file, line_del, &aux_line, &aux_eof)) == OK && aux_eof == FALSE)
		{
			if ((st = split(aux_line,&mod_file_record,field_del)) != OK)
				return st;
			if (mod_file_record.id == old_file_record.id)
			{
				old_file_record.barcode = mod_file_record.barcode;
				old_file_record.description = mod_file_record.description;
			}
			if ((st = export_record_to_CSV_file(new_file, old_file_record, field_del, line_del)) != OK)
				return st;
		}
		if (fseek(mod_file, 0L, SEEK_SET))
			return ERROR_INPUT_FILE;
		aux_eof = FALSE;
	}

	return OK;
}