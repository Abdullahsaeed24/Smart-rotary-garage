/*
 * keypad.c
 *
 * Created: 2/18/2020 10:36:29 AM
 *  Author: Abdullah saeed
 */ 

#include "keypad.h"
#include "Port.h"
#include "main.h"
#include "LCD.h"

unsigned char row = 0;
unsigned char column = 0;


void KeyPad_init(void)
{
	
	/* initiate the rows as input */
	ROWS_CONT_REG = 0x00;

	/* initiate the columns as high impedance*/

}


char KeyPad_Scan(void)
{
 /* enable the pull up resistor for the rows */	
 
char buttom_no=13 ;

 ROWS_DATA_REG = 0x0f;
 
 for (column = 0 ; column < 3 ; column ++)
 {
	 switch(column)
	 {
		 
		case 0 :
		/* write 0 to DDR of the column pin */
		GPIO_WritePortPin(COLUMN1_CONT_REG , COLUMN1_PIN , GPIO_OUT);
		GPIO_WritePortPin(COLUMN1_DATA_REG , COLUMN1_PIN , GPIO_IN);
		
		GPIO_WritePortPin(COLUMN2_CONT_REG , COLUMN2_PIN , GPIO_IN);
		GPIO_WritePortPin(COLUMN3_CONT_REG , COLUMN3_PIN , GPIO_IN);
		
		
			if (GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0); buttom_no = 1;}
			if (GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0); buttom_no = 4;}
			if (GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0); buttom_no = 7;}
			 if (GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0); buttom_no = 11;}
		
		
		
		break;
		
		
		case 1 :
		/* write 0 to DDR of the column pin */
		GPIO_WritePortPin(COLUMN2_CONT_REG , COLUMN2_PIN , GPIO_OUT);
		GPIO_WritePortPin(COLUMN1_DATA_REG , COLUMN2_PIN , GPIO_IN);
		
		GPIO_WritePortPin(COLUMN1_CONT_REG , COLUMN1_PIN , GPIO_IN);
		GPIO_WritePortPin(COLUMN3_CONT_REG , COLUMN3_PIN , GPIO_IN);		
			
			if (GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0); buttom_no = 2;}
			else if (GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0); buttom_no = 5;}
			else if (GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0); buttom_no = 8;}
			else if (GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0); buttom_no = 0;}
			
		break; 
		 
		 
		case 2 :
		GPIO_WritePortPin(COLUMN3_CONT_REG , COLUMN3_PIN , GPIO_OUT);
		GPIO_WritePortPin(COLUMN3_DATA_REG , COLUMN3_PIN , GPIO_IN);
		
		GPIO_WritePortPin(COLUMN2_CONT_REG , COLUMN2_PIN , GPIO_IN);
		GPIO_WritePortPin(COLUMN1_CONT_REG , COLUMN1_PIN , GPIO_IN);		
		
			if (GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW1_PINA_CHECK ,ROW1_PIN) == 0); buttom_no = 3;}
			else if (GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW2_PINA_CHECK ,ROW2_PIN) == 0); buttom_no = 6;}
			else if (GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW3_PINA_CHECK ,ROW3_PIN) == 0);return buttom_no = 9;}
			else if (GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0)
			{while(GPIO_ReadPortPin(ROW4_PINA_CHECK ,ROW4_PIN) == 0); buttom_no = 12;}
					
	
				
		
		break;

	 
		default:
		 
		break;
 
 }
 	
		}
			
		return buttom_no;   
		   
 }
