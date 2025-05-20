/* TRABAJO PRACTICO FINAL TECNICAS DIGITALES II
 * 
 * 	ARCHIVO: Secuencias.c
 * 	ALUMNOS: Cerutti, Julian.	Legajo: 79278
 * 		 Rios, Nahuel.		Legajo: 75502
 * 		 Villa, Federico.	Legajo: 88722
 * 		 Zangheri, Agustin      Legajo: 81920
 * 
 * 	VERSION: 3.0	
 * 	PENDIENTES:	# Terminar protocolos modo remoto.
 * 			# Completar con actualizacion de interfaz local y remota
 * 			
*/

///////////LIBRERIAS///////////
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <math.h>
#include "Secuencias.h"
#include "EasyPIO.h"
#include "kbhit.h"
/////////DEFINE////////////////
#define LOW 0
#define HIGH 1
////////VARIABLES GLOBALES/////
const int LED_PINS[NUM_LEDS] = {23, 24, 25, 12, 16, 20, 21, 26};	// GPIO Leds
volatile unsigned int current_delay = 500;											

/*	Guardamos todas las secuencias con su funcion y id	*/
SecuenciaMenu secuencias[NUM_SECUENCIAS] = {
    {1, "Auto Fantastico", el_auto_fantastico},
    {2, "El Choque", el_choque},
    {3, "La Apilada", la_apilada},
    {4, "La Carrera", la_carrera},
    {5, "La ola", la_ola},
    {6, "Aleatorio controlado", el_aleatorio_controlado},
    {7, "Binario", el_binario},
    {8, "Latido", el_latido}
};

////DEFINICION DE FUNCIONES//////
void apagar_todo() {
    /*
     * Funcion que se encarga de apagar todos los leds.
    */
    for (int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(LED_PINS[i], LOW);
    }
}
void ajustar_delay(char tecla)
{
    /*
     * Funcion que se encarga de aumentar o disminuir la variable
     * current_delay en base al ingreso por teclado.
     * Recibe por parametro el caracter a analizar.
    */
    if(tecla == '+' && current_delay > 50)
    {
	current_delay -= 50;
    }else if(tecla == '-' && current_delay < 2000)
    {
	current_delay += 50;
    }
}
/*
 * USADA ANTERIORMENTE EN LA VERSION 2
void menu_secuencias() {
    int opc = -1;
    char input[10];

    while (1) {
        system("clear");
        printf("-----------------------------------\n");
        printf("=== CONTROL DEL SECUENCIAS LED ===\n");
        printf("-----------------------------------\n");

        for (int i = 0; i < NUM_SECUENCIAS; i++) {
            printf("%d. %s\n", secuencias[i].id, secuencias[i].nombre);
        }

        printf("\n0. Salir\n");
        printf("-----------------------------------\n");
        printf("Seleccione una opcion (1-%d): ", NUM_SECUENCIAS);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%d", &opc) == 1) {
                if (opc >= 0 && opc <= NUM_SECUENCIAS) {
                    printf("Eligio la secuencia %s\n", secuencias[opc - 1].nombre);
                    break;
                }
            }
        }
        printf("Opcion invalida. Intente nuevamente.\n");
        sleep(1);
    }
    if (opc != 0) {
        secuencias[opc - 1].funcion();
    }
    
}
*/

void el_auto_fantastico()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces el
	 * auto fantastico.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	system("clear"); 	//Limpiamos pantallas
	configurar_terminal();	//Configuramos terminal no canonico
	//actualizar_estado("Ejecutando|Auto fantastico|Velocidad:%d",current_delay); VER
	int currentLed = 0;
	int direction = 1;
	
	while (1)
	{
		// Encendido y apagado de led actual
		digitalWrite(LED_PINS[currentLed], HIGH);
		delayMillis(current_delay);
		digitalWrite(LED_PINS[currentLed], LOW);
		// Cambiamos de led segun direccion
		currentLed += direction;
		//  Si llegamos a un extremo cambiamos de direccion
		if (currentLed == NUM_LEDS || currentLed == -1)
		{
			direction *= -1;
			currentLed += direction;
		}
		// Chequeo si debemos salir de la secuencia
		if(chequeo())
		{
		    apagar_todo();
		    break;
		}
		/*
		 * 	REVISAR
		char buffer[20];
		if(serial_receive(buffer,sizeof(buffer)))
		{
		    if(buffer[0] == 'V')
		    {
			current_delay = atoi(buffer+1);
			actualizar_estado("Ejecutando|Auto fantastico|Velocidad:%d",current_delay);
		    }
		}
		*/
	}
	restaurar_terminal();	// Restaura modo a modo canonico
	apagar_todo();		// Apaga los leds	
}

