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

#define M_PI 3.14159265358979323846
#define CUTOFF_FREQUENCY 32.0
#define QUALITY_FACTOR 1.7

#define UNIT_RESISTANCE "[kOhm]"
#define UNIT_CAPACITANCE "[nF]"
#define UNIT_FREQUENCY "[Hz]"
#define UNIT_Q_FACTOR " "

#define MIN_RESISTANCE_VALUE 100
#define MAX_RESISTANCE_VALUE 1000000
#define MULTIPLIER_RESISTANCE 1000

#define MIN_CAPACITANCE_VALUE 0.00000000001
#define MAX_CAPACITANCE_VALUE 0.000047
#define MULTIPLIER_CAPACITANCE 0.000000001

#define MIN_FREQUENCY_VALUE 32
#define MAX_FREQUENCY_VALUE 16000
#define MULTIPLIER_FREQUENCY 1

#define MAX_Q_FACTOR_VALUE 2
#define MIN_Q_FACTOR_VALUE 0.5
#define MULTIPLIER_Q_FACTOR 1

#define MAX_STR 100

typedef  enum{
	OK,
	ERROR_NULL_POINTER,
	ERROR_INVALID_DATA,
	ERROR_INVALID_RESULT
	} status_t;

/***PROTOTIPOS**********/
status_t read_resistor_value(const char * msg, double * val);
status_t read_frequency_value(const char * msg, double * val);
status_t read_q_factor_value(const char * msg, double * val);
status_t calculate_capacitor_value(const double res_val_R1, const double res_val_R2, const double freq, const double q, double * cap_val_C1, double * cap_val_C2);
status_t print_component_value(double val, const char * unit, const double multiplier, const char * msg);
void print_error_message(status_t err);
/***********************/

