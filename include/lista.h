/*
 * lista.h
 *
 *  Created on: 5 nov. 2021
 *      Author: usuario_
 */
#include <cstdio>

#ifndef LISTA_H_
#define LISTA_H_



struct rep_lista ;
typedef rep_lista *Lista;


Lista crear_lista() ;
void insertar(int elem, Lista &lst);

void remover(int elem, Lista &lst) ;
bool es_vacia_lista(Lista lst);

bool pertenece_a_lista(int elem, Lista lst);

int primero(Lista lst);

Lista siguiente(Lista lst) ;
void destruir_lista(Lista &lst) ;

void imprimir_lista(Lista lst);

void testLista();

#endif /* LISTA_H_ */
