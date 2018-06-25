/*TDA Vector*/
#include <stdio.h>
#include <stdlib.h>

#define INIT_CHOP 20
typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INVALID_KEY,
	ERROR_DUPLICATED_KEY,
	ERROR_INVALID_BARCODE,
	ERROR_NONEXISTENT_RECORD,
	ERROR_INVENTORY_FILE,
	ERROR_ADDITIONS_FILE,
	ERROR_NUMBER_OF_FIELDS,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t; /*En types.h*/

typedef enum {
	FALSE,
	TRUE
} bool_t;

typedef int (*comparator_t)(const void *, const void *);

typedef struct {
	void ** elements;
	size_t size;
	size_t alloc_size;
} ADT_Vector_t;

/*Asigna memoria e inicializa los atributos a un valor seguro, Y NADA MÁS.
  Si quiero inicializarla con valores hago otro creador.*/
status_t ADT_Vector_new(ADT_Vector_t ** p)
{
	size_t i;

	if (p == NULL)
		return ERROR_NULL_POINTER;
	if ((*p = (ADT_Vector_t *) malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_MEMORY;

	if ((*p->elements = (void **) malloc(INIT_CHOP * sizeof(void *))) == NULL)
	{
		free(*p);
		*p = NULL;
		return ERROR_MEMORY;
	}
	for (i = 0; i < INIT_CHOP; i++)
		(*p)->elements[i] = NULL;

	(*p)->elements = NULL;
	(*p)->size = 0;
	(*p)->alloc_size = 0;
	/******DESTRUCTORES,COMPARADORES, ETC.**********/
	/*(*p)->destructor = NULL;
	(*p)->comparator = NULL;
	(*p)->printer = NULL;*/
	/***********************************************/
	

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
		return (v->elements[position]);
}

bool_t ADT_Vector_is_empty(const ADT_Vector_t * p)
{
	return (p->size)?FALSE:TRUE;
}

status_t ADT_Vector_sort(ADT_Vector_t * v, comparator_t)
{
	
}

bool_t ADT_Vector_equals(const ADT_Vector_t * v1, const ADT_Vector_t * v2, comparator_t pf)
{
	size_t i;

	if (v1->size != v2->size)
		return FALSE;
	for (i = 0; i < v->size; i++)
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
		if ((st = (*pf)(v->elements[i]), fo) != OK)
			return st;
	}
	return OK;
}