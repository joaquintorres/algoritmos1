/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.h
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/
#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

#define MIN_ARGUMENTS 5
#define MAX_ARGUMENTS 5

#define CMD_ARG_INVENTORY_FILE_TOKEN_POSITION 1
#define CMD_ARG_INVENTORY_FILE_TOKEN_VALUE 2
#define CMD_ARG_INVENTORY_FILE_FLAG "-i"

#define CMD_ARG_ADDITIONS_FILE_TOKEN_POSITION 3
#define CMD_ARG_ADDITIONS_FILE_TOKEN_VALUE 4
#define CMD_ARG_ADDITIONS_FILE_FLAG "-a"

#define TEMP_FILENAME "salida.tmp"

#define LINE_DELIMITER '|'
#define FIELD_DELIMITER ','  /*Falta revisar.*/


status_t validate_arguments(int argc, char * argv[], char * inventory_file_path[], char * additions_file_path[]);


#endif