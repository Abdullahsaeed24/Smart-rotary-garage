/*
 * PORT.h
 *
 * Created: 12/26/2019 2:02:58 AM
 *  Author: Abdullah saeed
 */ 


 #ifndef PORT_H_
 #define PORT_H_
 
 #include "main.h"
 
 #define ROWS_DATA_REG   (GPIO_PORTA_DATA)
 #define ROWS_CONT_REG   (GPIO_PORTA_CONTROL)
 #define ROWS_PINA_CHECK (GPIO_PINA_CHECK)
 
 #define COLUMNS_DATA_REG  (GPIO_PORTA_DATA)
 #define COLUMNS_CONT_REG  (GPIO_PORTA_CONTROL)
 #define COLUMNS_PINA_CHECK(GPIO_PINA_CHECK)
 
 
 #define ROW1_DATA_REG   (GPIO_PORTA_DATA)
 #define ROW1_CONT_REG   (GPIO_PORTA_CONTROL)
 #define ROW1_PINA_CHECK (GPIO_PINA_CHECK)
 #define ROW1_PIN		 (GPIO_PIN_0)

 #define ROW2_DATA_REG   (GPIO_PORTA_DATA)
 #define ROW2_CONT_REG   (GPIO_PORTA_CONTROL)
 #define ROW2_PINA_CHECK (GPIO_PINA_CHECK)
 #define ROW2_PIN		 (GPIO_PIN_1)


 #define ROW3_DATA_REG   (GPIO_PORTA_DATA)
 #define ROW3_CONT_REG   (GPIO_PORTA_CONTROL)
 #define ROW3_PINA_CHECK (GPIO_PINA_CHECK)
 #define ROW3_PIN		 (GPIO_PIN_2)
 
 #define ROW4_DATA_REG   (GPIO_PORTA_DATA)
 #define ROW4_CONT_REG   (GPIO_PORTA_CONTROL)
 #define ROW4_PINA_CHECK (GPIO_PINA_CHECK)
 #define ROW4_PIN		 (GPIO_PIN_3)
 
 
 #define COLUMN1_DATA_REG   (GPIO_PORTA_DATA)
 #define COLUMN1_CONT_REG   (GPIO_PORTA_CONTROL)
 #define COLUMN1_PINA_CHECK (GPIO_PINA_CHECK)
 #define COLUMN1_PIN		(GPIO_PIN_4)

 #define COLUMN2_DATA_REG   (GPIO_PORTA_DATA)
 #define COLUMN2_CONT_REG   (GPIO_PORTA_CONTROL)
 #define COLUMN2_PINA_CHECK (GPIO_PINA_CHECK)
 #define COLUMN2_PIN		(GPIO_PIN_5)


#define COLUMN3_DATA_REG   (GPIO_PORTA_DATA)
#define COLUMN3_CONT_REG   (GPIO_PORTA_CONTROL)
#define COLUMN3_PINA_CHECK (GPIO_PINA_CHECK)
#define COLUMN3_PIN	       (GPIO_PIN_6)



/********* Ultrasonic Sensors configuration *********/

#define ECHO_DATA_REG   (GPIO_PORTC_DATA)
#define ECHO_CONT_REG   (GPIO_PORTC_CONTROL)
#define ECHO_PINA_CHECK (GPIO_PINC_CHECK)
#define ECHO_PIN        (GPIO_PIN_1)

#define TRRIGER_DATA_REG   (GPIO_PORTC_DATA)
#define TRRIGER_CONT_REG   (GPIO_PORTC_CONTROL)
#define TRRIGER_PINA_CHECK (GPIO_PINC_CHECK)
# define TRRIGER_PIN        (GPIO_PIN_0)


 
/********** LCD configuration ************/

#define LCD_DATA_PORT_DR    (GPIO_PORTB_DATA)
#define LCD_DATA_PORT_CR    (GPIO_PORTB_CONTROL)

