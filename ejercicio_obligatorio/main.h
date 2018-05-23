/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.h
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define UNIT_RESISTANCE "[kOhm]"
#define UNIT_CAPACITANCE "[nF]"
#define UNIT_FREQUENCY "[Hz]"
#define UNIT_QUALITY_FACTOR ""

#define MAX_STR 100
#define MAX_ERRORS 3

typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_DATA,
	ERROR_INVALID_RESULT
	} status_t;

/***PROTOTIPOS**********/
status_t read_resistor_value(const char * msg, double * val);
status_t read_frequency_value(const char * msg, double * val);
status_t read_quality_factor(const char * msg, double * val);
status_t calculate_capacitor_C1(double res_val_R1, double res_val_R2, double freq, double q, double * cap_val_C1);
status_t calculate_capacitor_C2(double res_val_R1, double res_val_R2, double freq, double q, double * cap_val_C2);
status_t print_resistor_value(const char * msg, double val);
status_t print_capacitor_value(const char * msg, double val);
status_t print_frequency_value(const char * msgdouble val);
status_t print_quality_factor(double val, const char * msg);
status_t print_error_message(status_t err);
/***********************/

