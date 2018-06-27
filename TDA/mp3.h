#include <stdio.h>

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

/*Se declara un tema como ADT_MP3_Track * track;*/
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


struct ADT_MP3_Track_t;
typedef struct ADT_MP3_Track_t ADT_MP3_Track_t;
/*PRIMITIVAS*/

/*Crea un nuevo tema vacío*/
status_t ADT_MP3_Track_new(ADT_MP3_Track_t ** p);

/*Crea un nuevo tema a partir de los parámetros título, artista y género*/
status_t ADT_MP3_Track_new_from_parameters(ADT_MP3_Track_t ** p, const char * title, const char * artist, char genre);

/*Crea un nuevo tema a partir de un archivo MP3, que debe ser abierto como archivo binario.*/
status_t ADT_MP3_Track_load(ADT_MP3_Track_t ** p, FILE * fo);

/*Devuelve el título del tema. Utiliza memoria dinámica por lo que la variable a la que
  se asigna DEBE SER LIBERADA CON LA FUNCIÓN free() PARA EVITAR FUGAS DE MEMORIA/FALLAS DE SEGMENTACIÓN.*/
/*Por ejemplo,
  char * title;
  ADT_MP3_Track_t * track;
  ADT_MP3_Track_new(&track);
  title = ADT_MP3_Track_get_title(track);
  printf("%s:%s \n", "Título:", title);
  free(title);*/
char * ADT_MP3_Track_get_title(const ADT_MP3_Track_t * p);

/*Devuelve el artista del tema. Utiliza memoria dinámica por lo que la variable a la que
  se asigna DEBE SER LIBERADA CON LA FUNCIÓN free() PARA EVITAR FUGAS DE MEMORIA/FALLAS DE SEGMENTACIÓN.*/
/*Por ejemplo,
  char * artist;
  ADT_MP3_Track_t * track;
  ADT_MP3_Track_new(&track);
  title = ADT_MP3_Track_get_artist(track);
  printf("%s:%s \n", "Artista:", artist);
  free(title);*/
char * ADT_MP3_Track_get_artist(const ADT_MP3_Track_t * p);

/*Devuelve el género del tema.*/
char ADT_MP3_Track_get_genre(const ADT_MP3_Track_t * p);

/*Establece el título del tema.*/
status_t ADT_MP3_Track_set_title(ADT_MP3_Track_t ** p, const char * title);

/*Establece el artista del tema.*/
status_t ADT_MP3_Track_set_artist(ADT_MP3_Track_t ** p, const char * artist);

/*Establece el género del tema*/
status_t ADT_MP3_Track_set_genre(ADT_MP3_Track_t ** p, const char genre);

/*Exporta el tema en formato CSV*/
status_t ADT_MP3_Track_export_as_CSV(const ADT_MP3_Track_t * p, char del, FILE * fo);
/*Exporta el tema en formato XML*/
status_t ADT_MP3_Track_export_as_XML(const ADT_MP3_Track_t * p, FILE * fo);

