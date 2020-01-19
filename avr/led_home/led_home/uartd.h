/*
 * IncFile1.h
 *
 * Created: 1/19/2020 15:18:37
 *  Author: Clau
 */ 
#define F_CPU 1000000UL
	
#include <stdio.h> 

#define DEFAULT_UART_BAUD_RATE  9600
//#define DEFAULT_UART_BAUD_REGISTERS  (((F_CPU / (UART_BAUD_RATE * 16UL))) - 1)

uint16_t Baud;
//uint16_t Baud_registers;

int printCHAR(char character, FILE *stream);

int init_uart(uint16_t baud);

FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW);


