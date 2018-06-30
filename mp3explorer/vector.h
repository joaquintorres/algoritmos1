/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: vector.h
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/
#ifndef VECTOR__H
#define VECTOR__H

#include <stdio.h>
#include "types.h"

#define XML_HEADER "<?xml version=\"1.0\" ?>"
#define XML_ELEMENT_TAG "tracks"

/*Un vector se declara como "ADT_Vector * v;". Es un vector polimórfico que contiene
elementos como void *, pero esto no significa que pueda contener distintos tipos de
elementos en cada posición: el tipo de dato de los elementos de un vector DEBE SER
EL MISMO PARA TODOS. */
struct ADT_Vector_t;
typedef struct ADT_Vector_t ADT_Vector_t;

typedef int (*comparator_t)(const void *, const void *);
typedef status_t (*destructor_t)(void *);
typedef status_t (*printer_t)(const void * element, void * pcontext, FILE * f);
typedef status_t (*vector_export)(const ADT_Vector_t * v, void * pcontext, FILE * fo);
/*******************PRIMITIVAS********************/

/*Crea un vector nuevo a partir de una variable previamente declarada como ADT_Vector_t * */
status_t ADT_Vector_new(ADT_Vector_t ** p);

/*Destruye un vector previamente creado.*/
status_t ADT_Vector_delete(ADT_Vector_t ** p);

/*Inserta un elemento new_element al final del vector. Nótese que se recibe el argumento COMO PUNTERO
y, por lo tanto, deben pasarse elementos nuevos como tales, incluso elementos de tipo básico.
Por ejemplo, para hacer un vector que contenga enteros estos deben pasarse como punteros a entero.
Como consecuencia, en este caso particular, cambiar el valor de la variable "fuera" del vector provocaría 
un cambio "dentro" del vector. Por esta razón, no es recomendable tratar un vector como si fuera un arreglo:
si, por ejemplo, se hace un ciclo for que aumente el valor de int i e inserte su dirección de memoria como 
elemento del vector, el vector terminará teniendo todos sus elementos apuntando a i en su último valor.*/
status_t ADT_Vector_append_element(ADT_Vector_t ** p, void * new_element);

/*Devuelve el elemento de la posición position del vector. En caso de no resultar exitosa, devuelve NULL,
por lo que es conveniente realizar la validación pertinente.*/
void * ADT_Vector_get_element(const ADT_Vector_t * v, int position);

/*Cambia el valor del elemento de la posición position, por new_element. El elemento anterior es borrado
permanentemente.*/
status_t ADT_Vector_set_element(ADT_Vector_t ** p, int position, void * new_element);

/*Ingresa la función de destrucción los elementos del vector. Es muy importante ingresarla inmediatamente
 después de crear cada vector.*/
status_t ADT_Vector_set_destructor(ADT_Vector_t * v, destructor_t pf);

/*Ingresa la función de comparación entre elementos del vector. Es muy importante ingresarla inmediatamente
 después de crear cada vector.*/
status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t pf);

/*Ingresa la función de impresión de los elementos del vector. Es muy importante ingresarla inmediatamente
 después de crear cada vector.*/
status_t ADT_Vector_set_printer(ADT_Vector_t * v, printer_t pf);

/*Devuelve TRUE en caso de que el vector esté vacío, y FALSE en el caso de que esté lleno.*/
bool_t ADT_Vector_is_empty(const ADT_Vector_t * p);

/*Ordena los elementos del vector de acuerdo al criterio de comparación ingresado con 
  ADT_Vector_set_comparator.*/
status_t ADT_Vector_sort(ADT_Vector_t * v);

/*Busca el elemento dado por key de acuerdo al criterio de comparación ingresado con 
  ADT_Vector_set_comparator. Para esto, EL VECTOR DEBE ESTAR PREVIAMENTE ORDENADO.*/
void * ADT_Vector_search(ADT_Vector_t * v, void * key);

/*Compara dos vectores de acuerdo al criterio de comparación entre elementos ingresado con 
 ADT_Vector_set_comparator.*/
bool_t ADT_Vector_equals(const ADT_Vector_t * v1, const ADT_Vector_t * v2);

/*Exporta el vector como CSV utilizando el impresor ingresado con ADT_Vector_set_printer,
 con el contexto correspondiente a este último.*/
status_t ADT_Vector_export_as_CSV(const ADT_Vector_t * v, void * pcontext, FILE * fo);

/*Exporta el vector como XML utilizando el impresor ingresado con ADT_Vector_set_printer,
 con el contexto correspondiente a este último.*/
status_t ADT_Vector_export_as_XML(const ADT_Vector_t * v, void * pcontext, FILE * fo);


#endif