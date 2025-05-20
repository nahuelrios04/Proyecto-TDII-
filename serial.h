#ifndef SERIAL_H
#define SERIAL_H

#include <termios.h>
#define BAUDRATE B9600
#define SERIAL_PORT "/dev/ttyAMA0"

extern int remote_mode;

// Inicializar comunicación serie
void serial_init();

// Enviar datos
void serial_send(const char *data);

// Recibir datos (no bloqueante)
int serial_receive(char *buffer, int size);

// Cambiar modo de operación
void set_remote_mode(int enable);

// Cerrar puerto
void serial_close();
char * get_remote_mode();


#endif
