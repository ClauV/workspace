/*
 * CFile1.c
 *
 * Created: 1/19/2020 15:17:26
 *  Author: Clau
 */ 
#include "uartd.h"
#include <avr/io.h>

int printCHAR(char character, FILE *stream)
{
	while ((UCSRA & (1 << UDRE)) == 0) {};

	UDR = character;

	return 0;
}

int init_uart(uint16_t baud)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	Baud = baud;
	UBRRL = (((F_CPU / (Baud * 16UL))) - 1);

	//fprintf(&uart_str, "Hello World\n\r");

	stdout = &uart_str;
    printf("Hello World 2\n\r");

	return 1;
}
