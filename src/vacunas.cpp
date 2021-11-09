#include "../include/vacunas.h"

using namespace std;



struct rep_vacuna{
    char* laboratorio;
    char* nombre;
    Fecha fecha_vencimiento;
};

typedef rep_vacuna *Vacuna;

Vacunas cargar_vacunas( char* laboratorio, char* nombre, Fecha fv){
    //Creamos el nodo con la información del lote.
    Vacuna nuevo= new rep_vacuna;
    nuevo->laboratorio=laboratorio;
    nuevo->nombre=nombre;
    nuevo->fecha_vencimiento=fv;   
    return nuevo;
}

void eliminar_nodo(Vacuna x){
        //eliminar_fecha(x->fecha_vencimiento);
        delete x;
    }

char* nombreVacuna(Vacuna x){
    return x->nombre;
}
