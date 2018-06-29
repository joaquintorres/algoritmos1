#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mp3.h"
#include "types.h"

/*CONSTANTES DEL ESTÁNDAR ID3V1*/
#define MP3_HEADER_SIZE	  128

#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63  /*Se dejan las posiciones de las otras características*/
#define LEXEM_SPAN_ALBUM   30  /*en caso de que se desee extender la funcionalidad*/

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1
/*******************************/

/*DICCIONARIO DE GÉNEROS*/
#define MAX_GENRE 125
#define MIN_GENRE 0
#define UNKNOWN_GENRE_STR "Unknown"


/***********************/
/*PARÁMETROS XML*/
#define XML_TAG_CONTENT_TITLE  "title"
#define XML_TAG_CONTENT_ARTIST "artist"
#define XML_TAG_CONTENT_GENRE  "genre"

/*CONSTANTES FUNCIONES PRIVADAS*/
#define MAX_STR 100 /*_compare_strings evita usar memoria dinámica para strings que tienen un tamaño fijo.*/

/*PROTOTIPOS FUNCIONES PRIVADAS*/
status_t _get_mp3_header_parameters (char * title,char * artist,char * genre,FILE * fo);
status_t _strdupl(const char * s, char ** t);
int _compare_strings(const char * a, const char * b);
/*******************************/

char * genre_dict[MAX_GENRE+1] = {
	"Blues",
	"Classic Rock",
	"Country",
	"Dance",
	"Disco",
	"Funk",
	"Grunge",
	"Hip-Hop",
	"Jazz",
	"Metal",
	"New Age",
	"Oldies",
	"Other",
	"Pop",
	"R&B",
	"Rap",
	"Reggae",
	"Rock",
	"Techno",
	"Industrial",
	"Alternative",
	"Ska",
	"Death Metal",
	"Pranks",
	"Soundtrack",
	"Euro-Techno",
	"Ambient",
	"Trip-Hop",
	"Vocal",
	"Jazz+Funk",
	"Fusion",
	"Trance",
	"Classical",
	"Instrumental",
	"Acid",
	"House",
	"Game",
	"Sound Clip",
	"Gospel",
	"Noise",
	"AlternRock",
	"Bass",
	"Soul",
	"Punk",
	"Space",
	"Meditative",
	"Instrumental Pop",
	"Instrumental Rock",
	"Ethnic",
	"Gothic",
	"Darkwave",
	"Techno-Industrial",
	"Electronic",
	"Pop-Folk",
	"Eurodance",
	"Dream",
	"Southern Rock",
	"Comedy",
	"Cult",
	"Gangsta",
	"Top 40",
	"Christian Rap",
	"Pop/Funk",
	"Jungle",
	"Native American",
	"Cabaret",
	"New Wave",
	"Psychadelic",
	"Rave",
	"Showtunes",
	"Trailer",
	"Lo-Fi",
	"Tribal",
	"Acid Punk",
	"Acid Jazz",
	"Polka",
	"Retro",
	"Musical",
	"Rock & Roll",
	"Hard Rock",
	"Folk",
	"Folk-Rock",
	"National Folk",
	"Swing",
	"Fast Fusion",
	"Bebob",
	"Latin",
	"Revival",
	"Celtic",
	"Bluegrass",
	"Avantgarde",
	"Gothic Rock",
	"Progressive Rock",
	"Psychedelic Rock",
	"Symphonic Rock",
	"Slow Rock",
	"Big Band",
	"Chorus",
	"Easy Listening",
	"Acoustic",
	"Humour",
	"Speech",
	"Chanson",
	"Opera",
	"Chamber Music",
	"Sonata",
	"Symphony",
	"Booty Brass",
	"Primus",
	"Porn Groove",
	"Satire",
	"Slow Jam",
	"Club",
	"Tango",
	"Samba",
	"Folklore",
	"Ballad",
	"Poweer Ballad",
	"Rhytmic Soul",
	"Freestyle",
	"Duet",
	"Punk Rock",
	"Drum Solo",
	"A Capela",
	"Euro-House",
	"Dance Hall"
};

