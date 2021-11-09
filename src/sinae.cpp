#include "../include/sinae.h"
#include <cmath>


using namespace std;


struct rep_SECOED{
    char* zona;
    int stock; //cantidad de vacunas que existen
    Grafo grafo;
};
typedef rep_SECOED *SECOED;

struct rep_SINAE{
   SECOED arrSECOED[4];
};
typedef rep_SINAE *SINAE;

SINAE crear_sinae(){
    SINAE res = new rep_SINAE;
    //res->arrSECOED = new rep_SECOED[4];
    return res;
}

SINAE cargarDatos(SINAE &S){

    SECOED norte = new rep_SECOED();
    char* asignar = "norte";
    //printf("Asignar es %s \n", asignar);
    norte->zona = asignar;
    norte->stock= -1;
    norte->grafo = crear_grafo(5); // NORTE
    agregar_puntoVacunacion("Artigas", norte->grafo);// Artigas = n=1
    agregar_puntoVacunacion("Salto", norte->grafo);// Salto = n=2
    agregar_puntoVacunacion("Rivera1", norte->grafo);// induccion
    agregar_puntoVacunacion("Tacuarembo", norte->grafo);
    agregar_puntoVacunacion("Rivera2", norte->grafo);
    agregar_arista(1, 2, norte->grafo);
    agregar_arista(2, 0, norte->grafo);
    agregar_arista(3, 0, norte->grafo);
    agregar_arista(0, 4, norte->grafo);
    agregar_arista(4, 5, norte->grafo);


    SECOED sur = new rep_SECOED();
    asignar = "sur";
    //printf("Asignar es %s \n", asignar);
    sur->zona = asignar;
    sur->stock= -1;
    sur->grafo = crear_grafo(4); // NORTE
    agregar_puntoVacunacion("Durazno", sur->grafo);// vertice 1
    agregar_puntoVacunacion("Florida", sur->grafo);// vertice 2
    agregar_puntoVacunacion("SanJose", sur->grafo);// vertice 3
    agregar_puntoVacunacion("Canelones", sur->grafo);// vertice 4
    agregar_arista(0, 1, sur->grafo);
    agregar_arista(0, 2, sur->grafo);
    agregar_arista(0, 3, sur->grafo);
    agregar_arista(1, 3, sur->grafo);
    agregar_arista(3, 4, sur->grafo);

    SECOED este = new rep_SECOED();
    asignar = "este";
    //printf("Asignar es %s \n", asignar);
    este->zona = asignar;
    este->stock= -1;
    este->grafo = crear_grafo(4); // este
    agregar_puntoVacunacion("CerroLargo", este->grafo);// Vertice 1
    agregar_puntoVacunacion("TreintayTres", este->grafo);// Vertice 2
    agregar_puntoVacunacion("Lavalleja", este->grafo);// Vertice 3
    agregar_puntoVacunacion("Rocha", este->grafo);//Vertice 4
    agregar_arista(1, 3, este->grafo);
    agregar_arista(2, 4, este->grafo);
    agregar_arista(3, 4, este->grafo);
    agregar_arista(0, 3, este->grafo);
    agregar_arista(0, 4, este->grafo);

    SECOED oeste = new rep_SECOED();
    asignar = "oeste";
    //printf("Asignar es %s \n", asignar);
    oeste->zona = asignar;
    oeste->stock= -1;
    oeste->grafo = crear_grafo(5); // oeste
    agregar_puntoVacunacion("Paysandu", oeste->grafo);// Artigas = n=1
    agregar_puntoVacunacion("RioNegro", oeste->grafo);// Salto = n=2
    agregar_puntoVacunacion("Soriano", oeste->grafo);// induccion
    agregar_puntoVacunacion("Flores", oeste->grafo);
    agregar_puntoVacunacion("Colonia", oeste->grafo);
    agregar_arista(1, 3, oeste->grafo);
    agregar_arista(1, 0, oeste->grafo);
    agregar_arista(2, 4, oeste->grafo);
    agregar_arista(0, 4, oeste->grafo);
    agregar_arista(0, 5, oeste->grafo);
 
    S->arrSECOED[0] = norte;
    S->arrSECOED[1] = sur;
    S->arrSECOED[2] = este;
    S->arrSECOED[3] = oeste;
    
    //printf("Se ingresaron todos las localidades y zonas. \n", S->arrSECOED[0]);
    for(int i=0; i<= 3; i++){
    	//printf("ALGO %d \n", i);
    	//printf("La region es %s \n", S->arrSECOED[i]->zona);
    	Grafo g = S->arrSECOED[i]->grafo;
    	imprimirGrafo(g);
    }


    return S;
 }

 SINAE cargar_vacunas(SINAE &S, Vacunas v, int cantV, int i){ // i es la region

     //ESTAMOS PARADOS EN LA REGION A LA QUE LE QUEREMOS ENVIAR LAS VACUNAS, arrSECOED[i], tenemos que dividir la cantidad de vacunas entre las localidades y entregar
     int vacunasARepartir;
     int resto;
     if(i == 0 || i == 3){
         vacunasARepartir = trunc(cantV/5);
         resto = cantV - (vacunasARepartir * 5);
     }
    if(i == 2 || i == 3){
        vacunasARepartir = trunc(cantV/4);
        resto = cantV - (vacunasARepartir * 5);
    }

    cargarVacunasSECOED(S->arrSECOED[i]->grafo, v, vacunasARepartir, resto);

 return S;
 }

 // Busca el lugar mas cercano con vacunas, en ese lugar guarda la fecha y retorna el nombre de la localidad
 char* agendar(SINAE &S, Fecha f, int regU, int locU){
	 char* res = "";

	 int i = 0;
	 //printf("Antes de perteneceARegion  \n");
	 bool flag = true;
	/*while(flag){
		Grafo g = S->arrSECOED[i]->grafo;
		flag = !(perteneceARegion(g, locPersona));
		i++;
	}*/
	PuntoVacunacion p = buscar_lugarConVacunas(S->arrSECOED[regU]->grafo, localidad(S->arrSECOED[regU]->grafo, locU));
	res = localidad(p);
	agendar(p, f);
	 //printf("Sale del agendar \n");
	 return res;
 }

 void cancelarReserva(SINAE &S, char* locReserva, Fecha f){
	 int i = 0;
	 while(i<4){
		 PuntoVacunacion p = buscar_puntoVacunacion(S->arrSECOED[i]->grafo, locReserva);
		 if(p == NULL)
			 i++;
		 else {
			cancelarReserva(p, f);
		 }
	 }
 }


 char* localidad(SINAE S, int reg, int loc){
	 return localidad(S->arrSECOED[reg]->grafo, loc);
 }
