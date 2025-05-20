#ifndef SECUENCIAS_H
#define SECUENCIAS_H

#define MAX_LONG_NOMBRE 21
#define NUM_LEDS 8
#define NUM_SECUENCIAS 8
#include "EasyPIO.h"
#include <stdlib.h>
#include <stdarg.h>
////PINES LEDS///////////////////////
extern const int LED_PINS[NUM_LEDS];
extern volatile unsigned int current_delay;
typedef struct {
    int id;                 // Identifica cada secuencia
    char nombre[MAX_LONG_NOMBRE];  // Nombre que aparece en el menú
    void (*funcion)();      // Función que llama a la secuencia
} SecuenciaMenu;
extern SecuenciaMenu secuencias[];
/////PROTOTIPOS//////////////////////
void manejar_modo_remoto();
void apagar_todo();
void el_auto_fantastico();
void el_choque();
void la_apilada();
void la_carrera();
void el_latido();
void la_ola();
void el_aleatorio_controlado();
void el_binario();
void ajustar_delay(char);
void delayMillis(unsigned int ms);
void actualizar_estado(const char *formato);
int chequeo();

#endif
