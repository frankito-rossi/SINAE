/*
 * listaPersonas.hpp
 *
 *  Created on: 5 nov. 2021
 *      Author: usuario_
 */
#ifndef LISTAPERSONAS_HPP_
#define LISTAPERSONAS_HPP_

#include <cstdio>
#include "persona.h"

using namespace std;

struct rep_listaPersonas;
typedef rep_listaPersonas *listaPersonas;

listaPersonas crearListaPersonas();


void insertarEnListaPersonas(persona elem, listaPersonas &lst) ;

void insertarEnListaPersonas(listaPersonas &lst, char* nombre,char* apellido,int ci,Fecha fecha_nacimiento, char* localidad);


void removerDeListaPersonas(persona elem, listaPersonas &lst) ;

bool esVaciaListaPersonas(listaPersonas lst);


bool perteneceAListaPersonas(persona elem, listaPersonas lst) ;

persona primeroEnListaPersonas(listaPersonas lst);

listaPersonas restoDeListaPersonas(listaPersonas lst) ;

void destruirListaPersonas(listaPersonas &lst) ;

persona perteneceAListaPersonasCI(int ci, listaPersonas lst);

#endif /* LISTAPERSONAS_HPP_ */
