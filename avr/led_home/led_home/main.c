/*
 * led_home.c
 *
 * Created: 1/18/2020 12:12:12
 * Author : Clau
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uartd.h"


#define LED PC5
#define BUTTON PC4

int main(void)
{
    DDRC |= (1 << LED);
	
	init_uart(9600);
	int i=0;
    while (1) 
    {
		if (PINC & (1 << BUTTON))
		{
			
		}
		printf("it:%d\n",i++);
		PORTC |= (1<<LED);
		_delay_ms(1000);
		PORTC &= ~(1 << LED);
		_delay_ms(1000);
    }
}

