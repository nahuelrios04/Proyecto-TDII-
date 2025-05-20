#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdbool.h>

#define PASSWORD "LED12345"       // Contraseña predeterminada
#define MAX_INTENTOS 3
#define PASSWORD_TIMEOUT 15000        // Tiempo máximo para ingresar contraseña
#define PASSWORD_LENGTH 8
#define MAX_ATTEMPTS 3

int verificar_password(void);

#endif