void el_choque()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces el
	 * choque.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	system("clear");
	printf("Reproduciendo el choque...\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");
	configurar_terminal();
	while (1)
	{
	    int pos_izq = 0;
	    int pos_der = NUM_LEDS - 1;
	    int dir_izq = 1;
	    int dir_der = -1;

	    while (pos_izq < pos_der)
	    {
		digitalWrite(LED_PINS[pos_izq], HIGH);
		digitalWrite(LED_PINS[pos_der], HIGH);
		delayMillis(current_delay);
		digitalWrite(LED_PINS[pos_izq], LOW);
		digitalWrite(LED_PINS[pos_der], LOW);
		pos_izq += dir_izq;
		pos_der += dir_der;
	    }

	    // Efecto de choque
	    for (int i = 0; i < 3; i++)
	    {
		digitalWrite(LED_PINS[pos_izq], HIGH);
		digitalWrite(LED_PINS[pos_der], HIGH);
		delayMillis(100);
		digitalWrite(LED_PINS[pos_izq], LOW);
		digitalWrite(LED_PINS[pos_der], LOW);
		delayMillis(100);
	    }
	    if(chequeo()) break;
	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}


void la_carrera()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces la
	 * carrera.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	system("clear");
	printf("Reproduciendo La carrera...\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");
	// Tabla con los valores de la secuencia
	int tabla[]={
		0b00000001,
		0b00000010,
		0b00000100,
		0b00001000,
		0b00010010,
		0b00101000,
		0b01100000,
		0b10000000};
	configurar_terminal();
	int flag = 0;
	while(1)
	{
		for(int k=0;k<8;k++)
		{			
			for(int i=0;i<NUM_LEDS;i++)
			{
				int estado = (tabla[k] >> i) & 0x01;
				digitalWrite(LED_PINS[i],estado);
			}
			delayMillis(current_delay);
			if(chequeo())
			{
			    flag = 1;
			    apagar_todo();
			    break;
			}
		}
		if(chequeo() || flag == 1)
		{
		    apagar_todo();
		    break;
		}	
	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}
void la_apilada()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces la
	 * apilada.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	const int delay_parpadeo = 150;
	int pos_final = 0;
	int flag = 0;
	configurar_terminal();
	system("clear");
	printf("Reproduciendo La apilada...\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");
	while(1)
	{
		int led_fijos[NUM_LEDS] = {0};
		int num_led_fijos = 0;
		while(num_led_fijos < NUM_LEDS)
		{
			for(int pos = 0; pos < (NUM_LEDS - num_led_fijos-1); pos++)
			{
			    digitalWrite(LED_PINS[pos],1);
			    delayMillis(current_delay);
			    digitalWrite(LED_PINS[pos],0);
			    if(chequeo())
			    {
				flag = 1;
				apagar_todo();
				break;
			    }
			}
			pos_final = NUM_LEDS - num_led_fijos - 1;
			for(int i = 0; i < 3 ; i++)
			{
				digitalWrite(LED_PINS[pos_final],1);
				delayMillis(delay_parpadeo);
				digitalWrite(LED_PINS[pos_final],0);
				delayMillis(delay_parpadeo);
			}
			digitalWrite(LED_PINS[pos_final],1);
			led_fijos[pos_final] = 1;
			num_led_fijos++;
			for(int j = 0 ; j < NUM_LEDS ; j++)
			{
				if(led_fijos[j])
				{
					digitalWrite(LED_PINS[j],1);
				}
			}
			if(chequeo() || flag == 1)
			{
			    apagar_todo();
			    break;
			}
		}
		if(flag == 1) break;
		delayMillis(2000);
		apagar_todo();
		pos_final = 0;
	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}

void la_ola()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces la
	 * ola.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	configurar_terminal();
	system("clear");
	printf("Ejecutando 'La Ola'\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");
	int flag = 0;
	while(1) 
	{
	    // Ola hacia la derecha
	    for(int i = 0; i < NUM_LEDS; i++)
	    {
		digitalWrite(LED_PINS[i], HIGH);
		delayMillis(current_delay);
		digitalWrite(LED_PINS[i], LOW);
		if(chequeo())
		{
		    flag = 1;
		    apagar_todo();
		    break;
		}
	    }
	    
	    // Ola hacia la izquierda
	    for(int i = NUM_LEDS-1; i >= 0; i--)
	    {
		digitalWrite(LED_PINS[i], HIGH);
		delayMillis(current_delay);
		digitalWrite(LED_PINS[i], LOW);
		if(chequeo())
		{
		    flag = 1;
		    apagar_todo();
		    break;
		}
	    }
	    
	    // Efecto final
	    for(int i = 0; i < NUM_LEDS; i++)
	    {
		digitalWrite(LED_PINS[i], HIGH);
		if(chequeo())
		{
		    flag = 1;
		    apagar_todo();
		    break;
		}
	    }
	    if(chequeo() || flag == 1)
	    {
		apagar_todo();
		break;
	    }
	    delayMillis(current_delay);
	    apagar_todo();
	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}
