/* Cada persona es agendada en un día y hora determinada. El tiempo que le toma a
cada persona ser vacunado, es de 5 minutos para la vacuna y 30 minutos de espera. Los horarios de vacunación son, los días hábiles de 8 a 20 horas*/
// Guardas dinamico los que se vayan agendando, antes de guardar hay que chequear si existe, si no existe tira error.


#include "../include/grafoPtosVacunacion.h"

#include <stddef.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>


using namespace std;

// Cambiamos vertice_t por ptoVacunacion
typedef struct ptoVacunacion{
    Lista adyacentes;
    int grado; //aristas que salen del vertice
    char* localidad; //se identifica con el nombre de la localidad
    int cantVacunas;
    Vacunas tipoVacuna;
    Fecha *agenda;  
    int genteAgendada; // En realidad es -1
} * PuntoVacunacion;

// Se convierte en crear_puntoVacunacion()
static PuntoVacunacion crear_puntoVacunacion(char* loc) {
  PuntoVacunacion res = new ptoVacunacion;
  res->adyacentes = crear_lista(); 
  res->grado = 0;
  res->localidad = loc;
  res->cantVacunas = 0; //PARA TESTEAR
  //res->cantVacunas = 0; // Estos campos se inicializan en "cero" por que se asignan despues
  res->tipoVacuna = NULL;  
  res->genteAgendada = 1;
  res->agenda = new Fecha[res->genteAgendada];
  return res;
}

static void renombrarPuntoVacunacion(char* loc, PuntoVacunacion &p){
	//printf("renombrarPuntoVacunacion:  %s \n", loc);
	p->localidad = loc;
	//printf("renombrarPuntoVacunacion:  %s \n", p->localidad);
}

void agendar(PuntoVacunacion &p, Fecha f){
	// Primero buscamos si hay algun lugar vacio en el array

	int i;
	Fecha test = crearFecha(0,0,0,0,0);
	while( i < p->genteAgendada && p->agenda[i] != test){
			i++;
	}

	if(i == p->genteAgendada){
	    p->genteAgendada++;
	    Fecha *aux = new Fecha[p->genteAgendada];

	    for(int i = 0; i < p->genteAgendada ; i++)
	    {
	        aux[i] = p->agenda[i];
	    }
	    aux[i] = f;

	    delete[] p->agenda;
	    p->agenda = aux;
	} else {
		if(p->agenda[i] == test){
			p->agenda[i] = f;
		}
	}
}

void cancelarReserva(PuntoVacunacion &p, Fecha f){
	int i;
	while( i < p->genteAgendada && p->agenda[i] != f){
		i++;
	}
	if(p->agenda[i] == f){
		reiniciarFecha(p->agenda[i]);
		p->genteAgendada--;
	}
}

PuntoVacunacion cargarVacunas(Vacunas v, int cv, PuntoVacunacion p){
    PuntoVacunacion res = p;
	res->tipoVacuna = v; // Hay que ver si lo guarda bien o no
    res->cantVacunas = cv;
    return res;
}

static void cargarVacunasStatic(Vacunas v, int cv, PuntoVacunacion &p){
	p->tipoVacuna = v;
	p->cantVacunas = cv;
}

int cantidadVacunas(PuntoVacunacion p){
    return p->cantVacunas;
}

// Se convierte en destruir_puntoVacunacion()
void destruir_puntoVacunacion(PuntoVacunacion &p) {
  destruir_lista(p->adyacentes);// Ojo con esta funcion, tiene que tener la misma firma 
  //delete p->tipoVacuna;// Funcionara?
  delete [] p->agenda;
  delete p;
}

struct rep_grafo {
  ptoVacunacion *puntoVacunacion; // array de puntos
  int max;         // identificador de vértice más alto
  int n;           // cantidad de vértices
  int m;           // cantidad de aristas
};

