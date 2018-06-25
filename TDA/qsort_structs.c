#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 10

typedef struct {
	size_t id;
	double price;
	char * description;
} product_t;

int compare_prices(const void * a,const void * b)
{
	double diff;
	diff = (((product_t *)a)->price - ((product_t *)b)->price);
	if (diff > 0)
		return 1;
	if (diff < 0)
		return (-1);
	return 0;
}

int compare_id(const void * a, const void * b)
{
	return (((product_t *)a)->id - ((product_t *)b)->id);
}

int compare_description(const void * a, const void * b)
{
	return (strcmp(((product_t *)a)->description, ((product_t *)b)->description));
}

void print_product(product_t product)
{
	printf("Producto %d:\n", product.id);
	printf("\t %s\n", product.description);
	printf("\t $%04.02f\n", product.price);
}

int main(void)
{
	size_t i;
	product_t product_array[MAX_PRODUCTS] = {
		{345,100.0, "Hamburguesa con queso"},
		{222,80.0, "Hamburguesa simple"},
		{1222,50.0, "Agua sin gas"},
		{1,1.0, "Caramelo"},
		{33,9000000.0, "servicio de mesa"},
		{97,14.50, "Mitomilanesa"},
		{11,2222, "Doblones"},
		{33333333, 3.1415, "Pie de manzana"},
		{1234,567.0, "Ñandúes"},
		{321,66, "Xcomplete"}
	};

	for (i = 0; i < MAX_PRODUCTS; i++)
		print_product(product_array[i]);

	qsort(product_array,MAX_PRODUCTS,sizeof(product_t),compare_id);
	printf("%s\n",  "*******COMPARACIÓN POR ID*********");
	for (i = 0; i < MAX_PRODUCTS; i++)
		print_product(product_array[i]);


	qsort(product_array,MAX_PRODUCTS,sizeof(product_t),compare_prices);
	printf("%s\n",  "*******COMPARACIÓN POR PRECIOS*********");
	for (i = 0; i < MAX_PRODUCTS; i++)
		print_product(product_array[i]);

	qsort(product_array,MAX_PRODUCTS,sizeof(product_t),compare_description);
	printf("%s\n",  "*******COMPARACIÓN ALFABÉTICA*********");
	for (i = 0; i < MAX_PRODUCTS; i++)
		print_product(product_array[i]);

	return 0;
}