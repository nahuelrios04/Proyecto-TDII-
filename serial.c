#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/select.h>
#include "serial.h"

static int serial_fd = -1;
int remote_mode = 0; // 0=local, 1=remoto


void serial_init() {
    serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (serial_fd < 0) {
        perror("Error al abrir puerto serie");
        return;
    }

    struct termios options;
    tcgetattr(serial_fd, &options);
    
    // Configuración básica
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag |= CS8;
    options.c_cc[VMIN] = 0;  // Lectura no bloqueante
    options.c_cc[VTIME] = 1; // Timeout de 0.1 segundos

    tcsetattr(serial_fd, TCSANOW, &options);
    printf("Puerto serie inicializado\n");
}

void serial_send(const char *data) {
    if (serial_fd >= 0 && remote_mode) {
        write(serial_fd, data, strlen(data));
    }
}

int serial_receive(char *buffer, int size) {
    fd_set fds;
    struct timeval tv = {0, 0};
    FD_ZERO(&fds);
    FD_SET(serial_fd, &fds);
    
    if (select(serial_fd + 1, &fds, NULL, NULL, &tv) > 0) {
        return read(serial_fd, buffer, size);
    }
    return 0;
}

void set_remote_mode(int enable) {
    remote_mode = enable;
    tcflush(serial_fd, TCIOFLUSH); // Limpiar buffers
}
char * get_remote_mode()
{
    if(remote_mode)
    {
        return "Activado";
    }else return "Desactivado";
}
void serial_close() {
    if (serial_fd >= 0) close(serial_fd);
}
