/*
 * LCD.h
 *
 * Created: 4/16/2020 10:20:32 PM
 *  Author: Abdullah saeed
 */ 


#ifndef LCD_H_
#define LCD_H_


#include"PORT.h"
#include"MAIN.h"

#define LCD_LINE_1          (0)
#define LCD_LINE_2          (1)
#define LCD_LINE_WIDTH      (16)

void LCD_Init(void);
void LCD_Update(void);
void LCD_SendChar (tBYTE character , tBYTE line ,tBYTE column)	;
void LCD_SendString (tBYTE * str ,tBYTE line)	;	
void LCD_Command(tBYTE command); 
void LCD_Clear(void);
#endif /* LCD_H_ */