void cargarVacunasSECOED(Grafo &g, Vacunas v, int cant, int resto){
    int j;
    PuntoVacunacion p;
    for(int j = 1; j <= g->max; j++){
    	//g->puntoVacunacion[j] = cargarVacunas(v, cant, &g->puntoVacunacion[j]);
    	p = &g->puntoVacunacion[j];
    	cargarVacunasStatic(v, cant, p);
    }
    	j = 1;
    while(resto != 0){
    	//g->puntoVacunacion[j] = cargarVacunas(v, cantidadVacunas(&g->puntoVacunacion[j]) + 1, &g->puntoVacunacion[j]);
        p = &g->puntoVacunacion[j];
        cargarVacunasStatic(v, cantidadVacunas(&g->puntoVacunacion[j]) + 1, p);
    	resto--;
        if(j == g->max)
            j = 1;
        else
            j++;
    }
}

Grafo crear_grafo(int max) {
  Grafo g = new rep_grafo;
  g->max = max;
  g->n = 0;
  g->m = 0;
  g->puntoVacunacion = new ptoVacunacion[max + 1]; //  la celda 0 es el sinae
  PuntoVacunacion p = crear_puntoVacunacion("SECOED");
  g->puntoVacunacion[0] = *p;
  g->puntoVacunacion[0].cantVacunas = -1;
  for (int i = 1; i <= max; i++){
	  p = crear_puntoVacunacion("");
	  g->puntoVacunacion[i] = *p;
  }

  return g;
}
int max_vertice(Grafo g) { return g->max; }

void agregar_puntoVacunacion( char* loc, Grafo &g){
	//printf("agregar_puntoVacunacion:  %s \n", loc);
    if((g->n < g->max)){
            g->n++;
            PuntoVacunacion p = &g->puntoVacunacion[g->n];
            renombrarPuntoVacunacion(loc, p);
    }
}  

bool existe_puntoVacunacion(int v, Grafo g){
    bool res = false;
	if(( 1 <= v) && (v <= g->max))
        res = true;
	return res;
}

int grado(int v, Grafo g){
    int res;
	if(existe_puntoVacunacion(v, g))
        res = g->puntoVacunacion[v].grado; // Ojo con esto
	return res;
}

Lista vertices(Grafo g) { // ke
  Lista lst = crear_lista();
  for (int i = g->max; i > 0; i--)
    if (existe_puntoVacunacion(i, g))
      insertar(i, lst);
  return lst;
}

int cantidad_vertices(Grafo g) { return g->n; }

void agregar_arista(int v1, int v2, Grafo &g) {// capaz que no va &g
  if(existe_puntoVacunacion(v1, g) && existe_puntoVacunacion(v2, g)){
    if (!pertenece_a_lista(v2, g->puntoVacunacion[v1].adyacentes)) { // ojo, misma firma lista
        g->m++;
        g->puntoVacunacion[v1].grado++;
        g->puntoVacunacion[v2].grado++;
        insertar(v2, g->puntoVacunacion[v1].adyacentes);
        if(!pertenece_a_lista(v1, g->puntoVacunacion[v2].adyacentes)){
        insertar(v1, g->puntoVacunacion[v2].adyacentes);
        }
    }
  }
}

bool existe_arista(int v1, int v2, Grafo g) {
  return pertenece_a_lista(v2, g->puntoVacunacion[v1].adyacentes);
}

int cantidad_aristas(Grafo g) { return g->m; }

Lista adyacentes(int v, Grafo g) {
  return g->puntoVacunacion[v].adyacentes;
}

void destruir_grafo(Grafo &g) {
  for (int i = 1; i <= g->max; i++)
    if (existe_puntoVacunacion(i, g)){
      	PuntoVacunacion del = &g->puntoVacunacion[i];
      	destruir_puntoVacunacion(del);
    }
  delete[] g->puntoVacunacion;
  delete g;
}

// HAY QUE CHEQUEAR QUE SALGA BIEN DEL DFS

static int DFS_buscarLocalidad(Grafo g, int vertice, bool (&visitado)[5], char* loc, int res) {

	if(res == -1){
		visitado[vertice] = true;
		Lista adjList = adyacentes(vertice, g);

		while(!es_vacia_lista(adjList) && g->puntoVacunacion[primero(adjList)].localidad != loc){
			if (!visitado[primero(adjList)])
				res = DFS_buscarLocalidad(g, primero(adjList), visitado, loc, res);
			adjList = siguiente(adjList);
		}
		if(!es_vacia_lista(adjList) && g->puntoVacunacion[primero(adjList)].localidad == loc)
			res = primero(adjList);
	}
	return res;
}

