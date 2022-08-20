/*
 * LCD.c
 *
 * Created: 4/16/2020 10:20:12 PM
 *  Author: Abdullah saeed
 */ 

#define F_CPU 1000000ul
#include <util/delay.h>
#include "Time.h"
#include "SW.h"
#include "UltraSonic.h"
#include"LCD.h"
#include"Port.h"
#include"main.h"
 
#include "UltraSonic.h"


#define LCD_CONFIG_WORD             (0x30)
#define LCD_CLR                     (0x01)

#define LCD_CURSOR_HOME             (0x02)

#define LCD_SET_ENTRY_MODE          (0x40)
#define LCD_INCREMENT_CURSOR        (0x02)
#define LCD_DECREMENT_CURSOR        (0x00)
#define LCD_DISPLAY_SHIFT_ON        (0x01)
#define LCD_DISPLAY_SHIFT_OFF       (0x00)

#define LCD_DISPLAY_CONTROL         (0x08)
#define LCD_DISPLAY_ON              (0x04)
#define LCD_DISPLAY_OFF             (0x00)
#define LCD_CURSOR_ON               (0x02)
#define LCD_CURSOR_OFF              (0x00)
#define LCD_CURSOR_BLINK_ON         (0x01)
#define LCD_CURSOR_BLINK_OFF        (0x00)

#define LCD_CURSOR_DISPLAY_CONTROL  (0x10)
#define LCD_SHIFT_CURSOR            (0x00)
#define LCD_SHIFT_DISPLAY           (0x08)
#define LCD_SHIFT_LEFT              (0x00)
#define LCD_SHIFT_RIGHT             (0x04)

#define LCD_FUNCTION_SET            (0x20)
#define LCD_DATA_LENGTH_4           (0x00)
#define LCD_DATA_LENGTH_8           (0x10)
#define LCD_ONE_LINE                (0x00)
#define LCD_TWO_LINES               (0x08)
#define LCD_SMALL_FONT              (0x00)
#define LCD_LARGE_FONT              (0x04)

#define LCD_SET_CGRAM_ADDRESS       (0x40)
#define LCD_SET_DDRAM_ADDRESS       (0x80)

#define LCD_LINE_SIZE               (0x28)
#define LCD_LINE_2_ADDRESS          (0x40)

#define LINE_1			(0x80)
#define LINE_2			(0xC0) 

#define  LCD_PERTIOD (30)
#define  OS_PERTIOD	 (10)
#define  SEC_TIMES	 (100)		

 
 
 
 


void LCD_Command(tBYTE command)
{
	LCD_DATA_PORT_DR= command;
	LCD_CMD_PORT_DR &= (~(1<<LCD_RS_PIN));	/* RS=0 command reg. */
	LCD_CMD_PORT_DR &= (~(1<<LCD_RW_PIN));	/* RW=0 Write operation */
	LCD_CMD_PORT_DR |= (1<<LCD_E_PIN);	/* Enable pulse */
	_delay_us(1);
	LCD_CMD_PORT_DR &= ~(1<<LCD_E_PIN);
	_delay_ms(1);
}

void LCD_SendChar (tBYTE character , tBYTE line , tBYTE column)	/* LCD data write function */
{
	
	switch(line)
	{
		case 0 :
		LCD_Command(LINE_1|column);
		break;
		case 1 :
		LCD_Command(LINE_2|column);
		break;		
		
		default:
		break;
	
	}
	
	
	LCD_DATA_PORT_DR= character;
	LCD_CMD_PORT_DR |= (1<<LCD_RS_PIN);	/* RS=1 Data reg. */
	LCD_CMD_PORT_DR &= ~(1<<LCD_RW_PIN);	/* RW=0 write operation */
	LCD_CMD_PORT_DR |= (1<<LCD_E_PIN);	/* Enable Pulse */
	_delay_us(1);
	LCD_CMD_PORT_DR &= ~(1<<LCD_E_PIN);
	_delay_ms(1);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_CMD_PORT_CR = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_DATA_PORT_CR= 0xFF;		/* Make LCD data port direction as o/p */
	
	LCD_DATA_PORT_DR &= (~(1<<LCD_E_PIN));
	_delay_ms(20);	/* LCD Power ON delay always >15ms */

	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}
 
void LCD_SendString (tBYTE * str ,tBYTE line)	 
{
	int i;
	for(i=0;str[i]!=0;i++)		
	{
		LCD_SendChar (str[i] ,line , i);
	}
}


void LCD_Clear(void)
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}
 
