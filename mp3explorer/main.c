#include <stdio.h>
#include <string.h>
#include "main.h"
#include "types.h"

char * format_dict[MAX_FORMATS]={
	ARG_FMT_CSV,
	ARG_FMT_XML,
	ARG_FMT_HTML
};

char * sort_dict[MAX_SORT_CRITERIA]={
	ARG_SORT_NAME,
	ARG_SORT_ARTIST,
	ARG_SORT_GENRE
}; 

int main(int argc, char * argv[])
{
	status_t st;
	format_t format;
	sort_t sort;

	if ((st = validate_arguments(argc, argv, &format, &sort)) != OK)
		return st;
	printf("%d\n",format);
	printf("%d\n",sort);
	return OK;
}

status_t validate_arguments(size_t argc, char * argv[], format_t * format, sort_t * sort)
{
	size_t i;
	if (argv == NULL)
		return ERROR_NULL_POINTER;
	if (argc < MIN_NUMBER_OF_ARGS)
		return ERROR_INVALID_NUMBER_OF_ARGS;
	if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_POSITION],CMD_ARG_FORMAT_FLAG))
		return ERROR_INVALID_FLAG;
	for (i = 0; i < MAX_FORMATS; i++)
	{
		if (strcmp(argv[CMD_ARG_FORMAT_TOKEN_VALUE],format_dict[i]) == 0)
		{
			*format = i;
			if (strcmp(argv[CMD_ARG_SORT_CRITERION_TOKEN_POSITION], CMD_ARG_SORT_CRITERION_FLAG))
				return ERROR_INVALID_FLAG;
			for (i = 0; i < MAX_SORT_CRITERIA; i++)
			{
				if (strcmp(argv[CMD_ARG_SORT_CRITERION_TOKEN_VALUE],sort_dict[i]) == 0)
				{
					*sort = i;
					
					return OK;
				}
			}
			return ERROR_INVALID_ARG;
		}
	}
	return ERROR_INVALID_ARG;
}