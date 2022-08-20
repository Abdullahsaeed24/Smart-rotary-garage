/*
 * motor.c
 *
 * Created: 7/18/2020 11:32:20 PM
 *  Author: abdal
 */ 


#include "motor.h"
#include "Port.h"


void motor_init(void)
{
	GPIO_InitPortPin(MOTOR_CR,MOTOR_PIN,GPIO_OUT);
	
}

void motor_on(void)
{
	
GPIO_InitPortPin(MOTOR_DR,MOTOR_PIN,0);	
	
}

void motor_off(void)
{
	
GPIO_InitPortPin(MOTOR_DR,MOTOR_PIN,1);		
	
}
