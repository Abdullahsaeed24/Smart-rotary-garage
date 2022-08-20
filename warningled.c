/*
 * warningled.c
 *
 * Created: 7/18/2020 11:33:34 PM
 *  Author: abdal
 */ 

#include "warningled.h"
#include "Port.h"



void wled_init(void)
{
	GPIO_InitPortPin(WLED_CR,WLED_PIN,GPIO_OUT);
	
}

void wled_on(void)
{
	
	GPIO_InitPortPin(WLED_DR,WLED_PIN,GPIO_IN);
	
}

void wled_off(void)
{
	
	GPIO_InitPortPin(WLED_DR,WLED_PIN,GPIO_OUT);
	
}