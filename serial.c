/* serial_lib.c */
#include "serial.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

static int serial_fd = -1;
static char rx_buffer[BUFFER_SIZE];
static pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t rx_thread;
int remote_mode = 0;
// Hilo de recepción (ejecución continua)
static void* serial_rx_thread(void* arg) {
    char temp_buf[BUFFER_SIZE];
    while(1) {
        int n = read(serial_fd, temp_buf, BUFFER_SIZE-1);
        if(n > 0) {
            pthread_mutex_lock(&buffer_mutex);
            temp_buf[n] = '\0';
            strncpy(rx_buffer, temp_buf, BUFFER_SIZE);
            pthread_mutex_unlock(&buffer_mutex);
        }
        usleep(10000); // Evitar uso excesivo de CPU
    }
    return NULL;
}

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
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 1; // Timeout de 0.1 segundos

    tcsetattr(serial_fd, TCSANOW, &options);

    // Crear hilo de recepción
    pthread_create(&rx_thread, NULL, serial_rx_thread, NULL);
    
    return 0;
}

void serial_send(const char* data) {
    if(serial_fd >= 0) {
        write(serial_fd, data, strlen(data));
    }
}

int serial_read(char* buffer, int size) {
    pthread_mutex_lock(&buffer_mutex);
    if(rx_buffer[0] != '\0') {
        strncpy(buffer, rx_buffer, size);
        rx_buffer[0] = '\0'; // Limpiar buffer
        pthread_mutex_unlock(&buffer_mutex);
        return 1;
    }
    pthread_mutex_unlock(&buffer_mutex);
    return 0;
}

void serial_close() {
    pthread_cancel(rx_thread);
    close(serial_fd);
    serial_fd = -1;
}

void set_remote_mode(int enable)
{
    remote_mode = enable;
    serial_init(B9600);
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
    }else return -1;
}
