
#ifndef FECHA_HPP_
#define FECHA_HPP_

typedef struct rep_fecha *Fecha;

Fecha crearFecha(int dia, int mes, int anio, int hora, int minuto);

bool esBisiesto(int a);


bool validarFecha(Fecha x);

int diaFecha(Fecha f);
int mesFecha(Fecha f);
int anioFecha(Fecha f);
int horaFecha(Fecha f);
int minutoFecha(Fecha f);

void reiniciarFecha(Fecha f);

void imprimirFecha(Fecha f);


#endif
