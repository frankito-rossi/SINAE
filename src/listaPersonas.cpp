#include "../include/listaPersonas.h"


using namespace std;


struct rep_listaPersonas {
  persona pers;
  rep_listaPersonas *sig;
};

listaPersonas crearListaPersonas() {
	listaPersonas res = new rep_listaPersonas;
	res->sig = NULL;
	return res;
}
/*
static void imprimir_lista(listaPersonas lst) {
  while (!esVaciaListaPersonas(lst)) {
    printf("%d ", ciPersona(primeroEnListaPersonas(lst)));
    lst = restoDeListaPersonas(lst);
  }
  printf(".");
}*/

void insertarEnListaPersonas(persona elem, listaPersonas &lst) {
  rep_listaPersonas *cursor = lst;

  while ((cursor->sig != NULL) && (ciPersona(elem) > ciPersona(cursor->sig->pers))) {
    cursor = cursor->sig;
  }
  if ((cursor->sig == NULL) || (ciPersona(elem) < ciPersona(cursor->sig->pers))) {
    rep_listaPersonas *nuevo = new rep_listaPersonas;
    nuevo->pers = elem;
    nuevo->sig = cursor->sig;
    cursor->sig = nuevo;
  } // else ya está elem en lst, no se hace nada

}

void insertarEnListaPersonas(listaPersonas &lst, char* nombre,char* apellido,int ci,Fecha fecha_nacimiento, char* localidad){
	//persona p = crear_persona(nombre, apellido, ci, fecha_nacimiento, localidad);
	persona p = crear_persona(nombre, apellido, ci, localidad);
	insertarEnListaPersonas(p, lst);
}

void removerDeListaPersonas(persona elem, listaPersonas &lst) {
  rep_listaPersonas *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->pers)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig != NULL) && (elem == cursor->sig->pers)) {
    rep_listaPersonas *aborrar = cursor->sig;
    cursor->sig = cursor->sig->sig;
    delete aborrar;
  } // else no está elem en lst, no se hace nada
}


bool esVaciaListaPersonas(listaPersonas lst) { return (lst->sig == NULL); }



bool perteneceAListaPersonas(persona elem, listaPersonas lst) {

	if(ciPersona(elem) == -1){
		return false;
	}else{
		rep_listaPersonas *cursor = lst;
		while ((cursor->sig != NULL) && (elem > cursor->sig->pers)) {
			printf("Problema \n");
			cursor = cursor->sig;
		}
		printf("Problema \n");
		printf("%d \n", (elem == cursor->sig->pers));
		printf("Problema \n");
		return ((cursor->sig != NULL) && (elem == cursor->sig->pers));
	}
}

persona primeroEnListaPersonas(listaPersonas lst) {
    persona res = NULL;
	if(!esVaciaListaPersonas(lst))
        res = lst->sig->pers;
	return res;
}

listaPersonas restoDeListaPersonas(listaPersonas lst) {
    listaPersonas res = NULL;
	if(!esVaciaListaPersonas(lst))
        res = lst->sig;
	return res;
}

void destruirListaPersonas(listaPersonas &lst) {
  while (lst != NULL) {
    rep_listaPersonas *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}
//CHEQUEAR ESTA FUNCION
persona perteneceAListaPersonasCI(int CI, listaPersonas lst) {
//printf("Entra a perteneceAListaPersonasCI \n");
/*	printf("lista :\n");
		imprimir_lista(lst);*/
  rep_listaPersonas *cursor = lst;
  persona res = NULL;
  while ((cursor->sig != NULL) && (CI > ciPersona(cursor->sig->pers))) {
    cursor = cursor->sig;
  }
  if((cursor->sig != NULL) && (CI == ciPersona(cursor->sig->pers))){
	  res = cursor->sig->pers;
  } else {
	  res = crear_persona("nombre","",-1, ""); // Persona ficticia, equivale a false
  }
  //printf("Sale de perteneceAListaPersonasCI \n");
  return (res);

}
