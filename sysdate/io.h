/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 1: Fecha y hora del sistema
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: io.h
	Descripción: Programa que recibe un formato por argumentos de línea
	de órdenes y devuelve la fecha actual en ese formato.
	****************************************************************/
#ifndef IO__H
#define IO__H

#include <stdio.h>
#include "types.h"

#define MAX_ERRORS 5
#define MAX_SERIOUSNESS 4

/*MENSAJES*/
#define ERR_MSG_OK "" /*Dejo la constante simbólica en caso de que se desee agregar un mensaje*/
#define ERR_MSG_NULL_POINTER "Ha ocurrido un error por pasaje de puntero nulo."
#define ERR_MSG_NUMBER_OF_ARGS "Cantidad de argumentos inválida."
#define ERR_MSG_FLAG "Flag incorrecta."
#define ERR_MSG_INVALID_ARGUMENT "Argumento incorrecto."
#define ERR_MSG_UNKNOWN "Error desconocido."

#define ERR_SERIOUSNESS_TRIVIAL_MSG ""
#define ERR_SERIOUSNESS_WARNING_MSG "Advertencia: "
#define ERR_SERIOUSNESS_ERROR_MSG "Error: "
#define ERR_SERIOUSNESS_FATAL_ERROR_MSG "Error fatal:"

#define USR_MSG_USAGE "La sintaxis correcta es ./sysdate -fmt <format> o sysdate -fmt <format> si el ejecutable se encuentra en PATH."
#define USR_MSG_USAGE_FMT "Los formatos aceptados son: "

/*******************/

/*ARGUMENTOS*/
#define MIN_NUMBER_OF_ARGS 3
#define MAX_NUMBER_OF_ARGS 3

#define CMD_ARG_FORMAT_TOKEN_POSITION 1
#define CMD_ARG_FORMAT_TOKEN_VALUE 2
#define CMD_ARG_FORMAT_FLAG "-fmt"

/************/

/*PROTOTIPOS*/
void print_error_message(error_seriousness_t seriousness, status_t status);

#endif