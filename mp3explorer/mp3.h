/*  ***************************************************************
  Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
  Trabajo Práctico N.° 2: Indexación automática de archivos MP3
  Alumno: Joaquín Torres
  Correo Electrónico: joaquintorres1997@gmail.com
  Archivo: mp3.h
  Descripción: Programa que ordena un número arbitrario de archivos MP3
  por un criterio especificado por el usuario y los exporta ordenados en un 
  formato también determinado por el usuario.
  ****************************************************************/
#ifndef MP3__H
#define MP3__H

#include <stdio.h>
#include "types.h"
#include "utils.h"

/*Tamaño máximo de una cadena de caracteres para el título y artista de un tema.*/
#define MAX_TITLE   30
#define MAX_ARTIST  30

/*CONSTANTES DEL ESTÁNDAR ID3V1*/
#define MP3_HEADER_SIZE   128

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
#define UNKNOWN_GENRE 126

/***********************/
/*PARÁMETROS XML*/
#define XML_TAG_CONTENT_TITLE  "title"
#define XML_TAG_CONTENT_ARTIST "artist"
#define XML_TAG_CONTENT_GENRE  "genre"

struct ADT_MP3_Track_t;
typedef struct ADT_MP3_Track_t ADT_MP3_Track_t;
/*PRIMITIVAS*/

/*Crea un nuevo tema vacío*/
status_t ADT_MP3_Track_new(ADT_MP3_Track_t ** p);

/*Borra un tema ya creado. IMPORTANTE: borrar un tema declarado pero no inicializado resulta en error*/
status_t ADT_MP3_Track_delete(void * p);

/*Crea un nuevo tema a partir de los parámetros título, artista y género*/
status_t ADT_MP3_Track_new_from_parameters(ADT_MP3_Track_t ** p, const char * title, const char * artist, const char * genre);

/*Crea un nuevo tema a partir de un archivo MP3, que debe ser abierto como archivo binario.*/
status_t ADT_MP3_Track_load_info(ADT_MP3_Track_t ** p, FILE * fo);

/*Devuelve el título del tema o NULL en el caso de título indefinido. Utiliza memoria dinámica por lo que la variable a la que
  se asigna DEBE SER LIBERADA CON LA FUNCIÓN free() PARA EVITAR FUGAS DE MEMORIA/FALLAS DE SEGMENTACIÓN.*/
char * ADT_MP3_Track_get_title(const ADT_MP3_Track_t * p);

/*Devuelve el artista del tema o NULL en el caso de artista indefinido. Utiliza memoria dinámica por lo que 
la variable a la que se asigna DEBE SER LIBERADA CON LA FUNCIÓN free() PARA EVITAR FUGAS DE MEMORIA/FALLAS DE SEGMENTACIÓN.*/
char * ADT_MP3_Track_get_artist(const ADT_MP3_Track_t * p);

/*Devuelve el género del tema.*/
char * ADT_MP3_Track_get_genre(const ADT_MP3_Track_t * p);

/*Establece el título del tema.*/
status_t ADT_MP3_Track_set_title(ADT_MP3_Track_t ** p, const char * title);

/*Establece el artista del tema.*/
status_t ADT_MP3_Track_set_artist(ADT_MP3_Track_t ** p, const char * artist);

/*Establece el género del tema*/
status_t ADT_MP3_Track_set_genre(ADT_MP3_Track_t ** p, char genre);

/*Exporta el tema en formato CSV. el delimitador(char) debe pasarse como puntero en pcontext.*/
status_t ADT_MP3_Track_export_as_CSV(const void * pv, void * pcontext, FILE * fo);
/*Exporta el tema en formato XML*/
status_t ADT_MP3_Track_export_as_XML(const void * pv, void * pcontext, FILE * fo);

/*Compara por título, devuelve un número negativo, nulo o positivo si el título de 
  t1 es menor, igual o mayor al título de t2, respectivamente. Los argumentos que 
  recibe son punteros dobles a ADT_Track_t*/
int ADT_MP3_Track_compare_by_title(const void * pv1, const void * pv2);

/*Compara por artista, devuelve un número negativo, nulo o positivo si el artista de 
  t1 es menor, igual o mayor al artista de t2, respectivamente. Los argumentos que 
  recibe son punteros dobles a ADT_Track_t*/
int ADT_MP3_Track_compare_by_artist(const void * pv1, const void * pv2);

/*Compara por género, devuelve un número negativo, nulo o positivo si el género de 
  t1 es menor, igual o mayor al género de t2, respectivamente. Los argumentos que 
  recibe son punteros dobles a ADT_Track_t*/
int ADT_MP3_Track_compare_by_genre(const void * pv1, const void * pv2);

/*PROTOTIPOS FUNCIONES PRIVADAS*/
status_t _get_mp3_header_info (char * title,char * artist,char * genre,FILE * fo);
#endif