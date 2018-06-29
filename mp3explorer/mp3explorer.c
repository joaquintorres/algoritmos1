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
	
	if (output_filename == NULL || input_files == NULL)
		return ERROR_NULL_POINTER;
	if ((st = ADT_Vector_new(&vector)) != OK)
		return st;
	if ((st = ADT_Vector_set_destructor(vector,ADT_MP3_Track_delete)) != OK)
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
		/*CIERRE*/
		if (fclose(fi) == EOF)
			return ERROR_DISK_SPACE;
	}


	if (fclose(fo) == EOF)
		return ERROR_DISK_SPACE;

	return OK;
}