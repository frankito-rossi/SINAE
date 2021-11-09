#include "../include/fecha.h"
#include <cstdio>

struct rep_fecha{
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
};

Fecha crearFecha(int dia, int mes, int anio, int hora, int minuto){
    Fecha res = new rep_fecha;
    res->dia = dia;
    res->mes = mes;
    res->anio = anio;
    res->hora = hora;
    res->minuto = minuto;

    return res;
}

bool esBisiesto(int a){
    return (((a % 4 == 0 && a % 100 != 0) || a % 400 == 0));
}

bool validarFecha(Fecha x){
    unsigned int arrayDiasMes[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if (x->anio<=2020){
        //"El anio ingresado debe ser mayor a 2020."
        return false;
    } 
    if (x->dia<=0||x->dia>31) return false;
    if (x->mes<=0||x->mes>12) return false;
    if (x->dia>arrayDiasMes[x->mes-1]) return false;
    if (x->mes==2 && x->dia==29 && !esBisiesto(x->anio)) return false;
    return true;
}


int diaFecha(Fecha f){return f->dia;}
int mesFecha(Fecha f){return f->mes;}
int anioFecha(Fecha f){return f->anio;}
int horaFecha(Fecha f){return f->hora;}
int minutoFecha(Fecha f){return f->minuto;}

void reiniciarFecha(Fecha f){
	f->dia = 0;
	f->mes = 0;
	f->anio = 0;
	f->hora = 0;
	f->minuto = 0;
}

void imprimirFecha(Fecha f){
	printf("Fecha = %d/%d/%d - %d:%d \n", f->dia, f->mes, f->anio, f->hora, f->minuto);
}
