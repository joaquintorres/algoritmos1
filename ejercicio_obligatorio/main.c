/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Ejercicio Obligatorio
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: main.c
	Descripción: Programa modularizado para el diseño de un 
	ecualizador gráfico. 
	****************************************************************/
#include "main.h"

int main(void)
{
	double resistor_value_R1;
	double resistor_value_R2;

	double capacitor_value_C1;
	double capacitor_value_C2;
	
	double frequency_value;
	double q_factor_value;
	
	/*Para nombrar las variables se asume que R1,R2,C1 y C2 son los nombres para los 
	componentes dados por el esquema circuital.*/
	status_t exit_status;
	
	/*Se verifica para todos los llamados a una función que el estado de salida sea exitoso.*/
	/******LECTURA*****/
	if ((exit_status = read_resistor_value("Ingrese el valor del primer resistor: ", &resistor_value_R1)) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = read_resistor_value("Ingrese el valor del segundo resistor: ", &resistor_value_R2)) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = read_frequency_value("Ingrese el valor de la frecuencia central: ", &frequency_value)) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = read_q_factor_value("Ingrese el valor del factor de calidad: ", &q_factor_value)) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	/*******CÁLCULO*****/
	if ((exit_status = calculate_capacitor_value(resistor_value_R1, resistor_value_R2,frequency_value,q_factor_value, &capacitor_value_C1, &capacitor_value_C2)) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	/*****ESCRITURA*****/
	if ((exit_status = print_component_value(resistor_value_R1, UNIT_RESISTANCE, MULTIPLIER_RESISTANCE, "Valor del resistor R1: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = print_component_value(resistor_value_R2, UNIT_RESISTANCE, MULTIPLIER_RESISTANCE, "Valor del resistor R2: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = print_component_value(frequency_value, UNIT_FREQUENCY, MULTIPLIER_FREQUENCY, "Valor de la frecuencia: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = print_component_value(q_factor_value, UNIT_Q_FACTOR, MULTIPLIER_Q_FACTOR, "Valor del factor de calidad: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status = print_component_value(capacitor_value_C1, UNIT_CAPACITANCE, MULTIPLIER_CAPACITANCE, "Valor del capacitor C1: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}
	
	if ((exit_status =print_component_value(capacitor_value_C2, UNIT_CAPACITANCE, MULTIPLIER_CAPACITANCE, "Valor del capacitor C2: ")) != OK)
	{
		print_error_message(exit_status);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}




/**************************************
Recibe un estado de error e imprime el 
mensaje de error correspondiente.
***************************************/
void print_error_message(status_t err)
{
	switch(err)
	{
		case ERROR_NULL_POINTER:
			fprintf(stderr,"%s", "ERROR: Puntero nulo.\n");
			break;
		case ERROR_INVALID_DATA:
			fprintf(stderr,"%s", "ERROR: Dato de entrada inválido.\n");
			break;
		case ERROR_INVALID_RESULT:
			fprintf(stderr,"%s", "ERROR: Resultado inválido. \n");
			break;
		case OK:
			break;
		default:
			fprintf(stderr,"%s", "ERROR: Error desconocido.");
			break;
	}
}

