/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: records.c
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "types.h"
#include "records.h"

/*Pasa un arreglo de cadenas a una estructura record_t, destruye la estructura*/
status_t make_record_from_string_array(record_t * record, char ** string_array)
{
	char * temp;
	char * aux;

	
	if (record == NULL || string_array == NULL)
		return ERROR_NULL_POINTER;
	
	if (strdupl(string_array[FIELD_POSITION_FOR_ID], &aux))
		return ERROR_MEMORY;

	record -> id = strtoul(aux, &temp, 10);
	if (*temp && *temp != '\n')
		return ERROR_INVALID_KEY;

	if ((strlen(string_array[FIELD_POSITION_FOR_BARCODE])) != EAN_BARCODE_LEN)
		return ERROR_INVALID_BARCODE;

	strcpy(record -> barcode, string_array[FIELD_POSITION_FOR_BARCODE]);

	/*free(&(record->description));*/
	if(strdupl(string_array[FIELD_POSITION_FOR_DESCRIPTION],&(record -> description)))
		return ERROR_MEMORY;

	return OK;
}
/*Lee del archivo CSV un registro, que pasa por puntero, además de un puntero a bool_t que indica si se encontró EOF*/
status_t read_record_from_CSV_file(record_t * record, FILE * file, char field_del, bool_t * eof)
{
	char * line;
	char ** aux_str_array;
	size_t l;
	status_t st;
	bool_t aux_eof;
	*eof = FALSE;

	
	if (record == NULL || file == NULL)
		return ERROR_NULL_POINTER;

	if ((st = read_line_from_file(file, &line, &aux_eof)) != OK)
		return st;
	

	if(aux_eof == TRUE)
	{
		*eof = TRUE;
		return OK;	
	}

	if ((st = split(line, &aux_str_array,field_del, &l)) != OK)
		return st;

	if (l < MIN_FIELDS || l > MAX_FIELDS)
		return ERROR_NUMBER_OF_FIELDS;

	if((st = make_record_from_string_array(record,aux_str_array))!= OK)
		return st;
	
	destroy_string_array(&aux_str_array,l);
	free(line);
	
	return OK;
}

/*Escribe sobre un archivo una estrucura record_t, en formato CSV*/
status_t export_record_to_CSV_file(record_t record,FILE * target_file,char field_del)
{
	if (target_file == NULL)
		return ERROR_NULL_POINTER;

	fprintf(target_file, "%d%c", record.id, field_del);
	fprintf(target_file, "%s%c", record.barcode, field_del);
	fprintf(target_file, "%s", record.description);
	fputc('\n', target_file);

	return OK;
}