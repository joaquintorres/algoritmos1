#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_POSITION 0
#define BARCODE_POSITION 1
#define DESCRIPTION_POSITION 2

#define INIT_CHOP 20
#define CHOP_SIZE 5


typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
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

status_t read_line_from_file(FILE * file, char del, char ** s, bool_t * eof)
{
	size_t used_size;
	size_t alloc_size;
	int c;
	char * aux ;

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

status_t strdupl(const char * s, char ** t)
{
	size_t i;

	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	for (i = 0;((*t)[i] = s[i]);i++);
	return OK;
}

status_t split(const char * s,item_t * item ,char del) /*Falta pasarlo a status_t y reemplazar ERROR_SPLIT*/
{
	char * line; /*Se toma la cadena por copia.*/
	char * p ; /*Variable auxiliar*/
	char * aux ;		/*Variable auxiliar*/
	char * temp; /*Variable auxiliar*/
	char del_array[2]; /*strtok() toma una cadena de caracteres, no un char.*/

	del_array[0] = del;
	del_array[1] = '\0';

	if (s == NULL)
		return ERROR_NULL_POINTER;
	if (strdupl(s, &line))
		return ERROR_MEMORY;

	p = strtok(line, del_array);
	if (strdupl(p, &aux))
	{
		free(line);
		return ERROR_MEMORY;
	}
	item -> id = strtoul(aux,&temp,10);
	if (*temp && *temp != '\n')
		return ERROR_INPUT_FILE;
	
	p = strtok(NULL, del_array);
	if (strdupl(p, &(item -> barcode)))
	{
		free(line);
		return ERROR_MEMORY;
	}	

	p = strtok(NULL, del_array);
	if (strdupl(p, &(item -> description)))
	{
		free(line);
		return ERROR_MEMORY;
	}

	free(line); /*Se libera la copia.*/
	return OK;
}

status_t write_item_to_file(FILE * target_file,item_t item,char field_del, char line_del)
{
	if (target_file == NULL)
		return ERROR_NULL_POINTER;

	fprintf(target_file, "%d%c", item.id, field_del);
	fprintf(target_file, "%s%c", item.barcode, field_del);
	fprintf(target_file, "%s", item.description);
	fputc(line_del, target_file);

	return OK;
}

status_t process_addition_items(FILE * old_file,FILE * mod_file, FILE * new_file, char line_del, char field_del)
{
	char * line;
	char * aux_line;
	bool_t eof;
	bool_t aux_eof;
	status_t st;
	item_t old_file_item;
	item_t mod_file_item;

	eof = FALSE;
	while ((st = read_line_from_file(old_file, line_del, &line, &eof)) == OK && eof == FALSE)
	{
		if ((st = split(line,&old_file_item,field_del)) != OK)
			return st;
		if ((st = write_item_to_file(new_file, old_file_item, field_del, line_del)) != OK)
			return st;
	} 
	/*Puede reemplazarse por una función que escriba directamente todos los datos sobre el archivo nuevo, pero
	  esto permite cambiar los delimitadores del CSV de salida modificando la función y realizar validaciones sobre, por ejemplo,
	  el número de ID.*/

	eof = FALSE;
	if (fseek(old_file, 0L, SEEK_SET)) /*Se devuelve el cursor del archivo original al principio, equivalente a rewind(). */
		return ERROR_INPUT_FILE; 		/* Usar rewind() no permitiría validar el resultado, por lo menos en la norma ANSI C89*/ 

	aux_eof = FALSE;
	while ((st = read_line_from_file(mod_file, line_del, &line, &eof)) == OK && eof == FALSE)
	{
		if ((st = split(line,&mod_file_item,field_del)) != OK)
			return st;
		while ((st = read_line_from_file(old_file, line_del, &aux_line, &aux_eof)) == OK && eof == FALSE)
		{
			if ((st = split(aux_line,&old_file_item,field_del)) != OK)
				return st;
			if (mod_file_item.id == old_file_item.id)
				return ERROR_INPUT_FILE;
			if ((st = write_item_to_file(new_file, mod_file_item, field_del, line_del)) != OK)
				return st;
		}
		if (fseek(old_file, 0L, SEEK_SET))
			return ERROR_INPUT_FILE;
		aux_eof = FALSE;
	}

	return OK;
}
int main(void)
{
	status_t st;
	FILE * inventory_file_ptr;
	FILE * appended_file_ptr;
	FILE * crud_file_ptr;  /*Puntero al archivo resultante de aplicar ABM (o CRUD por sus siglas en inglés)*/
	if ((inventory_file_ptr = fopen("inventario.csv","rt")) == NULL)
		return ERROR_INPUT_FILE;
	if ((appended_file_ptr = fopen("mod.csv","rt")) == NULL)
	{
		fclose(inventory_file_ptr);
		return ERROR_INPUT_FILE;
	}
	if ((crud_file_ptr = fopen("test.tmp","wt")) == NULL)
	{
		fclose(inventory_file_ptr);
		fclose(appended_file_ptr);
		return ERROR_INPUT_FILE;
	}

	if ((st = process_addition_items(inventory_file_ptr,appended_file_ptr, crud_file_ptr, '|', ',')) != OK)
		return st;
	fclose(inventory_file_ptr);
	fclose(appended_file_ptr);
	if ((fclose(crud_file_ptr)) == EOF)
		return ERROR_DISK_SPACE;

	return OK;
}