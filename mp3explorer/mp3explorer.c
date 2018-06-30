/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: mp3explorer.c
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/
#include <stdio.h>
#include "types.h"
#include "mp3.h"
#include "vector.h"
#include "mp3explorer.h"
#include "main.h"

printer_t printer_dict[MAX_FORMATS] = {
	ADT_MP3_Track_export_as_CSV,
	ADT_MP3_Track_export_as_XML
};
vector_export export_dict[MAX_FORMATS] = {
	ADT_Vector_export_as_CSV,
	ADT_Vector_export_as_XML
};
comparator_t comparator_dict[MAX_SORT_CRITERIA] = {
	ADT_MP3_Track_compare_by_title,
	ADT_MP3_Track_compare_by_artist,
	ADT_MP3_Track_compare_by_genre
};
status_t mp3_explorer(format_t format, sort_t sort, const char * output_filename, char ** input_files, size_t len)
{
	FILE * fo;
	FILE * fi;
	size_t i;
	status_t st;
	ADT_MP3_Track_t * track;
	ADT_Vector_t * vector;
	char CSV_del;
	void * pcontext;
	char XML_track_name[MAX_TRACK_NAME] = CONTEXT_XML_TRACK_NAME;
	CSV_del = CONTEXT_CSV_DELIMITER;

	if (output_filename == NULL || input_files == NULL)
		return ERROR_NULL_POINTER;

	switch (format)
	{
		case FMT_CSV:
			pcontext = (void *)(&CSV_del);
			break;
		case FMT_XML:
			pcontext = (void *)XML_track_name;
			break;
	}

	/*INICIALIZACIÖN DEL VECTOR*/
	if ((st = ADT_Vector_new(&vector)) != OK)
		return st;
	if ((st = ADT_Vector_set_destructor(vector,ADT_MP3_Track_delete)) != OK)
		return st;
	if ((st = ADT_Vector_set_printer(vector,printer_dict[format])) != OK)
		return st;
	if ((st = ADT_Vector_set_comparator(vector,comparator_dict[sort])) != OK)
		return st;

	if ((fo = fopen(output_filename, "wt")) == NULL) /*La salida es en formato texto.*/
		return ERROR_OUTPUT_FILE;
	/*ciclo de extracción de datos*/
	for (i = 0; i < len; i++)
	{
		/*APERTURA*/
		if ((fi = fopen(input_files[i], "rb")) == NULL)
		{
			fclose(fo);
			return ERROR_INPUT_FILE;
		}
		/*PROCESAMIENTO*/

		if ((st = ADT_MP3_Track_load(&track, fi)) != OK)
			return st;
		if ((st = ADT_Vector_append_element(&vector, track)) != OK)
			return st;

		/*CIERRE*/
		if (fclose(fi) == EOF)
			return ERROR_DISK_SPACE;
	}
	/*ORDENAMIENTO*/
	if ((st = ADT_Vector_sort(vector)) != OK)
		return st;

	/*EXPORTACIÓN*/
	if ((st = export_dict[format](vector,pcontext, fo)) != OK)
			return st;
	/*DESTRUCCIÓN*/
	if ((st = ADT_Vector_delete(&vector)) != OK)
		return st;
	if (fclose(fo) == EOF)
		return ERROR_DISK_SPACE;

	return OK;
}