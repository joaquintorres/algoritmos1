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

/*Tamaño máximo de una cadena de caracteres para el título y artista de un tema.*/
#define MAX_TITLE   30
#define MAX_ARTIST  30

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
char * ADT_MP3_Track_get_genre(const ADT_MP3_Track_t * p);

/*Establece el título del tema.*/
status_t ADT_MP3_Track_set_title(ADT_MP3_Track_t ** p, const char * title);

/*Establece el artista del tema.*/
status_t ADT_MP3_Track_set_artist(ADT_MP3_Track_t ** p, const char * artist);

/*Establece el género del tema*/
status_t ADT_MP3_Track_set_genre(ADT_MP3_Track_t ** p, const char * genre);

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

#endif