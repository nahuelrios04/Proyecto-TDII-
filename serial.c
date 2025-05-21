#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/select.h>
#include "serial.h"

int remote_mode = 0; // 0=local, 1=remoto



//////////// ANDA /////////////////////////////
void set_remote_mode(int enable) {
    remote_mode = enable;
}
char * get_remote_mode()
{
    if(remote_mode)
    {
        return "Activado";
    }else return "Desactivado";
}
////////////////////////////////////////////////
