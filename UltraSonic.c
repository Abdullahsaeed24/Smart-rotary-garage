/*
 * UltraSonic.c
 *
 * Created: 5/11/2020 11:01:37 PM
 *  Author: Abdullah saeed
 */ 

#include "UltraSonic.h"
#include <util/delay.h>
#include "LCD.h"
#include "Time.h"
#include "Port.h"
#include <stdlib.h>


static double distance ;



void ultrasonic_init(void)
{

GPIO_WritePortPin(TRRIGER_CONT_REG,TRRIGER_PIN , GPIO_OUT);	 // ADJUST TRIGGER PIN AS OUTPUT

GPIO_WritePortPin(ECHO_CONT_REG,ECHO_PIN , GPIO_IN);	 // ADJUST ECHO PIN AS INPUT
	

}


void ultrasonic(void)
{
	
	

char dist[5];	
	GPIO_WritePortPin(PORTC ,TRRIGER_PIN, 1);
	_delay_us(20);

	GPIO_WritePortPin(PORTC ,TRRIGER_PIN, 0);
	
	
	while(GPIO_ReadPortPin(PINC ,ECHO_PIN) == 0);
	TCNT1=0;
	
	
	
	while(GPIO_ReadPortPin(PINC ,ECHO_PIN) == 1);
	
	TIMSK &= (~(1 << TOIE1));
	
	distance = (float)(TCNT1) /58.30;
	
//   	  dtostrf(distance, 2, 2, dist);
//   	  LCD_SendString(dist,1);
// //  	
	TCNT1 = 0;
	
	TIMSK |= (1 << TOIE1);

	 

}



double GET_ULTRASONIC_DISTANCE(void)
{
	
return distance ;	
	
	
}