/*
 * sinae.hpp
 *
 *  Created on: 5 nov. 2021
 *      Author: usuario_
 */

#ifndef SINAE_HPP_
#define SINAE_HPP_

#include "sinae.h"

#include "grafoPtosVacunacion.h"
#include "vacunas.h"

using namespace std;

struct rep_SECOED;
typedef rep_SECOED *SECOED;

struct rep_SINAE;
typedef rep_SINAE *SINAE;


SINAE crear_sinae();

SINAE cargarDatos(SINAE &S);
SINAE cargar_vacunas(SINAE &S, Vacunas v, int cantV, int region);

// Busca el lugar mas cercano con vacunas, en ese lugar guarda la fecha y retorna el nombre de la localidad
char* agendar(SINAE &S, Fecha f, int regU, int locU);

void cancelarReserva(SINAE &S, char* locReserva, Fecha f);

char* localidad(SINAE S, int reg, int loc);

#endif /* SINAE_HPP_ */
