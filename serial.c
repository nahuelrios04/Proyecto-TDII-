/*
 * COMANDOS:
 *          *M0-M9: Retornan mediante comando_mp() con el respectivo entero M1 return 1;
 *          *S:  
 * 
*/
#include "serial.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
static int serial_fd = -1;


int remote_mode = 0;
// Hilo de recepción (ejecución continua)


int serial_init(int baudrate) {
    struct termios options;
    
    // Abrir puerto
    serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if(serial_fd < 0) return -1;

    // Configurar parámetros
    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ECHO);
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 1; // Timeout de 0.1 segundos

    tcsetattr(serial_fd, TCSANOW, &options);

    
    return 0;
}

void serial_send(const char* data) {
    if(serial_fd >= 0) {
        printf("[DEBUG]Enviando %s\n",data);
        write(serial_fd, data, strlen(data));
    }
}

int serial_read(char* buffer, int size) {
    fcntl(serial_fd,F_SETFL, O_NONBLOCK);
    int n = read(serial_fd,buffer,size - 1);
    if(n > 0)
    {
        buffer[n]= '\0';
        return 1;
    }
    return 0;
}

void serial_close() {
    
    close(serial_fd);
    serial_fd = -1;
}

void set_remote_mode(int enable)
{
    remote_mode = enable;
}
    
char * get_remote_mode(void)
{
    if(remote_mode)
    {
        return "Activado";
    }else return "Desactivado";
}

int comando_mp(char * command)
{
    command[strcspn(command,"\r\n")]='\0';
    if((strcmp(command,"M0")) == 0)
    {
        return 0;
    }else if((strcmp(command,"M1")) == 0)
    {
        return 1;
    }else if((strcmp(command,"M2")) == 0)
    {
        return 2;
    }else if((strcmp(command,"M3")) == 0)
    {
        return 3;
    }else if((strcmp(command,"M4")) == 0)
    {
        return 4;
    }else if((strcmp(command,"M5")) == 0)
    {
        return 5;
    }else if((strcmp(command,"M6")) == 0)
    {
        return 6;
    }else if((strcmp(command,"M7")) == 0)
    {
        return 7;
    }else if((strcmp(command,"M8")) == 0)
    {
        return 8;
    }else if((strcmp(command,"M9")) == 0)
    {
        return 9;
    }else return -1;
}
