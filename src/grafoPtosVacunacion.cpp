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

struct rep_grafo {
  ptoVacunacion *puntoVacunacion; // array de puntos
  int max;         // identificador de vértice más alto
  int n;           // cantidad de vértices
  int m;           // cantidad de aristas
};


// Se convierte en crear_puntoVacunacion()
static PuntoVacunacion crear_puntoVacunacion(char* loc) {
  PuntoVacunacion res = new ptoVacunacion;
  res->adyacentes = crear_lista(); 
  res->grado = 0;
  res->localidad = loc;
  res->cantVacunas = 0; //PARA TESTEAR
  //res->cantVacunas = 0; // Estos campos se inicializan en "cero" por que se asignan despues
  res->tipoVacuna = NULL;  
  res->genteAgendada = 0;
  res->agenda = new Fecha[res->genteAgendada];
  return res;
}

static void renombrarPuntoVacunacion(char* loc, PuntoVacunacion &p){
	//printf("renombrarPuntoVacunacion:  %s \n", loc);
	p->localidad = loc;
	//printf("renombrarPuntoVacunacion:  %s \n", p->localidad);
}

bool fechaDisponible(Grafo g, int i, Fecha f){
   bool res = true;
   PuntoVacunacion p = &g->puntoVacunacion[i];
	for(int i = 0; i < p->genteAgendada ; i++){
    	if(compararFechas(p->agenda[i], f) == 2){
    		return false; // HAY QUE ARREGLAR ESTO
    	}
    }
	return res;
}

int agendar(PuntoVacunacion &p, Fecha f){ //1 si puede agendar, -1 si no
	// Primero buscamos si hay algun lugar vacio en el array
	int res = 1;
	int i = 0;
	Fecha test = crearFecha(0,0,0,0,0);
	while( i < p->genteAgendada && p->agenda[i] != test){
			i++;
	}

	if(i == p->genteAgendada){
	    p->genteAgendada++;
	    p->cantVacunas--;
	    Fecha *aux = new Fecha[p->genteAgendada];

	    for(int i = 0; i < p->genteAgendada ; i++){
	    	aux[i] = p->agenda[i];
	    }
	    aux[i] = f;

	    //ORDENAMOS CON BUBBLE SORT
	    int k, j;
	    for (k = 0; k < p->genteAgendada-1; k++)
	        // Last i elements are already in place
	        for (j = 0; j < p->genteAgendada-k-1; j++)
	            if (compararFechas(aux[j], aux[j+1]) == 1){
		            Fecha cambio = aux[j];
		            aux[j] = aux[j+1];
		            aux[j+1] = cambio;
	            }
	    // TERMINA EL BUBBLE SORT
	    delete[] p->agenda;
	    p->agenda = aux;
	} else {
		if(p->agenda[i] == test){
			p->agenda[i] = f;
		}
	}
	return res;
}

