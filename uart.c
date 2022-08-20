/*
 * uart.c
 *
 * Created: 8/11/2020 3:34:58 PM
 *  Author: abdal
 */ 

#include "uart.h"

// define some macros
#define F_CPU 8000000ul
#define BAUD (9600)                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR


// function to initialize UART
void uart_init (void)
{
	UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
	UBRRL = BAUDRATE;                           // set baud rate
	UCSRB= 0x90;   // enable receiver , receiver interrupt
	UCSRC=0x3b; 
	
	}