/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
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
#include "records.h"


status_t process_update_records(FILE * inv_file,FILE * mod_file, FILE * new_file, char field_del)
{
	bool_t n1; /*Variable auxiliar de estado de la lectura del inventario*/
	bool_t n2; /*Variable auxiliar de estado de la lectura de las modificaciones*/
	record_t record_inv;
	record_t record_mod;
	status_t st;

	if (inv_file == NULL || mod_file == NULL || new_file == NULL)
		return ERROR_NULL_POINTER;
	/*n1 y n2 indican si se llegó al fin del archivo y st si hubo un error */
	if ((st = read_record_from_CSV_file(&record_inv,inv_file, field_del, &n1)) != OK) 
		return st;

	if ((st = read_record_from_CSV_file(&record_mod,mod_file, field_del, &n2)) != OK) 
		return st;

	while (n1 == FALSE && n2 == FALSE)
	{

		if (record_inv.id < record_mod.id)
		{
			if ((st = export_record_to_CSV_file(record_inv,new_file, field_del)) != OK)
				return st;
			if ((st = read_record_from_CSV_file(&record_inv,inv_file, field_del, &n1)) != OK) 
				return st;
		}else
		{	
			if (record_inv.id == record_mod.id)
			{
				if ((st = export_record_to_CSV_file(record_mod,new_file,field_del)) != OK)
				return st;
				if ((st = read_record_from_CSV_file(&record_mod,mod_file, field_del, &n2)) != OK) 
				return st;
				if ((st = read_record_from_CSV_file(&record_inv,inv_file, field_del, &n1)) != OK) 
				return st;
			}else
			{
				return ERROR_NONEXISTENT_RECORD;
			}
		}
	}
		
	if (n2 == FALSE)
		return ERROR_NONEXISTENT_RECORD;
	/*Se escriben los valores restantes del inventario*/
	while (n1 == FALSE)
	{
	if ((st = export_record_to_CSV_file(record_inv,new_file,field_del)) != OK)
			return st;
	if ((st = read_record_from_CSV_file(&record_inv,inv_file, field_del, &n1)) != OK) 
			return st;
	}

	return OK;
}
