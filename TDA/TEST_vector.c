#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void)
{
	void * i;
	ADT_Vector_t * v;
	
	ADT_Vector_new(&v);
	ADT_Vector_append_element(&v,(void *) i);
	return 0;
}