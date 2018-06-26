/*	****************************************************************************************
	Descripcion: Función para extraer los datos del encabezado de un archivo MP3, modificado
	de código escrito por el Ing. Martín Cardozo, (c) Martín Cardozo
	**************************************************************************************** */
#include <stdio.h>
#include <string.h>


#define MP3_HEADER_SIZE		128


#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63
#define LEXEM_SPAN_ALBUM   30

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1

typedef enum { OK, ERROR_NULL_POINTER } status_t;

status_t _get_mp3_header_parameters (char[LEXEM_SPAN_TITLE] * title,char[LEXEM_SPAN_ARTIST] * artist,char * genre,FILE * fo)
{
	char buf[MP3_HEADER_SIZE];
	char header[MP3_HEADER_SIZE];
	size_t length;

	if (fo == NULL)
		return ERROR_NULL_POINTER;

	fseek(fo, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
	length = ftell(fo);							/* da la distancia al comienzo 				*/
	fseek(fo,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/
	fread(header,sizeof(char),MP3_HEADER_SIZE,fo);

	memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
	buf[LEXEM_SPAN_TITLE] = '\0';
	*title = buf;

	memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
	buf[LEXEM_SPAN_ARTIST] = '\0';
	*artist = buf;

	memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
	buf[LEXEM_SPAN_GENRE] = '\0';
	*genre = buf[0];

	return OK;
}
