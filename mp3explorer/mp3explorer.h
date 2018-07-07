/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: mp3explorer.h
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/

#ifndef MP3EXPLORER__H
#define MP3EXPLORER__H

/*CONTEXTOS DE EXPORTACIÓN*/

#define CONTEXT_CSV_DELIMITER '|'
#define CONTEXT_XML_TRACK_NAME "track"
#define MAX_TRACK_NAME 10

/*PROTOTIPOS*/
status_t mp3_explorer(format_t format, sort_t sort, const char * output_filename, char ** input_files, size_t len);

#endif