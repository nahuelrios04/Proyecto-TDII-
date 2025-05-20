#include "EasyPIO.h"

// Definición del puntero GPIO
volatile unsigned int *gpio;

void pioInit() {
    int mem_fd;
    void *reg_map;
    
    // Abrir /dev/mem
    if((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
        perror("No se pudo abrir /dev/mem");
        return;
    }
    
    // Mapear memoria GPIO
    reg_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ|PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_BASE
    );
    
    if(reg_map == MAP_FAILED) {
        perror("Error en mmap");
        close(mem_fd);
        return;
    }
    
    gpio = (volatile unsigned int *)reg_map;
    close(mem_fd);
}

void pinMode(int pin, int function) {
    int reg = pin / 10;
    int offset = (pin % 10) * 3;
    
    GPFSEL[reg] &= ~(7 << offset);         // Limpiar bits
    GPFSEL[reg] |= (function << offset);   // Establecer función
}

void digitalWrite(int pin, int val) {
    int reg = pin / 32;
    int offset = pin % 32;
    
    if(val) {
        GPSET[reg] = 1 << offset;  // Encender
    } else {
        GPCLR[reg] = 1 << offset;  // Apagar
    }
}

int digitalRead(int pin) {
    int reg = pin / 32;
    int offset = pin % 32;
    
    return (GPLEV[reg] >> offset) & 1;
}

void delay(unsigned int milliseconds) {
    usleep(milliseconds * 1000);
}