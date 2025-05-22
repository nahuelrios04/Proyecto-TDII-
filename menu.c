/* TRABAJO PRACTICO FINAL TECNICAS DIGITALES II
 * 
 * 	ARCHIVO: menu.c
 * 	ALUMNOS: Cerutti, Julian.	    Legajo: 79278
 * 		     Rios, Nahuel.		    Legajo: 75502
 * 		     Villa, Federico.	    Legajo: 88722
 * 		     Zangheri, Agustin      Legajo: 81920
 * 
 * 	VERSION: 3.0	
 * 	PENDIENTES:	# Terminar protocolos modo remoto.
 * 			
*/
///////////LIBRERIAS///////////
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <stdarg.h>
#include "password.h"
#include "menu.h"
#include "serial.h"
#include "Secuencias.h"

////////VARIABLES GLOBALES/////
extern volatile int runnig;
extern int remote_mode;
extern SecuenciaMenu secuencias[];

////DEFINICION DE FUNCIONES//////
void mostrar_menu_secuencias()
{
    system("clear");
    printf("-----------------------------------\n");
    printf("=== CONTROL DEL SECUENCIAS LED ===\n");
    printf("-----------------------------------\n");
    printf("=== MODO REMOTO [%s]===\n",get_remote_mode());

    for (int i = 0; i < NUM_SECUENCIAS; i++)
    {
        printf("%d. %s\n", secuencias[i].id, secuencias[i].nombre);
    }
    printf("9. Activar/Desactivar Modo remoto\n");
    printf("\n0. Salir\n");
    printf("-----------------------------------\n");
    printf("Seleccione una opcion (0-9): ");
    fflush(stdout);
    fflush(stdin);
    
}

void mostrar_menu_remoto(void)
{

    system("clear");
    printf("-----------------------------------\n");
    printf("=== CONTROL DEL SECUENCIAS LED ===\n");
    printf("-----------------------------------\n");
    printf("========== MODO REMOTO ===========\n");

    for (int i = 0; i < NUM_SECUENCIAS; i++)
    {
        printf("%d. %s\n", secuencias[i].id, secuencias[i].nombre);
    }
}