void el_aleatorio_controlado() 
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces el
	 * aleatorio controlado.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	int ultimo_led = -1;
	configurar_terminal();
	system("clear");
	printf("Ejecutando 'El Aleatorio Controlado'\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");

	while(1)
	{
	    // Apagar el LED anterior
	    if(ultimo_led >= 0)
	    {
		digitalWrite(LED_PINS[ultimo_led], LOW);
	    }


	    // Encender nuevo LED aleatorio (no consecutivo)
	    int nuevo_led;
	    do 
	    {
		nuevo_led = rand() % NUM_LEDS;
	    } while(abs(nuevo_led - ultimo_led) <= 1 && NUM_LEDS > 3);
	    
	    digitalWrite(LED_PINS[nuevo_led], HIGH);
	    ultimo_led = nuevo_led;
	    delayMillis(current_delay);
	    if(chequeo())
	    {
		apagar_todo();
		break;
	    }
	}
	
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}

void el_binario()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces el
	 * binario.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	configurar_terminal();
	int flag = 0;
	system("clear");
	printf("Ejecutando 'El Binario'\n");
	printf("Presiona 'S' para detener. +/- para velocidad\n");
	while(1)
	{
	    // Contar de 0 a 255 (para 8 LEDs)
	    for(int num = 0; num < (1 << NUM_LEDS); num++)
	    {
		for(int bit = 0; bit < NUM_LEDS; bit++)
		{
		    digitalWrite(LED_PINS[bit], (num >> bit) & 0x01);
		}
		delayMillis(current_delay);
		if(chequeo())
		{
		    flag = 1;
		    apagar_todo();
		    break;
		}
	    }
	    if(chequeo() || flag == 1)
	    {
		apagar_todo();
		break;
	    }
	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}

void el_latido()
{
	/*
	 * Funcion que se encarga de ejecutar la secuencia de luces el
	 * latido.
	 ************************PENDIENTES*****************************
	 * 	#Funciones en modo remoto
	*/
	system("clear");
	printf("Ejecutando 'El Latido'\n");
	printf("Presiona 'S' para detener. '+'/- para velocidad.\n");

	int ciclo_pwm = 0;           // Controla el ciclo de trabajo (0-100)
	int direccion = 1;            // 1 para aumentar brillo, -1 para disminuir
	configurar_terminal();        // Modo no canónico

	while (1)
	{
	    if(chequeo())
	    {
		apagar_todo();
		break;
	    }

	    // Actualizar ciclo PWM
	    ciclo_pwm += direccion * 5;  // Ajusta la velocidad del efecto
	    if (ciclo_pwm >= 100) direccion = -1;
	    if (ciclo_pwm <= 0) direccion = 1;

	    // Aplicar PWM a todos los LEDs
	    for (int i = 0; i < 100; i++)
	    {
		for (int led = 0; led < NUM_LEDS; led++)
		{
		    digitalWrite(LED_PINS[led], (i < ciclo_pwm) ? HIGH : LOW);
		}
		delayMillis(current_delay * 10); // Ajuste fino con delayMicros
	    }

	}
	restaurar_terminal();	// Restaura modo no canonico
	apagar_todo();		// Apaga los leds
}

int chequeo()
{
    /*
     * Funcion que se encarga de leer el teclado y en base a conicidencia
     * con comandos ejecuta una accion.
     * IMPORTANTE: SE DEBE EJECUTAR EN UN ENTORNO DONDE SE LLAME A LA FUNCIONES
     * QUE CONFIGURAN LA TEMRINAL.
     * EJ:
     * 		configurar_terminal();
     * 		...
     * 		chequeo();
     * 		...
     * 		restaurar_terminal();
     * 
     * 's' o 'S': Devuelve 1. significa que hay que interrumpir la secuencia.
     * '+': llama a la funcion ajustar_delay() y disminuye curent_dely 50ms.
     * '-': llama ala funcion ajustar_delay() y aumenta current_delay 50ms.
    */
    if(kbhit())
    {
	char tecla = leer_tecla();
	if(tecla == 's' || tecla == 'S')
	{
	    return 1;
	}
	ajustar_delay(tecla);
	/*			VER				*/
	//actualizar_estado("Ejecutando|Auto fantastico|Velocidad:%d",current_delay);

    }
    return 0;
}
