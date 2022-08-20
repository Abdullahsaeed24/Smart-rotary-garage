/*
 * main.h
 *
 * Created: 12/26/2019 1:49:33 AM
 *  Author: Abdullah saeed
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#include <avr/io.h>
#include <avr/interrupt.h>


/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      (DDRA)
#define GPIO_PINA_CHECK         (PINA)



#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      (DDRB)
#define GPIO_PINB_CHECK         (PINB)



#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      (DDRC)
#define GPIO_PINC_CHECK         (PINC)



#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      (DDRD)
#define GPIO_PIND_CHECK         (PIND)


/* GPIO direction setting */
#define GPIO_OUT                (1)
#define GPIO_IN                 (0)


/******************/
#define TURN_ON  (1)
#define TURN_OFF (0)
/*********************/



/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */

#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))


#define SET_BIT(REG , PIN)   (REG = REG |(1<<PIN))
#define CLEAR_BIT(REG , PIN) (REG = REG & (~(1<<PIN)))
#define TOGGLE_BIT(REG , PIN) (REG = REG ^(1<<PIN))
/* End of code filling */





typedef unsigned int tWORD ;
typedef char tBYTE;
typedef unsigned char tUByte;


#endif /* MAIN_H_ */