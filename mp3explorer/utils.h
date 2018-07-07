/*  ***************************************************************
  Algoritmos y Programación I - 95.11 - Curso Ing. Martín Cardozo
  Trabajo Práctico N.° 2: Indexación automática de archivos MP3
  Alumno: Joaquín Torres
  Correo Electrónico: joaquintorres1997@gmail.com
  Archivo: utils.h
  Descripción: Programa que ordena un número arbitrario de archivos MP3
  por un criterio especificado por el usuario y los exporta ordenados en un 
  formato también determinado por el usuario.
  ****************************************************************/
#ifndef UTILS__H
#define UTILS__H

#include <stdio.h>
#include "types.h"

status_t strdupl(const char * s, char ** t);
int strcasecomp(const char * a, const char * b);


#endif