void cancelarReserva(PuntoVacunacion &p, Fecha f){
	int i = 0;
	//	QUE PASA SI NO NADIE AGENDADO
	while( i <= p->genteAgendada && (compararFechas(p->agenda[i], f) != 0)){
		i++;
	}
	if(compararFechas(p->agenda[i], f) == 0){
	//	printf("ENTRA\n");
	//	reiniciarFecha(p->agenda[i]);
	//	printf("ENTRA\n");
		p->genteAgendada--;
		p->cantVacunas++;
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



void cargarVacunasSECOED(Grafo &g, Vacunas v, int cant, int resto){
    int j;
    PuntoVacunacion p;
   	//printf("Cargando las vacunas . . . \n");
    for(int j = 1; j <= g->max; j++){
    	//g->puntoVacunacion[j] = cargarVacunas(v, cant, &g->puntoVacunacion[j]);
    	p = &g->puntoVacunacion[j];
    	cargarVacunasStatic(v, cant, p);
        //printf("Cantidad vacunas de %s = %d. \n", g->puntoVacunacion[j].localidad, cantidadVacunas(&g->puntoVacunacion[j]));
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
	if(( 0 <= v) && (v <= g->max))
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

/*static int DFS_buscarLocalidad(Grafo g, int vertice, bool (&visitado)[5], char* loc, int res) {

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
}*/

PuntoVacunacion buscar_puntoVacunacion(Grafo g, char* loc){//Si no esta, retorna null
	PuntoVacunacion res;
	/*bool visitado[5];
	for (int i=1; i<= g->max; i++){
		visitado[i] = false;
	}
	int pto = DFS_buscarLocalidad(g, 0, visitado, loc, -1);
	if(pto != -1){
		res = &g->puntoVacunacion[pto];
		//printf("punto : %s", res->localidad);
	}
	else
		res = NULL;
	*/

	int j = 1;
	res = NULL;
	while(j<=g->n && res == NULL){
		if(g->puntoVacunacion[j].localidad == loc){
			res = &g->puntoVacunacion[j];
		}
		j++;
	}

	return res;
}

static int DFS_buscarLugarConVacunas(Grafo g, int vertice, bool (&visitado)[5], int res){
	//printf("Entra a DFS_buscarLugarConVacunas \n");
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
	//printf("Sale de DFS_buscarLugarConVacunas = %d \n", res);
	return res;
}

bool perteneceARegion(Grafo g, char* loc){
	//printf("perteneceARegion. \n");
	//imprimirGrafo(g);
	bool res = false;
	int j = 1;

	//printf("La localidad a compara es: %s \n", &loc);
	for(int i = 1; i<=g->n; i++){
		//printf("%d \n", i);
		//printf("La localidad es %s \n", g->puntoVacunacion[i].localidad);
		char* comp = loc;
		bool b = (strcmp(comp, g->puntoVacunacion[j].localidad));
		if(b){
			res = true;
		}
	}

	//printf("%d", res);

/*	while(j <= g->n){
		//PuntoVacunacion p = &g->puntoVacunacion[j];
		printf("Entra al while con j = %d. \n", j);

		if(strcmp(loc, g->puntoVacunacion[j].localidad) == 0)
			res = true;
	}*/
	//printf("Se va de perteneceARegion con res = %d. \n", res);
	return res;
}

PuntoVacunacion buscar_lugarConVacunas(Grafo g, char* loc){
	//printf("Entra a buscar_lugarConVacunas \n");
	PuntoVacunacion res;
	bool visitado[5];
	for (int i=1; i<= g->max; i++){
		visitado[i] = false;
	}
	int comienzo = -1;
	int j = 1;
	while( j<= g->n){
		PuntoVacunacion p = &g->puntoVacunacion[j];
		//printf("loc  =  %s \n", loc);
		//printf("p->localidad  =  %s \n", p->localidad);
		if(strcmp(loc, p->localidad) == 0){
			comienzo = j;
			//printf("SON IGUALES- comienzo = %d \n", comienzo);
		}

		j++;
	}
	//printf("Cantidad de vacunas comienzo = %d\n", g->puntoVacunacion[comienzo].cantVacunas);

	if(comienzo != -1 && g->puntoVacunacion[comienzo].cantVacunas != 0){
		res = &g->puntoVacunacion[comienzo];
	} else {
		int pto = DFS_buscarLugarConVacunas(g, comienzo, visitado, -1);
		//printf("Confirmamos salida de DFS_buscarLugarConVacunas = %d \n", pto);
		if(pto != -1)
			res = &g->puntoVacunacion[pto];
		else
			res = NULL;
	}
	//printf("Sale de buscar_lugarConVacunas = %s \n", res->localidad);
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

void imprimirGrafoTodaLaInfo(Grafo g, FILE &f){
	//printf("imprimirGrafo \n");
	for(int i = 1; i<=g->n; i++){
		//printf("%d \n", i);
		printf("-.-.-.-.-.-.-.-.-.-.-.-.-\n");
		printf("Localidad: %s \n", g->puntoVacunacion[i].localidad);
		printf("Laboratorio de las vacunas: %s \n", laboratorioVacuna(g->puntoVacunacion[i].tipoVacuna));
		printf("Nombre de las vacunas: %s \n", nombreVacuna(g->puntoVacunacion[i].tipoVacuna));
		printf("Fecha vencimiento de las vacunas: %d/%d/%d \n", diaFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), mesFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), anioFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)));
		printf("Cantidad de dosis en stock: %d \n", g->puntoVacunacion[i].cantVacunas);
		printf("Cantidad de personas agendadas: %d \n", g->puntoVacunacion[i].genteAgendada);

		fprintf(&f, "-.-.-.-.-.-.-.-.-.-.-.-.-\n");
		fprintf(&f, "Localidad: %s \n", g->puntoVacunacion[i].localidad);
		fprintf(&f, "Laboratorio de las vacunas: %s \n", laboratorioVacuna(g->puntoVacunacion[i].tipoVacuna));
		fprintf(&f, "Nombre de las vacunas: %s \n", nombreVacuna(g->puntoVacunacion[i].tipoVacuna));
		fprintf(&f, "Fecha vencimiento de las vacunas: %d/%d/%d \n", diaFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), mesFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), anioFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)));
		fprintf(&f, "Cantidad de dosis en stock: %d \n", g->puntoVacunacion[i].cantVacunas);
		fprintf(&f, "Cantidad de personas agendadas: %d \n", g->puntoVacunacion[i].genteAgendada);

		Lista l = adyacentes(i, g);
		if(!es_vacia_lista(l)){
			printf("A continuacion se mostraran las localidades vecinas de esta: \n");
			fprintf(&f, "A continuacion se mostraran las localidades vecinas de esta: \n");
		}
		while(!es_vacia_lista(l)){
			//imprimir_lista(l);
			//printf("Primero: %d \n", primero(l));
			printf("-  %s \n", g->puntoVacunacion[primero(l)].localidad);
			fprintf(&f, "-  %s \n", g->puntoVacunacion[primero(l)].localidad);
			l = siguiente(l);
		}
	}
}