#define LCD_CMD_PORT_DR    (GPIO_PORTD_DATA)
#define LCD_CMD_PORT_CR    (GPIO_PORTD_CONTROL) 

#define LCD_RS_DR           (GPIO_PORTD_DATA)
#define LCD_RS_CR           (GPIO_PORTD_CONTROL)
#define LCD_RS_PIN          (GPIO_PIN_0)

#define LCD_RW_DR           (GPIO_PORTD_DATA)
#define LCD_RW_CR           (GPIO_PORTD_CONTROL)
#define LCD_RW_PIN          (GPIO_PIN_1)


#define LCD_E_DR           (GPIO_PORTD_DATA)
#define LCD_E_CR           (GPIO_PORTD_CONTROL)
#define LCD_E_PIN          (GPIO_PIN_2)



/*************switches *****************/

#define SW_REQ_DR            (GPIO_PORTD_DATA)
#define SW_REQ_CR            (GPIO_PORTD_CONTROL)
#define SW_REQ_PIN_PORT      (GPIO_PIND_CHECK)
#define SW_REQ_PIN           (GPIO_PIN_6)


#define SW_CANCEL_DR         (GPIO_PORTD_DATA)
#define SW_CANCEL_CR         (GPIO_PORTD_CONTROL)
#define SW_CANCEL_PIN_PORT   (GPIO_PIND_CHECK)
#define SW_CANCEL_PIN        (GPIO_PIN_5)


#define SW_CORRECT_DR        (GPIO_PORTD_DATA)
#define SW_CORRECT_CR        (GPIO_PORTD_CONTROL)
#define SW_CORRECT_PIN_PORT  (GPIO_PIND_CHECK)
#define SW_CORRECT_PIN       (GPIO_PIN_7)


#define SW_OK_DR			 (GPIO_PORTD_DATA)
#define SW_OK_CR		     (GPIO_PORTD_CONTROL)
#define SW_OK_PIN_PORT       (GPIO_PIND_CHECK)
#define SW_OK_PIN            (GPIO_PIN_3)



/************** motor*****************/

#define MOTOR_DR         (GPIO_PORTC_DATA)
#define MOTOR_CR         (GPIO_PORTC_CONTROL)
#define MOTOR_PIN_PORT   (GPIO_PINC_CHECK)
#define MOTOR_PIN        (GPIO_PIN_5)


/************** Warning led*****************/

#define WLED_DR         (GPIO_PORTC_DATA)
#define WLED_CR         (GPIO_PORTC_CONTROL)
#define WLED_PIN_PORT   (GPIO_PINC_CHECK)
#define WLED_PIN        (GPIO_PIN_6)



/************** PROX SENSOR*****************/
#define PROXSENSOR_DR         (GPIO_PORTD_DATA)
#define PROXSENSOR_CR         (GPIO_PORTD_CONTROL)
#define PROXSENSOR_PIN_PORT   (GPIO_PIND_CHECK)
#define PROXSENSOR_PIN        (GPIO_PIN_4)


/************** Color sensor pins *****************/

#define COLOR_PIN1_DR         (GPIO_PORTC_DATA)
#define COLOR_PIN1_CR         (GPIO_PORTC_CONTROL)
#define COLOR_PIN1_PIN_PORT   (GPIO_PINC_CHECK)
#define COLOR_PIN1_PIN        (GPIO_PIN_2)


#define COLOR_PIN2_DR         (GPIO_PORTC_DATA)
#define COLOR_PIN2_CR         (GPIO_PORTC_CONTROL)
#define COLOR_PIN2_PIN_PORT   (GPIO_PINC_CHECK)
#define COLOR_PIN2_PIN        (GPIO_PIN_3)


#define COLOR_PIN3_DR         (GPIO_PORTC_DATA)
#define COLOR_PIN3_CR         (GPIO_PORTC_CONTROL)
#define COLOR_PIN3_PIN_PORT   (GPIO_PINC_CHECK)
#define COLOR_PIN3_PIN        (GPIO_PIN_4)


					 
 #endif /* PORT_H_ */