
#ifndef PERSONA_HPP_
#define PERSONA_HPP_

#include "fecha.h"

using namespace std;

typedef struct rep_persona *persona;

persona crear_persona(char* nombre,char* apellido,int ci,Fecha fecha_nacimiento, char* localidad); //Agregar agenda

persona crear_persona(char* nombre,char* apellido,int ci, char* localidad); //Agregar agenda

persona crear_persona();

bool estaVacunado(persona x);

char* nombrePersona(persona x);

char* apellidoPersona(persona x);

int ciPersona(persona x);

char* localidadPersona(persona x);

char* ptoVacunacionPersona(persona x);

void agendarPersona(Fecha agenda,char* loc, persona &p);

Fecha fechaVacunacion(persona x);

void cancelarReserva(persona x);

#endif
