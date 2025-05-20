/**
 * @file delay_asm.h
 * @brief Funciones de delay en ensamblador ARM
 */

#ifndef DELAY_ASM_H
#define DELAY_ASM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Delay en milisegundos (implementado en ensamblador)
 * @param milliseconds Tiempo a esperar en ms
 */
void delayMillis(unsigned int milliseconds);

/**
 * @brief Delay en microsegundos (implementado en ensamblador)
 * @param microseconds Tiempo a esperar en µs
 */
void delayMicros(unsigned int microseconds);

#ifdef __cplusplus
}
#endif

#endif // DELAY_ASM_H