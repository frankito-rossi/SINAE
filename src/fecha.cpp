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

Fecha editarFecha(Fecha &res, int dia, int mes, int anio, int hora, int minuto){

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

bool validarFechaReserva(Fecha x){
    unsigned int arrayDiasMes[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if (x->anio<=2020){
        //"El anio ingresado debe ser mayor a 2020."
        return false;
    }
    if (x->dia<=0||x->dia>31) return false;
    if (x->mes<=0||x->mes>12) return false;
    if (x->dia>arrayDiasMes[x->mes-1]) return false;
    if (x->mes==2 && x->dia==29 && !esBisiesto(x->anio)) return false;
    if(x->hora<8 || x->hora>20) return false;
    if(x->minuto<00 || x->minuto>59) return false;
    return true;
}

bool validarFecha(Fecha x){
    unsigned int arrayDiasMes[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if (x->anio<=1900){
        //"El anio ingresado debe ser mayor a 2020."
        return false;
    } 
    if (x->dia<=0||x->dia>31) return false;
    if (x->mes<=0||x->mes>12) return false;
    if (x->dia>arrayDiasMes[x->mes-1]) return false;
    if (x->mes==2 && x->dia==29 && !esBisiesto(x->anio)) return false;
    if(x->hora<00 || x->hora>23) return false;
    if(x->minuto<00 || x->minuto>59) return false;
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

int compararFechas(Fecha f, Fecha g){ // Si f > g return 1, si f<g return -1, si f=g return 0, si los minutos difieren en menos de 5 return 2
	if((f->anio == g->anio) && (f->mes == g->mes) && (f->dia == g->dia) && (f->hora == g->hora) && (f->minuto == g->minuto))
		return 0;

	if((f->anio == g->anio) && (f->mes == g->mes) && (f->dia == g->dia)){
		//printf("f->min = %d \ng->min = %d \n",f->minuto, g->minuto );
		if((f->hora == g->hora) && (f->minuto < g->minuto+5) && (f->minuto+5 > g->minuto)){
			//printf("Sale con 2\n");
			return 2;}
		if((f->minuto > 55) && (f->hora+1 == g->hora) && (g->minuto < f->minuto+5-60))
			return 2;
		if((g->minuto > 55) && (g->hora+1 == f->hora) && (f->minuto < g->minuto+5-60))
			return 2;
	}
	if(f->anio > g->anio){return 1;}
	if(f->anio < g->anio){return -1;}
	if(f->mes > g->mes){return 1;}
	if(f->mes < g->mes){return -1;}
	if(f->dia > g->dia){return 1;}
	if(f->dia < g->dia){return -1;}
	if(f->hora > g->hora){return 1;}
	if(f->hora < g->hora){return -1;}
	// FALTA CUANDO UNA HORA ES POR EJ 17:58 Y LA OTRA 18:00
	if((f->minuto < g->minuto+5) && (f->minuto+5 > g->minuto)){return 2;}
	return 0;
}
