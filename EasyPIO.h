#ifndef EASY_PIO_H
#define EASY_PIO_H

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// Constantes
#define INPUT  0
#define OUTPUT 1
#define ALT5   2
#define ALT4   3
#define ALT0   4
#define ALT1   5
#define ALT2   6
#define ALT3   7

// Dirección base para Raspberry Pi 4
#define BCM2711_PERI_BASE   0xFE000000
#define GPIO_BASE           (BCM2711_PERI_BASE + 0x200000)
#define BLOCK_SIZE          (4*1024)

// Declaración del puntero GPIO (extern para acceso desde otros archivos)
extern volatile unsigned int *gpio;

// Macros para acceso a registros
#define GPFSEL      ((volatile unsigned int *)(gpio + 0))
#define GPSET       ((volatile unsigned int *)(gpio + 7))
#define GPCLR       ((volatile unsigned int *)(gpio + 10))
#define GPLEV       ((volatile unsigned int *)(gpio + 13))

// Declaraciones de funciones
void pioInit();
void pinMode(int pin, int function);
void digitalWrite(int pin, int val);
int digitalRead(int pin);
void delay(unsigned int milliseconds);

#endif