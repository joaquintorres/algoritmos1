#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_BARCODE,
	ERROR_OUT_OF_BOUNDS,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t; /*En types.h*/

typedef enum {
	FALSE,
	TRUE
} bool_t;

struct ADT_Vector_t;
typedef struct ADT_Vector_t ADT_Vector_t;

typedef int (*comparator_t)(const void *, const void *);
typedef status_t (*printer_t)(const void *, FILE * f);
/*PRIMITIVAS*/
status_t ADT_Vector_new(ADT_Vector_t ** p);
status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(void *));
status_t ADT_Vector_append_element(ADT_Vector_t ** p, void * new_element);
void * ADT_Vector_get_element(const ADT_Vector_t * v, int position);
status_t ADT_Vector_set_element(ADT_Vector_t ** p, int position, void * new_element);
bool_t ADT_Vector_is_empty(const ADT_Vector_t * p);
status_t ADT_Vector_sort(ADT_Vector_t * v, comparator_t);
bool_t ADT_Vector_equals(const ADT_Vector_t * v1, const ADT_Vector_t * v2, comparator_t pf);
status_t ADT_Vector_export_as_CSV(const ADT_Vector_t * v, void * context, printer_t pf, FILE * fo);