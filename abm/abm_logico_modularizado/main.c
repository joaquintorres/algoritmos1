/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c (para altas)
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "types.h"
#include "utils.h"
#include "records.h"
#include "process_additions.h"



/*Valida los argumentos pasados por línea de órdenes y devuelve por puntero las variables validadas.*/
status_t validate_arguments(int argc, char * argv[], char * inventory_file_path[], char * additions_file_path[])
{
	if (additions_file_path == NULL || inventory_file_path == NULL)
		return ERROR_NULL_POINTER;
	if(argc > MAX_ARGUMENTS || argc < MIN_ARGUMENTS)
		return ERROR_NUMBER_OF_ARGUMENTS;
	
	if (strcmp(argv[CMD_ARG_INVENTORY_FILE_TOKEN_POSITION], CMD_ARG_INVENTORY_FILE_FLAG))
		return ERROR_INVALID_FLAG; 
	*inventory_file_path = argv[CMD_ARG_INVENTORY_FILE_TOKEN_VALUE];
	
	if (strcmp(argv[CMD_ARG_ADDITIONS_FILE_TOKEN_POSITION], CMD_ARG_ADDITIONS_FILE_FLAG))
		return ERROR_INVALID_FLAG;

	*additions_file_path = argv[CMD_ARG_ADDITIONS_FILE_TOKEN_VALUE];

	return OK;
}

int main(int argc, char *argv[])
{
	char * inventory_file_path;
	char * additions_file_path;
	char * result_file_path;
	FILE * file_inventory;
	FILE * file_additions;
	FILE * file_result;  /*Puntero al archivo resultante de aplicar ABM (o CRUD por sus siglas en inglés)*/
	status_t st;

	if ((st = validate_arguments(argc, argv, &inventory_file_path, &additions_file_path)) != OK)
		return st;
	/*APERTURA*/
	if ((file_inventory = fopen(inventory_file_path,"rt")) == NULL)
		return ERROR_INVENTORY_FILE;
	if ((file_additions = fopen(additions_file_path,"rt")) == NULL)
	{
		fclose(file_inventory);
		return ERROR_ADDITIONS_FILE;
	}
	if ((file_result = fopen(TEMP_FILENAME,"wt")) == NULL)
	{
		fclose(file_inventory);
		fclose(file_additions);
		return ERROR_OUTPUT_FILE;
	}
	result_file_path = TEMP_FILENAME;
	
	/*PROCESAMIENTO*/

	if ((st = process_addition_records(file_inventory,file_additions, file_result, FIELD_DELIMITER, LINE_DELIMITER)) != OK)
	{	
		fclose(file_inventory);
		fclose(file_additions);
		fclose(file_result);
		return st;
	}

	/*CIERRE*/
	fclose(file_inventory);
	fclose(file_additions);
	if ((fclose(file_result)) == EOF)
		return ERROR_DISK_SPACE;
	
	if(remove(inventory_file_path))
		return ERROR_OUTPUT_FILE;
	if(rename(result_file_path, inventory_file_path))
		return ERROR_OUTPUT_FILE;
	
	return OK;
}
