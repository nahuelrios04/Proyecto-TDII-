#ifndef SERIAL_H
#define SERIAL_H

#include <termios.h>
#define BAUDRATE B9600
#define SERIAL_PORT "/dev/ttyAMA0"

extern int remote_mode;

void set_remote_mode(int);
char * get_remote_mode();


#endif