void imprimirGrafoTodaLaInfo(Grafo g){
	//printf("imprimirGrafo \n");
	for(int i = 1; i<=g->n; i++){
		//printf("%d \n", i);
		printf("-.-.-.-.-.-.-.-.-.-.-.-.-\n");
		printf("Localidad: %s \n", g->puntoVacunacion[i].localidad);
		printf("Laboratorio de las vacunas: %s \n", laboratorioVacuna(g->puntoVacunacion[i].tipoVacuna));
		printf("Nombre de las vacunas: %s \n", nombreVacuna(g->puntoVacunacion[i].tipoVacuna));
		printf("Fecha vencimiento de las vacunas: %d/%d/%d \n", diaFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), mesFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), anioFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)));
		printf("Cantidad de dosis en stock: %d \n", g->puntoVacunacion[i].cantVacunas);
		printf("Cantidad de personas agendadas: %d \n", g->puntoVacunacion[i].genteAgendada);
		Lista l = adyacentes(i, g);
		if(!es_vacia_lista(l))
			printf("A continuacion se mostraran las localidades vecinas de esta: \n");
		while(!es_vacia_lista(l)){
			//imprimir_lista(l);
			//printf("Primero: %d \n", primero(l));
			printf("-  %s \n", g->puntoVacunacion[primero(l)].localidad);
			l = siguiente(l);
		}
	}
}

static void DFS_listaDFS(Grafo g, int vertice, bool (&visitado)[5], int (&res)[5]){

	visitado[vertice] = true;
		Lista adjList = adyacentes(vertice, g);

		while(!es_vacia_lista(adjList)){
			if (!visitado[primero(adjList)]){
				int j = 0;
				while(res[j] != -1)
					j++;
				res[j] = primero(adjList);
				DFS_listaDFS(g, primero(adjList), visitado, res);


			}
			adjList = siguiente(adjList);
		}
	//printf("Sale de DFS_buscarLugarConVacunas = %d \n", res);
}


static void listaDFS(Grafo g, int (&res)[5]){
	bool visitado[5];
	for (int i=1; i<= g->max; i++){
		visitado[i] = false;
	}

	DFS_listaDFS(g, 0, visitado, res);
	for (int k=0; k<= g->max; k++){
		//printf("%d = %d \n", k, res[k]);
	}
}

void imprimirGrafoDFS(Grafo g){
	int res[5];

	for(int j = 0; j<=5; j++)
		res[j] = -1;
	listaDFS(g, res);

	int j = 0;
	while(j<= 5){
		int i = res[j];

		if(i>0){
			printf("-.-.-.-.-.-.-.-.-.-.-.-.-\n");
			printf("Localidad: %s \n", g->puntoVacunacion[i].localidad);
			printf("Laboratorio de las vacunas: %s \n", laboratorioVacuna(g->puntoVacunacion[i].tipoVacuna));
			printf("Nombre de las vacunas: %s \n", nombreVacuna(g->puntoVacunacion[i].tipoVacuna));
			printf("Fecha vencimiento de las vacunas: %d/%d/%d \n", diaFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), mesFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)), anioFecha(fechaVencimiento(g->puntoVacunacion[i].tipoVacuna)));
			printf("Cantidad de dosis en stock: %d \n", g->puntoVacunacion[i].cantVacunas);
			printf("Cantidad de personas agendadas: %d \n", g->puntoVacunacion[i].genteAgendada);
			Lista l = adyacentes(i, g);
			if(!es_vacia_lista(l))
				printf("A continuacion se mostraran las localidades vecinas de esta: \n");
			while(!es_vacia_lista(l)){
				printf("-  %s \n", g->puntoVacunacion[primero(l)].localidad);
				l = siguiente(l);
			}
		}
		j++;
	}
}


void reporteVacunas(Grafo g, FILE &f){

	for(int i = 1; i<=g->n; i++){
		if(g->puntoVacunacion[i].cantVacunas < 10){
			fprintf(&f, "-.-.-.-.-.-.-.-.-.-.-.-.-\n");
			fprintf(&f, "Localidad: %s \n", g->puntoVacunacion[i].localidad);
			fprintf(&f, "Cantidad de dosis en stock: %d \n", g->puntoVacunacion[i].cantVacunas);
		}
	}
}
