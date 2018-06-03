/*  ***************************************************************
	Algoritmos y Progrmación I - 95.11 - Curso Ing. Martín Cardozo
	Caso de Estudio N.° 2: Altas, bajas y modificaciones
	Alumno: Joaquín Torres
	Correo Electrónico: joaquintorres1997@gmail.com
	Archivo: altas.c
	Descripción: Programa que agrega líneas sobre un archivo CSV a
	partir de otro. Los archivos deben tener tres campos diferenciados para el ID, 
	el código de barras y la descripción de un producto.
	****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGUMENTS 5
#define MAX_ARGUMENTS 5

#define CMD_ARG_INVENTORY_FILE_TOKEN_POSITION 1
#define CMD_ARG_INVENTORY_FILE_TOKEN_VALUE 2
#define CMD_ARG_INVENTORY_FILE_FLAG "-i"

#define CMD_ARG_APPENDED_FILE_TOKEN_POSITION 3
#define CMD_ARG_APPENDED_FILE_TOKEN_VALUE 4
#define CMD_ARG_APPENDED_FILE_FLAG "-a"

#define TEMP_FILENAME "salida.tmp"
#define LINE_DELIMITER '|'
#define FIELD_DELIMITER ','

#define INIT_CHOP 20
#define CHOP_SIZE 5

#define ID_POSITION 0
#define BARCODE_POSITION 1
#define DESCRIPTION_POSITION 2

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_SPLIT,
	ERROR_BAD_INPUT,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

typedef struct {
	size_t id;
	char * barcode;
	char * description;
} item_t;

/*Valida los argumentos pasados por línea de órdenes y devuelve por puntero las variables validadas.*/
status_t validate_arguments(int argc, char * argv[], char ** inventory_file_path, char ** appended_file_path)
{
	if (appended_file_path == NULL || inventory_file_path == NULL)
		return ERROR_NULL_POINTER;
	if(argc > MAX_ARGUMENTS || argc < MIN_ARGUMENTS)
		return ERROR_NUMBER_OF_ARGUMENTS;
	
	if (strcmp(argv[CMD_ARG_INVENTORY_FILE_TOKEN_POSITION], CMD_ARG_INVENTORY_FILE_FLAG))
		return ERROR_INVALID_FLAG; 
	*inventory_file_path = argv[CMD_ARG_INVENTORY_FILE_TOKEN_VALUE];
	
	if (strcmp(argv[CMD_ARG_APPENDED_FILE_TOKEN_POSITION], CMD_ARG_APPENDED_FILE_FLAG))
		return ERROR_INVALID_FLAG;

	*appended_file_path = argv[CMD_ARG_APPENDED_FILE_TOKEN_VALUE];

	return OK;
}

