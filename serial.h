/* serial_lib.h */
#ifndef SERIAL_H
#define SERIAL_H



#define BUFFER_SIZE 256
#define SERIAL_PORT "/dev/ttyAMA0"  // Usar ttyAMA0 para Pi 3/4
extern int remote_mode;
// Inicializar puerto serie
int comando_mp(char * command);

int serial_init(int baudrate);

// Enviar string
void serial_send(const char* data);

int serial_read(char* buffer, int size);

// Cerrar puerto
void serial_close();

void set_remote_mode(int);
char * get_remote_mode(void);

#endif
