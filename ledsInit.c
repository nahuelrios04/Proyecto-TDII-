#include <stdio.h>
#include "EasyPIO.h"
#include "Secuencias.h"


void leds_init()
{
	for(int i = 0; i < NUM_LEDS;i++)
	{
		pinMode(LED_PINS[i],OUTPUT);
		digitalWrite(LED_PINS[i],0);
	}
}




