.global delayMillis
.global delayMicros
.section .text

@ delayMillis(unsigned int milliseconds)
delayMillis:
    push {r4, lr}            @ Guardar registros
    mov r4, r0               @ Guardar el valor de milisegundos

    @ Convertir milisegundos a microsegundos (x1000)
    ldr r1, =1000
    mul r0, r4, r1
    bl delayMicros           @ Llamar a delayMicros

    pop {r4, pc}             @ Restaurar registros y retornar

@ delayMicros(unsigned int microseconds)
delayMicros:
    @ r0 contiene el número de microsegundos
    @ Cada iteración del bucle toma ~3 ciclos (aproximadamente)
    @ A 1GHz, 3 ciclos = 3ns por iteración
    
    @ Calcular número de iteraciones necesarias
    @ (microsegundos * 1000) / 3 ≈ iteraciones
    ldr r1, =333             @ 1000/3 ≈ 333
    mul r0, r0, r1           @ r0 = microsegundos * 333
    
    @ Bucle de delay
1:  subs r0, r0, #1          @ Decrementar contador
    bne 1b                   @ Repetir si no es cero
    
    bx lr                    @ Retornar
