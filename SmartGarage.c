/*
 * Smart Garage.c
 *
 * Created: 7/17/2020 10:00:59 PM
 * Author : abdal
 */ 


#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000ul
#include <avr/interrupt.h>
#define F_CPU 8000000ul
#include "Time.h"
#include "UltraSonic.h"
#include "LCD.h"
#include "keypad.h"
#include "SW.h"
#include "Port.h"
#include "main.h"
#include "request.h"
#include "garage.h"
#include "uart.h"
#include "motor.h"
#include "warningled.h"

 // initialize timer, interrupt and variable
 void timer1_init()
 {
	 // set up timer with prescaler = 8
	 TCCR1B |= (1 << CS10);
	 
	 // initialize counter
	 TCNT1 = 0;
	 
	 // enable overflow interrupt
	 TIMSK |= (1 << TOIE1);
	 
	 // enable global interrupts
	 sei();
	 

 }


// OS 
 ISR(TIMER1_OVF_vect)
 {



 }
 
char c;

int main(void)
{


MCUCSR |= (1<<JTD);
MCUCSR |= (1<<JTD);

 _delay_ms(300);
/** initialization tasks **/
  timer1_init();
  LCD_Init();
  motor_init();
  wled_init();
  KeyPad_init();
  /** ultrasonic_init */
  ultrasonic_init(); 

	LCD_SendString("Scanning Update ..",0);
	LCD_SendString("Please Wait.....  ",1);
	

// configure the switches as input
  GPIO_WritePortPin(SW_REQ_CR    , SW_REQ_PIN	, 0);
  GPIO_WritePortPin(SW_OK_CR     , SW_OK_PIN	, 0);
  GPIO_WritePortPin(SW_CANCEL_CR , SW_CANCEL_PIN , 0);
  
  
  /**color sensor pins */
  GPIO_WritePortPin(DDRC ,2 ,0);
  GPIO_WritePortPin(DDRC ,3 ,0);
  GPIO_WritePortPin(DDRC ,4 ,0);
  GPIO_WritePortPin(DDRD ,4 ,0);
		
	  
	  wled_on();
 	  garage_scan();
	  motor_off();
	  wled_off();
	 	 	 
		
	while (1) 
    {

/*ultrasonic();*/
 
//  
//  motor_on();
//  	 LCD_SendString("motor on   ",0);
//  	 _delay_ms(100);
//   while(GPIO_ReadPortPin(PIND,4) == 0);
//   
//  motor_off();
//  LCD_SendString("motor off  ",0);
//  _delay_ms(300);
  	  
req_update();
garage_update();

 
 }


}