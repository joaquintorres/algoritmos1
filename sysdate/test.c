#include <stdio.h>
#include <time.h>
typedef enum{
	ERROR_NULL_POINTER = 's',
	ERROR_MEMORY = '#'

}error_t;

int main(void)
{
	time_t raw_time;
	struct tm * cal_ptr;
	if ((raw_time = time(NULL)) == -1)
		return 1;
	if((cal_ptr = localtime(&raw_time)) == NULL)
		return 1;
	printf("Día del año: %02d Día del mes:%02d %02d:%02d:%02d\n",cal_ptr -> tm_yday, (cal_ptr->tm_mday) + 30, cal_ptr->tm_hour, cal_ptr->tm_min, cal_ptr->tm_sec);
	printf("%c\n", ERROR_NULL_POINTER);
	cal_ptr -> tm_isdst = 1; 
	cal_ptr -> tm_mday =20; 
	printf("Día del año: %02d Día del mes:%02d %02d:%02d:%02d\n",cal_ptr -> tm_yday, cal_ptr->tm_mday, cal_ptr->tm_hour, cal_ptr->tm_min, cal_ptr->tm_sec);
	return 0;
}
