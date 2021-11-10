
#ifndef VACUNAS_HPP_
#define VACUNAS_HPP_


#include "fecha.h"

using namespace std;


struct rep_vacuna;

typedef rep_vacuna *Vacunas;
/*
colaVacuna crear_cola();

bool estaVacia(colaVacuna x);

void cargar_vacunas(colaVacuna x, int lote, char *laboratorio, char *tipo, fecha fv, int stock);

//Reduce en 1 el stock de vacunas.
void dar_vacuna(colaVacuna x);

void eliminar_nodo(colaVacuna x);
*/

Vacunas cargar_vacunas( char* laboratorio, char* nombre, Fecha fv);

char* laboratorioVacuna(Vacunas v);
char* nombreVacuna(Vacunas v);
Fecha fechaVencimiento(Vacunas v);

void eliminar_nodo(Vacunas x);

#endif
