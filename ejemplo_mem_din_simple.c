#include <stdio.h>
#include <stdlib.h>
#define INIT_CHOP 100
#define MAX_STR 10
#define CHOP_SIZE 1

double * load_values(size_t * l);
int main(void)
{
	size_t len;
	load_values(&len);
	return 0;
}
double * load_values(size_t * l)
{
	size_t alloc_size;
	double *v; /*arreglo dinámico*/
	double *aux; /*arreglo auxiliar para realloc*/
	char str[MAX_STR]; /*arreglo estático de paso para c dato ingresado*/
	char * temp; /*variable para strtod*/

	if (l == NULL)
		return NULL;
	/*asigno memoria para unos datos iniciales*/
	/*malloc 1*/
	if ((v = (double *)malloc(INIT_CHOP * sizeof(double)) ) == NULL)
	{
		*l = 0;/*Cuando sale mal limpio el puntero de la longitud y devuelvo el coso*/
		return NULL;
	}
	alloc_size = INIT_CHOP;
	*l = 0;

	/*ENTRADA Y REASIGNACIÓN DE MEMORIA*/
	while(fgets(str,MAX_STR +2, stdin) != NULL)
	{
		/*Reasignación de memoria cuando se llega al límite de memoria*/
		if (*l == alloc_size)
		{
			/*Validación de realloc, que devuelve null cuando falla.*/
			/*malloc 2*/
			if ((aux = (double *)realloc(v,(alloc_size + CHOP_SIZE)*sizeof(double))) == NULL)
			{
				/*libero memoria*/
				free(v);
				/*limpio*/
				*l = 0;
				return NULL;
			}
			/*si sale todo bien*/
			v = aux;
			alloc_size += CHOP_SIZE;
		}
		/*Carga de datos*/
		v[(*l)++] = strtod(str, &temp);
		if (*temp && *temp != '\n')
		{
			free(v);
			*l = 0;
			return NULL;
		}
		
	}
	return 0;
}