/*
 * keypad.c
 *
 * Created: 2/18/2020 10:20:53 AM
 * Author : Abdullah saeed
 */ 

#include <avr/io.h>
#include "keypad.h"
#include "LCD.h"
#include "PORT.h"

int main(void)
{
		MCUCSR |= (1<<JTD);
		MCUCSR |= (1<<JTD);
	DDRA = 0xff;
	KeyPad_init();
	LCD_Init();
	//LCD_SendString("hello",0);
	
    /* Replace with your application code */
    while (1) 
    {
		
		KeyPad_Scan();
		
    }
}

