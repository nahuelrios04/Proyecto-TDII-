#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "kbhit.h"
#include "password.h"

static struct termios old_termios;

// Contraseña predefinida (puedes cambiarla)
const char password_correcta[PASSWORD_LENGTH+1] = "LED12345";

void limpiar_buffer_entrada()
{
    tcflush(STDIN_FILENO, TCIFLUSH);
}

void configurar_terminal_no_canonico() {
    struct termios new_termios;
    
    // Guardar configuración actual
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    
    // Configurar modo no canónico y sin eco
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    
    // Aplicar nueva configuración
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}



void mostrar_asteriscos(char *buf, int len) {
    printf("\rPassword: ");
    for(int i = 0; i < len; i++) {
        putchar('*');
    }
    fflush(stdout);
}

int verificar_password() {
    system("clear");
    char password_ingresada[PASSWORD_LENGTH+1] = {0};
    int intentos = 0;
    time_t tiempo_inicio;
    
    configurar_terminal_no_canonico();
    
    while(intentos < MAX_ATTEMPTS) {
        printf("\n=== SISTEMA DE SECUENCIAS LED ===\n");
        printf("Ingrese la contraseña (%d intentos restantes):\n", MAX_ATTEMPTS - intentos);
        printf("Password: ");
        fflush(stdout);

        
        tiempo_inicio = time(NULL);
        int pos = 0;
        char c;
        
        while(pos < PASSWORD_LENGTH) {
            if(read(STDIN_FILENO, &c, 1) > 0) {
                // Enter antes de completar
                if(c == '\n' || c == '\r') {
                    break;
                }
                
                // Backspace
                if(c == 127 || c == 8) {
                    if(pos > 0) {
                        pos--;
                        password_ingresada[pos] = '\0';
                        mostrar_asteriscos(password_ingresada, pos);
                    }
                    continue;
                }
                
                // Solo caracteres alfanuméricos
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
                    password_ingresada[pos++] = c;
                    mostrar_asteriscos(password_ingresada, pos);
                }
            }
            
            // Timeout
            if(time(NULL) - tiempo_inicio > (PASSWORD_TIMEOUT / 1000)) {
                printf("\n\nTiempo agotado. Por favor intente nuevamente.\n");
                sleep(1);
                limpiar_buffer_entrada();
                break;
            }
        }
        limpiar_buffer_entrada();
        // Verificar contraseña
        if(strncmp(password_ingresada, password_correcta, PASSWORD_LENGTH) == 0) {
            printf("\n\nAcceso concedido. Iniciando sistema...\n");
            sleep(1);
            restaurar_terminal();
            return 1;
        } else {
            printf("\n\nContraseña incorrecta.\n");
            memset(password_ingresada, 0, sizeof(password_ingresada));
            sleep(1);
            intentos++;
        }
    }
    
    printf("\nDemasiados intentos fallidos. Saliendo...\n");
    sleep(2);
    // Al final de verificar_password(), antes de los return:
    restaurar_terminal();
    fflush(stdin);
    tcflush(STDIN_FILENO, TCIFLUSH);
    return 0;
}
