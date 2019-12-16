/*
 * shift_lib.c
 *
 * Created: 16/12/2019 17:26:23
 * Author : Clau
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	// setup set ports as output
   DDRA = 0xFF;
   DDRB = 0xFF;
   DDRC = 0xFF;
   

    while (1) 
    {
		PORTA |= (1 << 0);
		PORTC &= ~(1 << 0);
		_delay_ms(10);
		PORTA &= ~(1 << 0);
		PORTC |= (1 << 0);
		_delay_ms(10);
    }
}

