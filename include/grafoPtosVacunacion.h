/*
 * grafoPtosVacunacion.h
 *
 *  Created on: 5 nov. 2021
 *      Author: usuario_
 */

#ifndef GRAFOPTOSVACUNACION_H_
#define GRAFOPTOSVACUNACION_H_

#include "fecha.h"
#include "lista.h"
#include "vacunas.h"

using namespace std;



// Cambiamos vertice_t por ptoVacunacion
struct ptoVacunacion;
typedef ptoVacunacion *PuntoVacunacion;

// Se convierte en crear_puntoVacunacion()
static PuntoVacunacion crear_puntoVacunacion(char* loc);

void agendar(PuntoVacunacion &p, Fecha f);

void cancelarReserva(PuntoVacunacion &p, Fecha f);

PuntoVacunacion cargarVacunas(Vacunas v, int cv, PuntoVacunacion p);
int cantidadVacunas(PuntoVacunacion p);

// Se convierte en destruir_puntoVacunacion()
static void destruir_puntoVacunacion(PuntoVacunacion &p);

struct rep_grafo ;
typedef rep_grafo *Grafo;

void cargarVacunasSECOED(Grafo &g, Vacunas v, int cant, int resto);

Grafo crear_grafo(int max);
int max_vertice(Grafo g);

void agregar_puntoVacunacion( char* loc, Grafo &g);

bool existe_puntoVacunacion(int v, Grafo g);

int grado(int v, Grafo g);

Lista vertices(Grafo g) ;


int cantidad_vertices(Grafo g);

void agregar_arista(int v1, int v2, Grafo &g) ;

bool existe_arista(int v1, int v2, Grafo g);

int cantidad_aristas(Grafo g);

Lista adyacentes(int v, Grafo g) ;

void destruir_grafo(Grafo &g);

PuntoVacunacion buscar_puntoVacunacion(Grafo g, char* loc);//Si no esta, retorna null

bool perteneceARegion(Grafo g, char* loc);

PuntoVacunacion buscar_lugarConVacunas(Grafo g, char* loc);

char* localidad(Grafo g, int i);

char* localidad(PuntoVacunacion p);

void destruir_puntoVacunacion(PuntoVacunacion &p);

void imprimirGrafo(Grafo g);


#endif /* GRAFOPTOSVACUNACION_H_ */
