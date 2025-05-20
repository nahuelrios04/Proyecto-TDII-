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
        system("clear");
        printf("-----------------------------------\n");
        printf("=== CONTROL DEL SECUENCIAS LED ===\n");
        printf("-----------------------------------\n");
        printf("=== MODO REMOTO [%s]===\n",get_remote_mode());

        for (int i = 0; i < NUM_SECUENCIAS; i++) {
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
            }else if(opc == 0) return 0;
        }
        printf("Opcion invalida. Intente nuevamente.\n");
        sleep(1);
    }
}

/*
void actualizar_estado(const char* formato) 
{

    char buffer[100];
    va_list args;
    va_start(args,formato);
    vsnprintf(buffer,sizeof(buffer),formato,args);
    va_end(args);
    
    
    if(remote_mode) {
        char mensaje[120];
        snprintf(mensaje,sizeof(mensaje), "ESTADO:%s\n", buffer);
        serial_send(mensaje);
    }
    
}

void manejar_modo_remoto()
{
    
    printf("Modo remoto activado\n");
    actualizar_estado("Modo remoto|Menu principal");
    
    while(remote_mode)
    {
        char buffer[50];
        int bytes = serial_receive(buffer,sizeof(buffer));
        if(bytes > 0)
        {
            buffer[bytes]='\0';
            if(strcmp(buffer,"Q\n") == 0)
            {
                set_remote_mode(0);
            }else
            {
                printf("Comando recibido:%s\n",buffer);
            }
        }
        
        if(kbhit())
        {
            char tecla = getchar();
            if(tecla == 'q' || tecla == 'Q')
            {
                set_remote_mode();
            }
        }
    }
    
}
*/
