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
int running = 1;
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
    serial_init(B9600);
    // Configuración inicial
    set_remote_mode(0); // Iniciar en modo local
    configurar_terminal();
    mostrar_menu_secuencias();
    while(running) 
    {
        if(kbhit())
        {
            char tecla = leer_tecla();
            switch(tecla)
            {
                case '1': secuencias[0].funcion(); break;
                case '2': secuencias[1].funcion(); break;
                case '3': secuencias[2].funcion(); break;
                case '4': secuencias[3].funcion(); break;
                case '5': secuencias[4].funcion(); break;
                case '6': secuencias[5].funcion(); break;
                case '7': secuencias[6].funcion(); break;
                case '8': secuencias[7].funcion(); break;
                case '9': 
                {
                    set_remote_mode(!remote_mode);
                    break;
                }
                case '0': 
                {
                    running = 0;
                    break;
                }
                default: break;
            }
            mostrar_menu_secuencias();
            
        }
        
        char buffer[BUFFER_SIZE];
        if(remote_mode == 1 && serial_read(buffer,BUFFER_SIZE)==0)
        {
            printf("%s",buffer);
            switch(comando_mp(buffer))
            {
                case 1: secuencias[0].funcion(); break;
                case 2: secuencias[1].funcion(); break;
                case 3: secuencias[2].funcion(); break;
                case 4: secuencias[3].funcion(); break;
                case 5: secuencias[4].funcion(); break;
                case 6: secuencias[5].funcion(); break;
                case 7: secuencias[6].funcion(); break;
                case 8: secuencias[7].funcion(); break;
                case 9: 
                {
                    set_remote_mode(!remote_mode);
                    break;
                }
                case 0: 
                {
                    running = 0;
                    break;
                }
            }
            //mostrar_menu_secuencias();
            memset(buffer,0,BUFFER_SIZE);
            delayMillis(100);
        }
    }
    serial_close();
    restore_terminal();
    return 0;
}


void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}


