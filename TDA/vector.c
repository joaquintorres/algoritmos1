/*TDA Vector*/
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define INIT_CHOP 20
#define CHOP_SIZE 10

struct ADT_Vector_t{
	void ** elements;
	size_t size;
	size_t alloc_size;
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

	(*p)->elements = NULL;
	(*p)->size = 0;
	(*p)->alloc_size = INIT_CHOP;
	/******DESTRUCTORES,COMPARADORES, ETC.**********/
	/*(*p)->destructor = NULL;
	(*p)->comparator = NULL;
	(*p)->printer = NULL;*/
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
		(*p)->alloc_size+=CHOP_SIZE;
		if ((aux = (void **) realloc((*p)->elements, CHOP_SIZE * sizeof(void *))) == NULL)
		{
			/*Debería destruir todo el trabajo? I don't think so.*/
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
status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(void *))
{
	size_t i;
	status_t st;

	if (p == NULL)
		return ERROR_NULL_POINTER;
	for (i= 0; i < (*p)->size; i++)
	{
		if ((st = (*pf)((*p)->elements[i])) != OK) /*Con destructor pasado como pf*/
			return st;
		(*p)->elements[i] = NULL;
	}
	free((*p)->elements);
	(*p)->elements = NULL;
	free(*p);
	*p = NULL;
	return OK;
}


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
	if (p == NULL || new_element == NULL)
		return ERROR_NULL_POINTER;
	if (position > ((*p)->size))
		return ERROR_OUT_OF_BOUNDS;
	(*p)->elements[position] = new_element;
	return OK;
}

bool_t ADT_Vector_is_empty(const ADT_Vector_t * p)
{
	return (p->size)?FALSE:TRUE;
}

status_t ADT_Vector_sort(ADT_Vector_t * v, comparator_t pf)
{
	if (v == NULL || pf == NULL)
		return ERROR_NULL_POINTER;
	qsort(v->elements, v-> size,sizeof(void *), pf);
	return OK;
}

bool_t ADT_Vector_equals(const ADT_Vector_t * v1, const ADT_Vector_t * v2, comparator_t pf)
{
	size_t i;

	if (v1->size != v2->size)
		return FALSE;
	for (i = 0; i < v1->size; i++)
	{
		if ((*pf)(v1->elements[i], v2->elements[i]))
			return FALSE;
	}
	return TRUE;
}

status_t ADT_Vector_export_as_CSV(const ADT_Vector_t * v, void * context, printer_t pf, FILE * fo)
{
	size_t i;
	status_t st;

	if (v == NULL || context == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < v->size; i++)
	{
		if ((st = (*pf)(v->elements[i], fo)) != OK)
			return st;
	}
	return OK;
}