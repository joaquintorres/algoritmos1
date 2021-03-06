/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "types.h"
#include "mp3explorer.h"

char * format_dict[MAX_FORMATS]={
	ARG_FMT_CSV,
	ARG_FMT_XML
};

char * sort_dict[MAX_SORT_CRITERIA]={
	CMD_ARG_SORT_BY_NAME,
	CMD_ARG_SORT_BY_ARTIST,
	CMD_ARG_SORT_BY_GENRE
}; 

int main(int argc, char * argv[])
{
	status_t st;
	config_t config;
	char ** input_files;
	size_t len;

	if ((st = validate_arguments(argc, argv, &config, &input_files, &len)) != OK)
		return st;
	if ((st = mp3_explorer(config.format, config.sort, config.output_filename, input_files, len)) != OK)
		return st;

	return OK;
}

status_t validate_arguments(size_t argc, char * argv[], config_t * config, char ***input_files, size_t * len)
{
	size_t i;
	bool_t found;

	if (argv == NULL || config == NULL || input_files == NULL || len == NULL)
		return ERROR_NULL_POINTER;
	if (argc < MIN_NUMBER_OF_ARGS)
		return ERROR_INVALID_NUMBER_OF_ARGS;
	if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_POSITION],CMD_ARG_FORMAT_FLAG))
		return ERROR_INVALID_FLAG;

	found = FALSE;
	while (found == FALSE)
	{
		for (i = 0; i < MAX_FORMATS; i++)
		{
			if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_VALUE],format_dict[i]) == 0)
			{
				config->format = i;
				found = TRUE;
			}
		}
		if (found == FALSE)
			return ERROR_INVALID_ARG;
	}

	if (strcmp(argv[CMD_ARG_SORT_CRITERION_TOKEN_POSITION], CMD_ARG_SORT_CRITERION_FLAG))
		return ERROR_INVALID_FLAG;

	found = FALSE;
	while (found == FALSE)
	{
		for (i = 0; i < MAX_SORT_CRITERIA; i++)
		{
			if (strcmp(argv[CMD_ARG_SORT_CRITERION_TOKEN_VALUE],sort_dict[i]) == 0)
			{
				config->sort = i;
				found = TRUE;
			}
		}
		if (found == FALSE)		
			return ERROR_INVALID_ARG;
	}
	
	if (strcmp(argv[CMD_ARG_OUTPUT_TOKEN_POSITION], CMD_ARG_OUTPUT_FLAG))
		return ERROR_INVALID_FLAG;
	
	config->output_filename = argv[CMD_ARG_OUTPUT_TOKEN_VALUE];
	
	*len = argc - CMD_ARG_OUTPUT_TOKEN_VALUE-1;
	*input_files = argv + (CMD_ARG_OUTPUT_TOKEN_VALUE+1);
	return OK;
}