/*Lee líneas de un archivo, separando una línea con algún delimitador pasado como argumento.
La línea se devuelve por puntero como una cadena de caracteres. Además, se devuelve un booleano
por puntero indicando si se llegó al EOF o no (con TRUE y FALSE respectivamente).*/
status_t read_line_from_file(FILE * file, char del, char ** s, bool_t * eof)
{
	size_t used_size;
	size_t alloc_size;
	int c;
	char * aux;

	if (s == NULL || eof == NULL)
		return ERROR_NULL_POINTER;
	if ((*s = (char *) malloc(INIT_CHOP*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	alloc_size = INIT_CHOP;
	used_size = 0;
	while ((c = fgetc(file))!= del && c != EOF)
	{
		if (used_size == alloc_size - 1)
		{
			if ((aux = (char *) realloc(*s, (alloc_size + CHOP_SIZE)*sizeof(char))) == NULL)
			{
				free(*s);
				*s = NULL;
				return ERROR_MEMORY;
			}
			*s = aux;
			alloc_size += CHOP_SIZE;
		}
		(*s)[used_size++] = c;
	}
	*eof = (c == EOF) ? TRUE:FALSE;
	return OK;	
}
/*Recibe una cadena de caracteres y devuelve por puntero la misma cadena copiada.*/
status_t strdupl(const char * s, char ** t)
{
	size_t i;

	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	for (i = 0;(*t)[i] = s[i];i++);
	return OK;
}
/*Destruye un arreglo de cadenas de caracteres.*/
status_t destroy_string_array(char *** p, size_t l)
{
	size_t i;

	if (p == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < l; i++)
	{
		free((*p)[i]);
		(*p)[i] = NULL;
	}/*Libera las cadenas*/
	free(*p); /*Libera el arreglo.*/
	*p = NULL;
	return OK;
}

/*Recibe una línea separada en campos por un delimitador pasado como argumento.
Devuelve por puntero un arreglo de cadenas que contiene en cada elemento uno de los campos originales
y una variable que contiene la cantidad de campos.*/
char ** split(const char * s, char del, size_t * l) /*Falta pasarlo a status_t y reemplazar ERROR_SPLIT*/
{
	char * line; /*Se toma la cadena por copia.*/
	char ** fields;
	char * q; /*Variable auxiliar*/
	char * p; /*Variable auxiliar*/
	size_t i;
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (s == NULL || l == NULL)
		return NULL;
	if (strdupl(s, &line))
	{
		*l = 0;
		return NULL;

	}
	for (i = 0; line [i]; i++)
	{
		if (line[i] == del)
			(*l)++;	
	} /*Se cuenta la cantidad de delimitadores.*/
	(*l)++; /*La cantidad de campos es la cantidad de delimitadores más uno.*/
	if ((fields = (char **) malloc ((*l)*sizeof(char *)) ) == NULL)
	{
		free(line);
		*l = 0;
		free(fields);
		return NULL;
	}
	for (q = line, i = 0; (p = strtok(q, del_array)) != NULL;q =NULL, i++)
	{
			if (strdupl(p, &(fields[i])))
			{
				free(line);
				destroy_string_array(&fields,i);
				*l = 0;
				return NULL;
			}
	}

	free(line); /*Se libera la copia.*/
	return fields;
}
/*Carga los datos de un archivo CSV abierto a un arreglo de estructuras item_t, devolviendo 
además por puntero el "tamaño" del arreglo.*/
status_t load_item_array_from_file(FILE * file_ptr, item_t ** item_array, size_t *n, char del)
{
	char * line;
	char * temp;
	char ** string_array;
	bool_t eof;
	status_t st;
	size_t used_size;
	size_t alloc_size;
	size_t string_array_length;
	item_t * aux;

	if(item_array == NULL || n == NULL)
		return ERROR_NULL_POINTER;
	*n = 0; /*"tamaño" del arreglo*/
	eof = FALSE;
	alloc_size = 0;
	used_size = 0;		/*la primera iteración va a usar realloc "como si fuera" malloc, */
	*item_array = NULL; /*así que pongo el arreglo como nulo*/
	while ((st = read_line_from_file(file_ptr, del,&line,&eof)) == OK && eof == FALSE)
	{
		if (used_size == alloc_size)
		{
			if ((aux = (item_t *) realloc(*item_array, (alloc_size + CHOP_SIZE) * sizeof(item_t))) == NULL)
			{
				free (*item_array);
				*item_array = NULL;
				return ERROR_MEMORY;
			}
			*item_array = aux;
			alloc_size += CHOP_SIZE;
		}
		/*transformo cada línea en un arreglo de cadenas*/
		if((string_array = split(line, del, &string_array_length)) == NULL)
			return ERROR_SPLIT;
		(*item_array)->id = strtoul(string_array[ID_POSITION],&temp,10);
		/*niveles de punteros: *item_array es arreglo de estructuras*/
		if (*temp && *temp != '\n' )
			return ERROR_INVALID_DATA;
		(*item_array)->barcode = string_array[BARCODE_POSITION];
		(*item_array)->description = string_array[DESCRIPTION_POSITION];
		(*item_array)++;
		used_size++;

	}
	*n = used_size;
	return st; /*si sale mal devuelve el error de lectura, si sale bien devuelve ok.*/
}
/*Escribe sobre un archivo un arreglo de estructuras item_t, en formato CSV*/
status_t write_item_array_to_file(FILE * target_file_ptr, item_t * item_array, size_t item_array_size, char field_del, char line_del)
{
	size_t i;
	if (target_file_ptr == NULL || item_array == NULL)
		return ERROR_NULL_POINTER;
	if (item_array_size == 0)
		return ERROR_BAD_INPUT;
	for (i = 0; i < item_array_size; ++i)
	{
		fprintf(target_file_ptr, "%d%c", item_array[i].id, field_del);
		fprintf(target_file_ptr, "%s%c", item_array[i].barcode, field_del);
		fprintf(target_file_ptr, "%s%c", item_array[i].description, field_del);
		fputc(line_del, target_file_ptr);
	}
	return OK;
}
/*Realiza las altas de un arreglo a otro, depositando el resultado en */
status_t add_to_item_array(item_t * modified_arr,size_t modified_arr_size,item_t * modifying_arr,size_t modifying_arr_size, item_t ** merged_arr)
{
	size_t i;
	size_t j;

	if (modified_arr == NULL || modifying_arr == NULL || merged_arr == NULL)
		return ERROR_NULL_POINTER;
	if ((*merged_arr = (item_t *) malloc((modified_arr_size + modifying_arr_size)*sizeof(item_t))) == NULL)
	{
		free(*merged_arr);
		*merged_arr = NULL;
		return ERROR_MEMORY;
	}
	for (i = 0; i < modified_arr_size;++i)
	{
		for (j = 0; j < modifying_arr_size; ++j)
		{
			if (modified_arr[i].id == modifying_arr[j].id)
				return ERROR_INPUT_FILE; /*Si se trata de agregar un número de ID igual a alguno existente hay un error.*/
		}
	}
	for (i = 0; i < modified_arr_size; ++i)
	{
		(*merged_arr)[i].id = modified_arr[i].id;
		(*merged_arr)[i].barcode = modified_arr[i].barcode;
		(*merged_arr)[i].description = modified_arr[i].description;
	}
	for (j = 0; j < modifying_arr_size; ++j)
	{
		(*merged_arr)[i+j+1].id = modifying_arr[j].id;
		(*merged_arr)[i+j+1].barcode = modifying_arr[j].barcode;
		(*merged_arr)[i+j+1].description = modifying_arr[j].description;
	}
	return OK;
}

int main(int argc, char *argv[])
{
	char * inventory_file_path;
	char * appended_file_path;
	char *crud_file_path;
	FILE * inventory_file_ptr;
	FILE * appended_file_ptr;
	FILE * crud_file_ptr;  /*Puntero al archivo resultante de aplicar ABM (o CRUD por sus siglas en inglés)*/
	item_t * inventory_item_array;
	item_t * appended_item_array;
	item_t * crud_item_array;
	size_t inventory_item_array_size;
	size_t appended_item_array_size;
	size_t crud_item_array_size; 
	status_t st;

	if ((st = validate_arguments(argc, argv, &inventory_file_path, &appended_file_path)) != OK)
		return st;
	/*APERTURA*/
	if ((inventory_file_ptr = fopen(inventory_file_path,"rt")) == NULL)
		return ERROR_INPUT_FILE;
	if ((appended_file_ptr = fopen(appended_file_path,"rt")) == NULL)
	{
		fclose(inventory_file_ptr);
		return ERROR_INPUT_FILE;
	}
	if ((crud_file_ptr = fopen(TEMP_FILENAME,"wt")) == NULL)
	{
		fclose(inventory_file_ptr);
		fclose(appended_file_ptr);
		return ERROR_INPUT_FILE;
	}
	crud_file_path = TEMP_FILENAME;
	/*CARGA*/
	if ((st = load_item_array_from_file(inventory_file_ptr,&inventory_item_array,&inventory_item_array_size,LINE_DELIMITER))!=OK)
		return st;

	if ((st = load_item_array_from_file(appended_file_ptr,&appended_item_array,&appended_item_array_size,LINE_DELIMITER))!=OK)
		return st;
	
	/*ABM*/
	crud_item_array_size = inventory_item_array_size + appended_item_array_size;

	if ((st = add_to_item_array(inventory_item_array,inventory_item_array_size,appended_item_array,appended_item_array_size, &crud_item_array))!=OK)
		return OK;	

	/*ESCRITURA*/
	if((st = write_item_array_to_file(crud_file_ptr, crud_item_array,crud_item_array_size,FIELD_DELIMITER,LINE_DELIMITER)) != OK)
		return st;
	/*CIERRE*/
	fclose(inventory_file_ptr);
	fclose(appended_file_ptr);
	if ((fclose(crud_file_ptr)) == EOF)
		return ERROR_DISK_SPACE;
	if(remove(inventory_file_path))
		return ERROR_OUTPUT_FILE;
	if(rename(crud_file_path, inventory_file_path))
		return ERROR_OUTPUT_FILE;
	return OK;
}