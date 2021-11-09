#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "include/fecha.h"
#include "include/listaPersonas.h"
#include "include/persona.h"
#include "include/sinae.h"
#include "include/vacunas.h"

int main(){
    /* CARGAR DATOS DEL GRAFO DEL SINAE */
	//testLista(); //Parece que la lista funciona bien

	SINAE S = crear_sinae();
	S = cargarDatos(S);


	Fecha fVacuna = crearFecha(8, 11, 2022, 11, 54);
	Vacunas vn = cargar_vacunas( "Uruguayser", "Lavacuna", fVacuna);
	S = cargar_vacunas(S, vn, 15, 0);// Esta funcion no esta funcionando del todo
	S = cargar_vacunas(S, vn, 15, 1);
	S = cargar_vacunas(S, vn, 15, 2);
	S = cargar_vacunas(S, vn, 15, 3);
    
	listaPersonas lPersonas = crearListaPersonas();

    
    int n, opcion, subopcion;
    
    do{
    	printf("Bienvenido al gestor de vacunación.\n");
        printf("Seleccione el tipo de usuario:\n");
        printf("1. Usuario.\n");
        printf("2. Administrador.\n");
        printf("0. Salir.\n");
        printf( "\n   Introduzca opci%cn: ");

        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                printf("MENÚ DE USUARIO\n");
                printf("Seleccione la opción que desea ejecutar:\n");
                
                printf("1. Agendarse.\n");
                printf("2. Consulta de reserva.\n");
                printf("3. Cancelar reserva.\n");
                printf("0. Salir.\n");

                scanf("%d",&subopcion);
                switch(subopcion){
                    case 1:{
//Reserva fecha y hora en un punto de vacunación para una persona, envia un mensaje a la persona.
                        //char* = scanf("%");
                        printf("Ingrese su nombre.\n");
                        char* nombreU;
                        scanf("%s", &nombreU);
                        //nombreU = "franco";

                        printf("Ingrese su apellido.\n");
                        char* apellidoU;
                        scanf("%s", &apellidoU);
                        //apellidoU = "rossi";

                        printf("Ingrese su ci.\n");
                        int ciU;
                        scanf("%d", &ciU);
                        //ciU = 47443261;

                        printf("Ingrese su fecha de nacimiento, siguiendo el formato DD/MM/AAAA hh:mm separados con un espacio. \n");
                        int diaU,mesU,anioU,horaU,minutoU;
                        scanf("%d %d %d %d %d", &diaU, &mesU, &anioU, &horaU,&minutoU);
                        //diaU = 20;
                        //mesU = 11;
                        //anioU = 1996;
                        //horaU = 16;
                        //minutoU = 56;
                        Fecha fU = crearFecha(diaU, mesU, anioU, horaU, minutoU);

                        /*printf("Ingrese su localidad de residencia. Las opciones son: Artigas, Salto, Rivera1, Rivera2, Tacuarembo, Paysandu, RioNegro, Soriano, Flores, Colonia, Durazno, Florida, SanJose, Canelones, CerroLargo, TreintayTres, Lavalleja, Rocha.\n");
                        char* localidadU;
                        scanf("%s", &localidadU);*/

                        int regU;
                        int locU;

                        printf("Ingrese el numero correspondiente a su region: 1 - norte, 2 - sur, 3 - este, 4 - oeste.\n");
                        scanf("%d",&regU);// ojo, la region es regU - 1

                        switch(regU){
                        	case 1: {
                        		 printf("Ingrese el numero correspondiente a su localidad: 1 - Artigas, 2 - Salto, 3 - Rivera1, 4 - Tacuarembo, 5 - Rivera2.\n");
                        		 scanf("%d",&locU);
                        		 break;
                        	}
                        	case 2: {
                        		 printf("Ingrese el numero correspondiente a su localidad: 1 - Durazno, 2 - Florida, 3 - SanJose, 4 - Canelones.\n");
                        		 scanf("%d",&locU);
                        		 break;
                        	}
                        	case 3: {
                        		 printf("Ingrese el numero correspondiente a su localidad: 1 - CerroLargo, 2 - TreintayTres, 3 - Lavalleja, 4 - Rocha.\n");
                        		 scanf("%d",&locU);
                        		 break;
                        	}
                        	case 4: {
                        		 printf("Ingrese el numero correspondiente a su localidad: 1 - Paysandu, 2 - RioNegro, 3 - Soriano, 4 - Flores, 5 - Colonia.\n");
                        		 scanf("%d",&locU);
                        		 break;
                        	}
                        	break;

                        }
                        regU--;
                        char* localidadU = localidad(S, regU, locU);

                        //localidadU = "Salto";

                        //persona usuario = crear_persona(nombreU, apellidoU, ciU, crearFecha(diaU, mesU, anioU, horaU, minutoU), localidadU);
                        //persona usuario1 = crear_persona(nombreU, apellidoU, ciU, fU, localidadU);
                        //insertarEnListaPersonas(usuario, lPersonas);

                        insertarEnListaPersonas(lPersonas, nombreU, apellidoU, ciU, fU, localidadU);
                        persona usuario = perteneceAListaPersonasCI(ciU, lPersonas);

                        printf("Ingrese la fecha en la que desea vacunarse, siguiendo el formato DD/MM/AAAA hh:mm separados con un espacio. \n");
                        int dia,mes,anio,hora,minuto;
                        //dia = 2;
                        //mes = 2;
                        //anio = 2;
                        //hora = 2;
                        //minuto = 2;
                        scanf("%d %d %d %d %d", &dia, &mes, &anio, &hora, &minuto);
                        Fecha f = crearFecha(dia,mes,anio,hora,minuto);

                        char* locAgenda = agendar(S, f, regU, locU);
                        // DESPUES EN LA PERSONA A AGENDAR LO QUE HAY QUE HACER ES AGENDAR LA FECHA Y LA LOCALIDAD QUE DEVUELVE LA OTRA FUNCION

                        agendarPersona(f,locAgenda, usuario);

                        break;
                }
                    case 2:{
//mediante la CI te dice la fecha, hora y lugar a vacunarse

                    	printf("Ingrese su ci.\n");
                    	int ciCR;
                    	scanf("%d", &ciCR);
                    	//ciCR = 47443261;

                    	persona pCR = perteneceAListaPersonasCI(ciCR, lPersonas);
                        if(pCR != NULL){
                        	int diaP, mesP, anioP, horaP, minutoP;
                        	diaP = diaFecha(fechaVacunacion(pCR));
                        	mesP= mesFecha(fechaVacunacion(pCR));
                        	anioP = anioFecha(fechaVacunacion(pCR));
                        	horaP = horaFecha(fechaVacunacion(pCR));
                        	minutoP = minutoFecha(fechaVacunacion(pCR));
                        	char * locImp = ptoVacunacionPersona(pCR);
                        	printf("SE ROMPE ACA?: %s \n", locImp);
                        	printf("Su lugar de vacunacion es: %s. El dia: %d/%d/%d - %d:%d \n", locImp, diaP, mesP, anioP, horaP, minutoP );
                        }else{
                        	printf("Usted ingreso una CI que no esta agendada en el sistema.\n");
                        }
                        break;
                    }
                    case 3:{
                        // Cancelar Reserva
                    	printf("Ingrese su ci.\n");
                    	int ciCRv;
                    	scanf("%d", &ciCRv);

                    	persona pCRv = perteneceAListaPersonasCI(ciCRv, lPersonas);
                        if(pCRv != NULL){
                        	cancelarReserva(S, ptoVacunacionPersona(pCRv), fechaVacunacion(pCRv));
                        	cancelarReserva(pCRv);
                        	removerDeListaPersonas(pCRv, lPersonas) ;
                        }else{
                        	printf("Usted ingreso una CI que no esta agendada en el sistema.\n");
                        }
                        break;
                    }
                    case 0: break;
                        
                }
                break;

            case 2:
                printf("MENÚ DE ADMINISTRADOR\n");
                printf("Seleccione la opción que desea ejecutar:\n");

                printf("1. Grafo SINAE.\n");
                printf("2. Reporte SECOED.\n");
                printf("3. Subgrafo SECOED.\n");
                printf("4. Subgrafo SECOED.\n");
                printf("0. Salir.\n");

                scanf("%d",&subopcion);
                switch(subopcion){
                    case 1:
//Despliega el grafo del SINAE con sus SECOED y los puntos de vacunación.
                        //
                        break;
                    case 2:
//Despliega la información de un SECOED., genera informe, manda mail.
                        break;
                    case 3:
//El sistema deberá emitir un subgrafo inducido por los puntos de vacunación a visitar, correspondiente a un SECOED.
                        break;
                    case 4:
                        break;
                    case 0:
                        break;
                }
                break;

    }} while (opcion!=0);
    

    

    return 1;
}
