#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include "kbhit.h"

static struct termios original_termios;

// Configurar terminal en modo no canónico y sin eco
void configurar_terminal() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// Restaurar configuración original
void restaurar_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

// Verificar si hay tecla presionada
int kbhit() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

// Leer la tecla presionada
char leer_tecla() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) < 0) {
        perror("Error al leer tecla");
    }
    return c;
}