struct ADT_MP3_Track_t {
	char title[LEXEM_SPAN_TITLE+1];
	char artist[LEXEM_SPAN_ARTIST+1];
	char genre;
};

status_t ADT_MP3_Track_new(ADT_MP3_Track_t ** p)
{
	if (p == NULL)
		return ERROR_NULL_POINTER;
	if ((*p = (ADT_MP3_Track_t *) malloc(sizeof(ADT_MP3_Track_t))) == NULL)
		return ERROR_MEMORY;
	(*p)->title[0] = '\0';
	(*p)->artist[0] = '\0';
	(*p)->genre = MAX_GENRE + 1;
	return OK;
}

status_t ADT_MP3_Track_delete(void * p)
{
	if (p == NULL)
		return ERROR_NULL_POINTER;
	free(*(ADT_MP3_Track_t **)p);
	*(ADT_MP3_Track_t **)p = NULL;
	return OK;
}

status_t ADT_MP3_Track_new_from_parameters(ADT_MP3_Track_t ** p, const char * title, const char * artist,const char * genre)
{
	size_t i; 
	bool_t found; /*variables auxiliares*/
	if (p == NULL || title == NULL || artist == NULL || genre == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(title) > LEXEM_SPAN_TITLE || strlen(artist) > LEXEM_SPAN_ARTIST)
		return ERROR_OUT_OF_BOUNDS;

	if ((*p = (ADT_MP3_Track_t *) malloc(sizeof(ADT_MP3_Track_t))) == NULL)
		return ERROR_MEMORY;
	
	strcpy((*p)->title, title);
	strcpy((*p)->artist, artist);

	/*búsqueda del byte de género*/
	found = FALSE;
	while (found == FALSE)
	{
		for (i = MIN_GENRE; i < MAX_GENRE + 1 ; i++)
		{
			if (strcmp(genre,genre_dict[i]) == 0)
			{
				
				(*p)->genre = (char)i;     /*Si se ponen mal los límites del ciclo e i es mayor al valor*/
				found = TRUE;				/*máximo de char, el valor del byte de genre va a ser negativo.*/
			}							   /*Las funciones que exportan genre como cadena de caracteres debe validar esto.*/
		}
		if (found == FALSE)
		{
			(*p)->genre = MAX_GENRE + 1; /*Género "desconocido"*/
			return ERROR_OUT_OF_BOUNDS;
		}
	}
	/*La búsqueda podría ponerse en su propia función privada.*/

	return OK;
}

