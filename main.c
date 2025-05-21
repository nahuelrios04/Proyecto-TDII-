/* TRABAJO PRACTICO FINAL TECNICAS DIGITALES II
 * 
 * 	ARCHIVO: main.c
 * 	ALUMNOS: Cerutti, Julian.	Legajo: 79278
 * 		     Rios, Nahuel.		Legajo: 75502
 * 		     Villa, Federico.	Legajo: 88722
 * 		     Zangheri, Agustin      Legajo: 81920
 * 
 * 	VERSION: 3.0	
 * 	PENDIENTES:	# Terminar protocolos modo remoto.
 * 			    # Completar con actualizacion de interfaz local y remota
 * 			
*/

///////////LIBRERIAS///////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "Secuencias.h"
#include "ledsInit.h"
#include "EasyPIO.h"
#include "kbhit.h"
#include "serial.h"
#include "password.h"
#include "menu.h"

////////VARIABLES GLOBALES///////
volatile int running = 1;
extern SecuenciaMenu secuencias[];
void procesar_comando(char *);
extern int remote_mode;
static struct termios original_termios;

////DEFINICION DE FUNCIONES//////
void restore_terminal(void);
void terminal();

int main()
{
    struct termios original_term;
    tcgetattr(STDIN_FILENO, &original_term);
    
    struct termios new_term = original_term;
    new_term.c_lflag &= ~(ICANON & ~ECHO);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    if(!verificar_password()) 
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_term);
        return 1;
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &original_term);
    pioInit();
    leds_init();
    
    // Configuración inicial
    set_remote_mode(0); // Iniciar en modo local
    int opcion = -1;
    while(running) 
    {
        
        opcion = mostrar_menu_secuencias();
        if(opcion == 0)
        {
            running = 0;
            system("clear");
            printf("SALIENDO....\n");
            running = 0;
            break;
        }else if(opcion <=NUM_SECUENCIAS && opcion > 0)
        {
            secuencias[opcion-1].funcion();
        }
        

    }
    
    return 0;
}


void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}


