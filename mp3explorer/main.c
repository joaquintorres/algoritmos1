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
	char * output_filename;
	char ** input_files;
	size_t len;
	size_t i;

	if ((st = validate_arguments(argc, argv, &format, &sort, &output_filename, &input_files, &len)) != OK)
		return st;
	printf("%d\n",format);
	printf("%d\n",sort);
	printf("%s\n",output_filename);
	for (i = 0; i < len; i++)
		printf("%s\n", input_files[i]);
	return OK;
}

status_t validate_arguments(size_t argc, char * argv[], format_t * format, sort_t * sort, char * output_filename[], char ***input_files, size_t * len)
{
	size_t i;
	if (argv == NULL || format == NULL || sort == NULL || output_filename == NULL || input_files == NULL || len == NULL)
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
					if (strcmp(argv[CMD_ARG_OUTPUT_TOKEN_POSITION], CMD_ARG_OUTPUT_FLAG))
						return ERROR_INVALID_FLAG;
					*output_filename = argv[CMD_ARG_OUTPUT_TOKEN_VALUE];
					*len = argc - CMD_ARG_OUTPUT_TOKEN_VALUE-1;
					*input_files = argv + (CMD_ARG_OUTPUT_TOKEN_VALUE+1);
					return OK;
				}
			}
			return ERROR_INVALID_ARG;
		}
	}
	return ERROR_INVALID_ARG;
}