status_t ADT_MP3_Track_load(ADT_MP3_Track_t ** p, FILE * fo)
{
	char title[LEXEM_SPAN_TITLE];
	char artist[LEXEM_SPAN_ARTIST];
	char genre;
	status_t st;

	if (p == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	if ((*p = (ADT_MP3_Track_t *) malloc(sizeof(ADT_MP3_Track_t))) == NULL)
		return ERROR_MEMORY;

	if ((st = _get_mp3_header_parameters(title,artist,&genre,fo))!=OK)
		return st;

	strcpy((*p)->title, title);
	strcpy((*p)->artist, artist);
	(*p)->genre = genre;
	return OK;
}
/*USA MEMORIA DINAMICA. LIBERAR.*/
char * ADT_MP3_Track_get_title(const ADT_MP3_Track_t * p)
{
	char * aux;
	if (p == NULL)
		return NULL;
	_strdupl(p->title,&aux);
	return aux;	
}
/*USA MEMORIA DINAMICA. LIBERAR.*/
char * ADT_MP3_Track_get_artist(const ADT_MP3_Track_t * p)
{
	char * aux;
	if (p == NULL)
		return NULL;
	_strdupl(p->artist,&aux);
	return aux;	
}

char * ADT_MP3_Track_get_genre(const ADT_MP3_Track_t * p)
{
	if (p == NULL)
		return '\0';
	if (p->genre < MIN_GENRE || p->genre > MAX_GENRE)
		return UNKNOWN_GENRE_STR;
	return (genre_dict[(int) p->genre]);
}

status_t ADT_MP3_Track_set_title(ADT_MP3_Track_t ** p, const char * title)
{
	if (p == NULL || title == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(title) > LEXEM_SPAN_TITLE)
		return ERROR_OUT_OF_BOUNDS;
	strcpy((*p)->title, title);
	return OK;
}

status_t ADT_MP3_Track_set_artist(ADT_MP3_Track_t ** p, const char * artist)
{
	if (p == NULL || artist == NULL)
		return ERROR_NULL_POINTER;
	if (strlen(artist) > LEXEM_SPAN_ARTIST)
		return ERROR_OUT_OF_BOUNDS;
	strcpy((*p)->artist,artist);
	return OK;
}

status_t ADT_MP3_Track_set_genre(ADT_MP3_Track_t ** p, const char * genre)
{
	bool_t found;
	size_t i;
	if (p == NULL || genre == NULL)
		return ERROR_NULL_POINTER;
	/*búsqueda del byte de género*/
	found = FALSE;
	while (found == FALSE)
	{
		for (i = MIN_GENRE; i < MAX_GENRE + 1 ; i++)
		{
			if (strcmp(genre,genre_dict[i]) == 0)
			{
				
				(*p)->genre = (char)i;     /*Si se ponen mal los límites del ciclo e i es mayor al valor*/
				found = TRUE;				/*máximo de char, el valor del byte de genre va a ser negativo.*/
			}							   /*Las funciones que exportan genre como cadena de caracteres debe validar esto.*/
		}
		if (found == FALSE)
			return ERROR_OUT_OF_BOUNDS; /*no borra lo que ya estaba, devuelve un error*/
	}
	return OK;
}


int ADT_MP3_Track_compare_by_title(const void * pv1, const void * pv2)
{
	ADT_MP3_Track_t ** t1;
	ADT_MP3_Track_t ** t2;

	t1 = (ADT_MP3_Track_t **) pv1;
	t2 = (ADT_MP3_Track_t **) pv2;
	return (_compare_strings((*t1)->title,(*t2)->title));
}

int ADT_MP3_Track_compare_by_artist(const void * pv1, const void * pv2)
{
	ADT_MP3_Track_t ** t1;
	ADT_MP3_Track_t ** t2;

	t1 = (ADT_MP3_Track_t **) pv1;
	t2 = (ADT_MP3_Track_t **) pv2;
	return (_compare_strings((*t1)->artist,(*t2)->artist));
}

int ADT_MP3_Track_compare_by_genre(const void * pv1, const void * pv2)
{
	ADT_MP3_Track_t ** t1;
	ADT_MP3_Track_t ** t2;

	t1 = (ADT_MP3_Track_t **) pv1;
	t2 = (ADT_MP3_Track_t **) pv2;
	return((int)((*t1)->genre - (*t2)->genre)); /*También se podría hacer alfabéticamente*/
}

status_t ADT_MP3_Track_export_as_CSV(const void * pv, void * pcontext, FILE * fo)
{
	char del;
	ADT_MP3_Track_t * p;
	if (pv == NULL || fo == NULL || pcontext == NULL)
		return ERROR_NULL_POINTER;

	p = (ADT_MP3_Track_t *) pv;
	del = *(char *)pcontext;

	fprintf(fo,"%s", p->title);
	fputc(del,fo);
	fprintf(fo,"%s", p->artist);
	fputc(del,fo);

	if (p->genre < MIN_GENRE || p->genre > MAX_GENRE)
		fprintf(fo, "%s\n", UNKNOWN_GENRE_STR);
	else
		fprintf(fo, "%s\n", genre_dict[(int)p->genre]);
	return OK;
}

status_t ADT_MP3_Track_export_as_XML(const void * pv, void * pcontext, FILE * fo)
{
	char * tag_content_track;
	ADT_MP3_Track_t * p;
	if(pv == NULL || fo == NULL || pcontext == NULL)
		return ERROR_NULL_POINTER;
	tag_content_track = (char *)pcontext;
	p = (ADT_MP3_Track_t *) pv;
	fprintf(fo,"\t%s%s%s\n", "<",tag_content_track,">");
	/*se usa %s para imprimir el caracter '<' para que puedan agregársele
	  eventuales modificaciones.*/
	fprintf(fo,"\t\t%s%s%s ", "<",XML_TAG_CONTENT_TITLE,">");
	fprintf(fo,"%s", p->title);
	fprintf(fo,"%s%s%s\n", "</",XML_TAG_CONTENT_TITLE,">");
	
	fprintf(fo,"\t\t%s%s%s ", "<",XML_TAG_CONTENT_ARTIST,">");
	fprintf(fo,"%s", p->artist);
	fprintf(fo,"%s%s%s\n", "</",XML_TAG_CONTENT_ARTIST,">");

	fprintf(fo,"\t\t%s%s%s ", "<",XML_TAG_CONTENT_GENRE,">");
	if (p->genre < MIN_GENRE || p->genre > MAX_GENRE)
		fprintf(fo, "%s", UNKNOWN_GENRE_STR);
	else
		fprintf(fo, "%s", genre_dict[(int)p->genre]);
	fprintf(fo,"%s%s%s\n", "</",XML_TAG_CONTENT_GENRE,">");
	
	fprintf(fo,"\t%s%s%s\n", "</",tag_content_track,">");

	return OK;
}

status_t _get_mp3_header_parameters (char * title,char * artist,char * genre,FILE * fo)
{
	char buf[MP3_HEADER_SIZE];
	char header[MP3_HEADER_SIZE];
	size_t length;
	if (fo == NULL || title == NULL || artist == NULL)
		return ERROR_NULL_POINTER;

	fseek(fo, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
	length = ftell(fo);							/* da la distancia al comienzo 				*/
	fseek(fo,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/
	fread(&header,sizeof(char),MP3_HEADER_SIZE,fo);

	memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
	buf[LEXEM_SPAN_TITLE] = '\0';
	strcpy(title, buf);
	
	memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
	buf[LEXEM_SPAN_ARTIST] = '\0';
	strcpy(artist, buf);
	
	memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
	buf[LEXEM_SPAN_GENRE] = '\0';
	*genre = buf[0];

	return OK;
}

status_t _strdupl(const char * s, char ** t)
{
	size_t i;

	if (s == NULL || t == NULL)
		return ERROR_NULL_POINTER;
	if ((*t = (char *) malloc((strlen(s)+1)*sizeof(char))) == NULL)
		return ERROR_MEMORY;
	for (i = 0;((*t)[i] = s[i]);i++);
	return OK;
}

/*Compara cadenas de caracteres no arbitrariamente largas, pero sin hacer distinciones
entre minúsculas y mayúsculas. Así, "Pink Floyd", "pink floyd" y "PiNK fLoYD" son "iguales"*/ 
int _compare_strings(const char * a, const char * b)
{
	size_t i;
	char  low_a[MAX_STR]; /*se evita el uso de memoria estática, útil por*/
	char  low_b[MAX_STR];
	/*se crea una copia de los argumentos*/
	for (i = 0; (low_a[i] = a[i]); i++);
	for (i = 0; (low_b[i] = b[i]); i++);

	/*se pasan las copias a minúsculas*/
	for (i = 0; i < strlen(low_a); i++)
		low_a[i] = tolower(low_a[i]);
	for (i = 0; i < strlen(low_b); i++)
		low_b[i] = tolower(low_b[i]);

	return (strcmp(low_a,low_b));
}