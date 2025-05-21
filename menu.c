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
int mostrar_menu_secuencias()
{
    int opc = -1;

    while (1) 
    {
        //si modo remoto activado envia M1
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

        if (scanf("%d", &opc) == 1)
        {
            if (opc > 0 && opc <= NUM_SECUENCIAS)
            {
                printf("Eligio la secuencia %s\n", secuencias[opc - 1].nombre);
                return opc;
            }else if(opc == 9)
            {
                if(remote_mode)
                {
                    set_remote_mode(0);
                    break;
                }else
                { 
                    set_remote_mode(1);
                    break;
                }
            }else if(opc == 0)
            {
                return 0;
            }else return -1;
        }else return -1;
        printf("Opcion invalida. Intente nuevamente.\n");
        sleep(1);
    }
    return -1;
}

void mostrar_menu_remoto(void)
{
   while (1) 
    {
        serial_send("M1");
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
}
