#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

/*status_t destroy_string(void * p)
{
	if (p == NULL)
		return ERROR_NULL_POINTER;
	*((char *)p)='\0';
	return OK;
}*/
status_t destroy_int(void * ip)
{
	if (ip == NULL)
		return ERROR_NULL_POINTER;
	*((int *)ip) = 0;
	return OK;
}

int compare_ints(const void * a, const void *b)
{
	return(**(int **)a - **(int **)b);
}

int main(void)
{
	ADT_Vector_t * v;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int o;
	size_t count;

	i = 13;
	j = 1000;
	k = 423;
	l = 2134;
	m = 45;
	n = 0;
	o = 780;


	ADT_Vector_new(&v);
	ADT_Vector_set_destructor(v, destroy_int);
	ADT_Vector_set_comparator(v, compare_ints);

	ADT_Vector_append_element(&v,&i);
	ADT_Vector_append_element(&v,&j);
	ADT_Vector_append_element(&v,&k);
	ADT_Vector_append_element(&v,&l);
	ADT_Vector_append_element(&v,&m);
	ADT_Vector_append_element(&v,&n);
	ADT_Vector_append_element(&v,&o);
	
	for (count = 0; count < 7; count++)
		printf("%d\n", *((int *) ADT_Vector_get_element(v,count)));
	
	ADT_Vector_sort(v);
	for (count = 0; count < 7; count++)
		printf("%d\n", *((int *) ADT_Vector_get_element(v,count)));

	ADT_Vector_delete(&v);		


	return OK;
}