PuntoVacunacion buscar_puntoVacunacion(Grafo g, char* loc){//Si no esta, retorna null
	PuntoVacunacion res;
	bool visitado[5];
	for (int i=1; i<= g->max; i++){
		visitado[i] = false;
	}
	int pto = DFS_buscarLocalidad(g, 0, visitado, loc, -1);
	if(pto != -1)
		res = &g->puntoVacunacion[pto];
	else
		res = NULL;
	return res;
}
static int DFS_buscarLugarConVacunas(Grafo g, int vertice, bool (&visitado)[5], int res){
	printf("Entra a DFS_buscarLugarConVacunas \n");
	if(res == -1){
		visitado[vertice] = true;
		Lista adjList = adyacentes(vertice, g);

		while(!es_vacia_lista(adjList) && g->puntoVacunacion[primero(adjList)].cantVacunas == 0){
			if (!visitado[primero(adjList)])
				res = DFS_buscarLugarConVacunas(g, primero(adjList), visitado, res);
			adjList = siguiente(adjList);
		}
		if(!es_vacia_lista(adjList) && g->puntoVacunacion[primero(adjList)].cantVacunas != 0)
			res = primero(adjList);
	}
	printf("Sale de DFS_buscarLugarConVacunas = %d \n", res);
	return res;
}

bool perteneceARegion(Grafo g, char* loc){
	printf("perteneceARegion. \n");
	imprimirGrafo(g);
	bool res = false;
	int j = 1;

	printf("La localidad a compara es: %c", loc);
	for(int i = 1; i<=g->n; i++){
		//printf("%d \n", i);
		printf("La localidad es %s \n", g->puntoVacunacion[i].localidad);
		bool b = (strcmp(loc, g->puntoVacunacion[j].localidad));
		if(b){
			res = true;
		}
	}

	printf("%d", res);

/*	while(j <= g->n){
		//PuntoVacunacion p = &g->puntoVacunacion[j];
		printf("Entra al while con j = %d. \n", j);

		if(strcmp(loc, g->puntoVacunacion[j].localidad) == 0)
			res = true;
	}*/
	printf("Se va de perteneceARegion con res = %d. \n", res);
	return res;
}

PuntoVacunacion buscar_lugarConVacunas(Grafo g, char* loc){
	printf("Entra a buscar_lugarConVacunas \n");
	PuntoVacunacion res;
	bool visitado[5];
	for (int i=1; i<= g->max; i++){
		visitado[i] = false;
	}
	int comienzo;
	int j = 1;
	while( j<= g->n){
		PuntoVacunacion p = &g->puntoVacunacion[j];
		printf("loc  =  %s \n", loc);
		printf("p->localidad  =  %s \n", p->localidad);
		if(strcmp(loc, p->localidad) == 0)
			comienzo = j;
		j++;
	}
	if(g->puntoVacunacion[comienzo].cantVacunas != 0){
		res = &g->puntoVacunacion[comienzo];
	} else {
		int pto = DFS_buscarLugarConVacunas(g, comienzo, visitado, -1);
		printf("Confirmamos salida de DFS_buscarLugarConVacunas = %d \n", pto);
		if(pto != -1)
			res = &g->puntoVacunacion[pto];
		else
			res = NULL;
	}
	printf("Sale de buscar_lugarConVacunas = %s \n", res->localidad);
	return res;
}


char* localidad(Grafo g, int i){
	return g->puntoVacunacion[i].localidad;
}

char* localidad(PuntoVacunacion p){
	return p->localidad;
}

void imprimirGrafo(Grafo g){
	//printf("imprimirGrafo \n");
	for(int i = 1; i<=g->n; i++){
		//printf("%d \n", i);
		printf("La localidad es %s \n", g->puntoVacunacion[i].localidad);
	}
}
