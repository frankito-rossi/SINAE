
#include "../include/lista.h"


struct rep_lista {
  int id;
  rep_lista *sig;
};

Lista crear_lista() {
  Lista res = new rep_lista;
  res->sig = NULL;
  return res;
}

/*Lista copia_lista(Lista lst) {
  Lista res = new rep_lista;
  Lista ultimo = res;
  while (lst->sig != NULL) {
    lst = lst->sig;
    ultimo->sig = new rep_lista;
    ultimo = ultimo->sig;
    ultimo->elem = lst->elem;
  }
  ultimo->sig = NULL;
  return res;
}*/

void insertar(int elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->id)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig == NULL) || (elem < cursor->sig->id)) {
    rep_lista *nuevo = new rep_lista;
    nuevo->id = elem;
    nuevo->sig = cursor->sig;
    cursor->sig = nuevo;
  } // else ya está elem en lst, no se hace nada
}

void remover(int elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->id)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig != NULL) && (elem == cursor->sig->id)) {
    rep_lista *aborrar = cursor->sig;
    cursor->sig = cursor->sig->sig;
    delete aborrar;
  } // else no está elem en lst, no se hace nada
}

bool es_vacia_lista(Lista lst) { return (lst->sig == NULL); }

bool pertenece_a_lista(int elem, Lista lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->id)) {
    cursor = cursor->sig;
  }
  return ((cursor->sig != NULL) && (elem == cursor->sig->id));
}

int primero(Lista lst) {
	int res = 0;
	if(!es_vacia_lista(lst))
		res = lst->sig->id;
	return res;
}

Lista siguiente(Lista lst) {
	Lista res;
	if(!es_vacia_lista(lst))
		res = lst->sig;
	return res;
}

void destruir_lista(Lista &lst) {
  while (lst != NULL) {
    rep_lista *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}

void imprimir_lista(Lista lst) {
  while (!es_vacia_lista(lst)) {
    printf("%d ", primero(lst));
    lst = siguiente(lst);
  }
  printf(".");
}

void testLista(){
	printf("Test Lista. \n");
	Lista l = crear_lista();
	insertar(4, l);
	insertar(1, l);
	printf("Se inserto el 4 y el 1. \n");

	printf("2 pertenece a la lista ? %d \n",pertenece_a_lista(2,l));
	printf("4 pertenece a la lista ? %d \n",pertenece_a_lista(4,l));
	printf("3 pertenece a la lista ? %d \n",pertenece_a_lista(3,l));
	printf("1 pertenece a la lista ? %d \n",pertenece_a_lista(1,l));
	printf("La lista es :  \n");
	imprimir_lista(l);
	insertar(3, l);
	insertar(5, l);
	printf("Se inserto el 3 y el 5. \n");
	printf("La lista es :  \n");
	imprimir_lista(l);
}
