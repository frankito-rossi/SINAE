#include "../include/persona.h"
#include "../include/fecha.h"
#include <cstdio>


struct rep_persona{
    char* nombre;
    char* apellido;
    int ci;
    Fecha fecha_nacimiento;
    char* localidad;
    int region;
   // bool vacunado;
    Fecha fecha_reserva;
    char* localidad_reserva;
    //agregar vertice(punto de vacunacion)
    //Falta guardar donde se vacuna.
};

persona crear_persona(char* nombre,char* apellido,int ci,Fecha fecha_nacimiento, char* localidad){
    persona nueva = new rep_persona;
    
    nueva->nombre=nombre;
    nueva->apellido=apellido;
    nueva->ci=ci;
    nueva->fecha_nacimiento=fecha_nacimiento;
    nueva->localidad=localidad;
   // nueva->vacunado=false;//bool chequearVacuna(char*ci)
    
    return nueva;
}

persona crear_persona(char* nombre,char* apellido,int ci, char* localidad){
    persona nueva = new rep_persona;

    nueva->nombre=nombre;
    nueva->apellido=apellido;
    nueva->ci=ci;
    nueva->localidad=localidad;
   // nueva->vacunado=false;//bool chequearVacuna(char* ci)

    return nueva;
}


/*bool estaVacunado(persona x){
    return x->vacunado;
}*/

char* nombrePersona(persona x){
    return x->nombre;
}

char* apellidoPersona(persona x){
    return x->apellido;
}

int ciPersona(persona x){
    return x->ci;
}

char* localidadPersona(persona x){
    return x->localidad;
}

char* ptoVacunacionPersona(persona x){
	return x->localidad_reserva;
}

void agendarPersona(Fecha agenda,char* loc, persona &p){
	//imprimirFecha(agenda);
	p->fecha_reserva = agenda;
	//imprimirFecha(p->fecha_reserva);
	//printf("agendarPersona en : %s \n", loc);
	p->localidad_reserva = loc;
	//printf("agendarPersona en : %s \n", p->localidad_reserva);
}


Fecha fechaVacunacion(persona x){
	return x->fecha_reserva;
}

void cancelarReserva(persona x){
	reiniciarFecha(x->fecha_reserva);
	x->localidad_reserva = "";
}
