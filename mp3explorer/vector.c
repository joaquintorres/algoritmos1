/*  ***************************************************************
	Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
	Trabajo Práctico N.° 2: Indexación automática de archivos MP3
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: vector.c
	Descripción: Programa que ordena un número arbitrario de archivos MP3
	por un criterio especificado por el usuario y los exporta ordenados en un 
	formato también determinado por el usuario.
	****************************************************************/

/*TDA Vector*/
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "types.h"

#define INIT_CHOP 20
#define CHOP_SIZE 10

struct ADT_Vector_t{
	void ** elements;
	size_t size;
	size_t alloc_size;
	comparator_t comparator;
	destructor_t destructor;
	printer_t printer;
};

/*Asigna memoria e inicializa los atributos a un valor seguro, Y NADA MÁS.
  Si quiero inicializarla con valores hago otro creador.*/
status_t ADT_Vector_new(ADT_Vector_t ** p)
{
	size_t i;
	
	if (p == NULL)
		return ERROR_NULL_POINTER;
	if ((*p = (ADT_Vector_t *) malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_MEMORY;

	if (((*p)->elements = (void **) malloc(INIT_CHOP * sizeof(void *))) == NULL)
	{
		free(*p);
		*p = NULL;
		return ERROR_MEMORY;
	}

	for (i = 0; i < INIT_CHOP; i++)
		(*p)->elements[i] = NULL;

	(*p)->size = 0;
	(*p)->alloc_size = INIT_CHOP;
	/******DESTRUCTORES,COMPARADORES, ETC.**********/
	(*p)->destructor = NULL;
	(*p)->comparator = NULL;
	(*p)->printer = NULL;
	/***********************************************/
	return OK;
}

/*AGREGAR EL USO DEL DESTRUCTOR PARA NO DEJAR UN PUNTERO COLGADO*/
status_t ADT_Vector_append_element(ADT_Vector_t ** p, void * new_element)
{
	void ** aux;

	if (p == NULL || new_element == NULL)
		return ERROR_NULL_POINTER;

	if (((*p)->alloc_size) == ((*p)->size))
	{
		(*p)->alloc_size += CHOP_SIZE;
		if ((aux = (void **) realloc((*p)->elements, ((*p)->alloc_size) * sizeof(void *))) == NULL)
		{
			ADT_Vector_delete(p);
			return ERROR_MEMORY;
		}
		(*p)->elements = aux;
	}
	
	(*p)->elements[(*p)->size] = new_element;
	((*p)->size)++;
	return OK;
}

/*Destruye el vector, el segundo argumento que se le pasa es un puntero
  a una función que indica cómo borrar cada globito.*/
status_t ADT_Vector_delete(ADT_Vector_t ** p)
{
	size_t i;
	status_t st;

	if (p == NULL)
		return ERROR_NULL_POINTER;
	for (i= 0; i < (*p)->size; i++)
	{
		if ((st = (*p)->destructor(&((*p)->elements[i]))) != OK)
			return st;
	}
	free((*p)->elements);
	(*p)->elements = NULL;
	free(*p);
	*p = NULL;
	return OK;
}

/**GETTERS Y SETTERS**/
void * ADT_Vector_get_element(const ADT_Vector_t * v, int position)
{
	if (v == NULL)
		return NULL;
	if (position > (v->size))
		return NULL;
	return (v->elements[position]);
}

status_t ADT_Vector_set_element(ADT_Vector_t ** p, int position, void * new_element)
{
	status_t st;
	void ** aux;

	if (p == NULL || new_element == NULL)
		return ERROR_NULL_POINTER;
	
	if (position > ((*p)->size))
	{
		if (position > ((*p)->alloc_size))
		{
			(*p)->alloc_size = position + CHOP_SIZE;
			if ((aux = (void **) realloc((*p)->elements, ((*p)->alloc_size) * sizeof(void *))) == NULL)
			{
				ADT_Vector_delete(p);
				return ERROR_MEMORY;
			}
			(*p)->elements = aux;
			(*p)->size = position;
			(*p)->elements[position] = new_element;
			return OK;
		}else 
		{
			(*p)->size = position;
			(*p)->elements[position] = new_element;
			return OK;
		} /*se toma este caso para evitar llamar al destructor sobre memoria restringida*/
	}

	if ((st = (*p)->destructor((*p)->elements[position])) != OK) /*destruye el elemento*/
		return st;
	(*p)->elements[position] = new_element; /*el tamaño no se modifica.*/
	return OK;
}

status_t ADT_Vector_set_destructor(ADT_Vector_t * v, destructor_t pf)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;
	v->destructor = pf;
	return OK;
}

status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t pf)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;
	v->comparator = pf;
	return OK;
}

status_t ADT_Vector_set_printer(ADT_Vector_t * v, printer_t pf)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;
	v->printer = pf;
	return OK;
}

bool_t ADT_Vector_is_empty(const ADT_Vector_t * v)
{
	return (v->size)?FALSE:TRUE;
}

status_t ADT_Vector_sort(ADT_Vector_t * v)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;
	qsort(v->elements, v->size ,sizeof(void *), v->comparator);
	return OK;
}

void * ADT_Vector_search(ADT_Vector_t * v, void * key)
{
	if (v == NULL || key == NULL)
		return NULL;
	return (bsearch(key,v->elements, v-> size,sizeof(void *), v->comparator));
}

bool_t ADT_Vector_equals(const ADT_Vector_t * v1, const ADT_Vector_t * v2)
{
	size_t i;

	if (v1->size != v2->size)
		return FALSE;
	for (i = 0; i < v1->size; i++)
	{
		if (v1->comparator(v1->elements[i], v2->elements[i]))
			return FALSE;
	}
	return TRUE;
}

status_t ADT_Vector_export_as_CSV(const ADT_Vector_t * v, void * pcontext, FILE * fo)
{
	size_t i;
	status_t st;

	if (v == NULL || pcontext == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < v->size; i++)
	{
		if ((st = v->printer(v->elements[i],pcontext, fo)) != OK) /*puntero a función que imprime la línea en CSV*/
			return st;
	}
	return OK;
}

status_t ADT_Vector_export_as_XML(const ADT_Vector_t * v, void * pcontext, FILE * fo)
{
	size_t i;
	status_t st;

	if (v == NULL || pcontext == NULL)
		return ERROR_NULL_POINTER;
	fprintf(fo, "%s\n", XML_HEADER);
	fprintf(fo, "%s%s%s\n", "<",XML_ELEMENT_TAG,">");
	for (i = 0; i < v->size; i++)
	{
		if ((st = v->printer(v->elements[i],pcontext, fo)) != OK) /*puntero a función que imprime la línea en CSV*/
			return st;
	}
	fprintf(fo, "%s%s%s\n", "</",XML_ELEMENT_TAG,">");
	return OK;
}