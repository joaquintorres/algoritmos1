#include <stdio.h>
#include <string.h>

#define MAX_TITLE 30
#define MAX_ARTIST 30
#define MAX_YEARS 3000
#define MIN_YEARS 1850
typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_NUMBER_OF_ARGUMENTS,
	ERROR_INVALID_FLAG,
	ERROR_INVALID_DATA,
	ERROR_NUMBER_OF_FIELDS,
	ERROR_OUT_OF_BOUNDS,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE
} status_t; /*En types.h*/

typedef struct {
	char[MAX_TITLE+1] title;
	char[MAX_ARTIST+1] artist;
	ushort year;
	char genre;
} ADT_MP3_Track_t;

status_t ADT_MP3_Track_new(ADT_MP3_Track_t ** p)
{
	if (p == NULL)
		return ERROR_NULL_POINTER;
	if ((*p = (ADT_MP3_Track_t *) malloc(sizeof(ADT_MP3_Track_t))) == NULL)
		return ERROR_MEMORY;
	(*p)->title = '\0';
	(*p)->artist = '\0';
	(*p)->year = 0; /*Preguntar*/
	/*(*p)->genre Preguntar */
	return OK;
}
status_t ADT_MP3_Track_new_from_parameters(ADT_MP3_Track_t ** p, const char * title, const char * artist, ushort year, char genre)
{
	if (p == NULL || name == NULL || artist == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(title) > MAX_TITLE || strlen(artist) > MAX_ARTIST || year > MAX_YEARS || year < MIN_YEARS)
		return ERROR_OUT_OF_BOUNDS;

	if ((*p = (ADT_MP3_Track_t *) malloc(sizeof(ADT_MP3_Track_t))) == NULL)
		return ERROR_MEMORY;
	
	strcpy((*p)->title, title);
	strcpy((*p)->artist, artist);
	(*p)->year = year;
	(*p)->genre = genre;
	return OK;
}

status_t ADT_MP3_Track_load(ADT_MP3_Track_t ** p, FILE * fo)
{
	return OK;
}
/*USA MEMORIA DINAMICA MUAJAJJAJAJAJJAJASJSDJJDAJS*/
char * ADT_MP3_Track_get_title(const ADT_MP3_Track_t * p)
{
	char * aux;
	if (p == NULL)
		return NULL;
	strdupl(p->title,&aux);
	return aux;	
}
/*USA MEMORIA DINAMICA MUAJAJJAJAJAJJAJASJSDJJDAJS LIBERARRRRRRRR*/
char * ADT_MP3_Track_get_artist(const ADT_MP3_Track_t * p)
{
	char * aux;
	if (p == NULL)
		return NULL;
	strdupl(p->artist,&aux);
	return aux;	
}

char ADT_MP3_Track_get_genre(const ADT_MP3_Track_t * p)
{
	if (p == NULL)
		return NULL
	return (p->genre);
}

status_t ADT_MP3_Track_set_title(ADT_MP3_Track_t ** p, const char * title)
{
	if (p == NULL || title == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(title) > MAX_TITLE)
		return ERROR_OUT_OF_BOUNDS;
	strcpy((*p)->title, title);
	return OK;
}

status_t ADT_MP3_Track_set_artist(ADT_MP3_Track_t ** p, const char * artist)
{
	if (p == NULL || artist == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(artist) > MAX_ARTIST)
		return ERROR_OUT_OF_BOUNDS;
	strcpy((*p)->artist,artist);
	return OK;
}

status_t ADT_MP3_Track_set_genre(ADT_MP3_Track_t ** p, const char genre)
{
	if (p == NULL)
		return ERROR_NULL_POINTER;
	(*p)->genre = genre;
	return OK;
}