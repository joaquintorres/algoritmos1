#include<stdio.h>
int main(void){
	typedef enum{
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	} dia_t;
	/*Monday you can fall apart...*/
	dia_t parcial = WEDNESDAY;
	printf("%d \n", parcial);
	/*¿cómo hago si quiero imprimir el tipo de la variable*/
	return 0;
	}
