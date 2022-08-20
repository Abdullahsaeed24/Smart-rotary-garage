/*
 * garage.c
 *
 * Created: 7/18/2020 10:53:30 PM
 *  Author: abdal
 */ 
#define  F_CPU  8000000ul
#include <util/delay.h>
#define  F_CPU  8000000ul
#include "garage.h"
#include "request.h"
#include "LCD.h"
#include "keypad.h"
#include "SW.h"
#include "motor.h"
#include "warningled.h"
#include "UltraSonic.h"


#define  LOC_NUM (6)

static tLOCATION_STATE location_data[LOC_NUM];

tUByte available_locations[LOC_NUM];
tUByte Notavailable_locations[LOC_NUM];

static tUByte availableloc=0;
static tUByte Notavailableloc=0;
static tREQUEST re;


static void no_req_function(void);
static void enter_function(void);
static void extract_function(void);
static void choose_function(void);

static void detect_which_location_enter(tUByte locarion);
static void detect_which_location_extract(tUByte locarion);


static tUByte scan_counter = 0;


void garage_scan(void)
{
	
	/** motor on **/
	motor_on();
	 _delay_ms(150);
	while(scan_counter <= LOCATION6)
	{
	
	
	/** check the proxsensor is seeing any location **/
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not 
	/** if yes motor off , ask is what is the coloer of locaton  **/
	motor_off();
	
	ultrasonic();
	_delay_ms(600);
	 
	/** test which the color of location   **/
	
	// is that color is white color 
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) && 
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	{
	
	ultrasonic();
	// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 6.000))
	{
	
	scan_counter ++;

	// store the location state in the data base  
		location_data[LOCATION1] = FILL ;
	
		// turn on the motor
		motor_on();
		_delay_ms(100);
		
	
	}
	
	
	else if (GET_ULTRASONIC_DISTANCE() > 6.00)
	{

	scan_counter ++;

	 // store the location state in the data base
		location_data[LOCATION1] = EMPTY ;
			// turn on the motor
			motor_on();
			_delay_ms(100);
				
	
	}
		
	

	}
	
	
	
	// is that color is Black color 
	else if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	
	{

	ultrasonic();

	// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 6.000))
	{
		scan_counter ++;

		// store the location state in the data base
		location_data[LOCATION2] = FILL ;
		// turn on the motor
		motor_on();
		//wled_on();
		_delay_ms(100);
			
		
	}
	
	
	else if (GET_ULTRASONIC_DISTANCE() > 6.00)
	{

		// store the location state in the data base
		location_data[LOCATION2] = EMPTY ;
		scan_counter ++;
		
			// turn on the motor
			motor_on();
			//wled_on();
			_delay_ms(100);
			
	}
	
	

	}
	
	
	// is that color is Green color 
	else if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	
	{
	ultrasonic();

	// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 6.000))
	{
		scan_counter ++;
		
		// store the location state in the data base
		location_data[LOCATION3] = FILL ;
			// turn on the motor
			motor_on();
			//wled_on();
			_delay_ms(100);
			
		
	}
	
	
		else if (GET_ULTRASONIC_DISTANCE() > 6.00)
	{

		scan_counter ++;
		
		// store the location state in the data base
		location_data[LOCATION3] = EMPTY ;
			// turn on the motor
			motor_on();
			//wled_on();
			_delay_ms(100);
			
		
	}
	
	
	}
	
	
	// is that color is Red color 	
	else if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
	
	{
		ultrasonic();

	// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 6.000))
	{
		scan_counter ++;
				
		// store the location state in the data base
		location_data[LOCATION4] = FILL ;
		
		// turn on the motor
		motor_on();
		//wled_on();
		_delay_ms(100);
			
	}
	
	
	else if (GET_ULTRASONIC_DISTANCE() > 6.00)
	{
		scan_counter ++;
		
		// store the location state in the data base
		location_data[LOCATION4] = EMPTY ;
		
			// turn on the motor
			motor_on();
			//wled_on();
			_delay_ms(100);
			
	}
	
	

	}
		
	
	
	// is that color is Yellow color 
	else if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
	{
	
	ultrasonic();	
	// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 7.000))
	{
		scan_counter ++;
		
		// store the location state in the data base
		location_data[LOCATION5] = FILL ;
			// turn on the motor
			motor_on();
			//wled_on();
			_delay_ms(100);
			
		
	}
	
	
	else if (GET_ULTRASONIC_DISTANCE() > 6.00)
	{

		// store the location state in the data base
		location_data[LOCATION5] = EMPTY ;
		scan_counter ++;
		// turn on the motor
		motor_on();
		//wled_on();
		_delay_ms(100);
			
		
	}
	
	
	}

		
	
	// is that color is Blue color 
	else if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
	{
		
	ultrasonic();
		// ask is the location is fill or empty
	if ((GET_ULTRASONIC_DISTANCE()>= 3.00) && (GET_ULTRASONIC_DISTANCE()<= 7.000))
	{
		scan_counter ++;
		
		// store the location state in the data base
		location_data[LOCATION6] = FILL ;
		
		// turn on the motor
		motor_on();
		//wled_on();
		_delay_ms(100);
			
	}
	
	
	else if (GET_ULTRASONIC_DISTANCE() > 7.00)
	{

		// store the location state in the data base
		location_data[LOCATION6] = EMPTY ;
		
		// turn on the motor
		motor_on();
		//wled_on();
		_delay_ms(100);
			
	}
	
	
	}
		
		// is that color is no color 
	else {
		
		// keep turning on the motor 
		motor_on();
		//wled_on();
		_delay_ms(100);
		 }	
	
	
	
	
	}
		
	/* is that location empty or fill !!*/
	
	
	/*********************************************************************************************************************/
	
	tUByte counter=0;
	/*tBYTE key;*/
	availableloc = 0;
	Notavailableloc=0;

	motor_off();
	wled_off();

	for(counter = LOCATION1 ; counter <= LOCATION6 ; counter++)

	{
		if(location_data[counter]== EMPTY)
		{
			
			available_locations[availableloc] = counter ;
			availableloc ++;
			

		}
		
		
		else if(location_data[counter] == FILL)
		{
			Notavailable_locations[Notavailableloc] = counter ;
			Notavailableloc ++ ;
			
		}
		
		
		
	}
	
	
	// scan the array
	
	
	
	// distinguish the available locations and the not available
	
	tUByte loc=0 ;
	
	// display the available locations number
	for(counter = 0 ; counter < availableloc ;counter++)
	{
		
		LCD_SendString("AVAILABLE LOCATIONS",0);
		LCD_SendChar( available_locations[counter]+'0',1,loc);
		LCD_SendChar( ' ',1,loc+1);
		
		loc = loc +2;
		
	}

	loc =0;
	


	
	if (availableloc == 0)
	{

	
		LCD_SendString("Sorry The Garage  ",0);
		LCD_SendString("     Is Full      ",1);
	
	}


	else if (availableloc == 1)
	{
		
		LCD_SendChar(' ',1,2);
		LCD_SendChar(' ',1,3);
		LCD_SendChar(' ',1,4);
		LCD_SendChar(' ',1,5);
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		

	}

	if (availableloc == 2)
	{
		LCD_SendChar(' ',1,4);
		LCD_SendChar(' ',1,5);
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar( ' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);

		

	}

	
	if (availableloc == 3)
	{
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar( ' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		
		
		

	}

	
	if (availableloc == 4)
	{

		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar(' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		
	}

	if (availableloc == 5)
	{
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar(' ',1,12);
		LCD_SendChar(' ',1,13);
		LCD_SendChar(' ',1,14);
		LCD_SendChar( ' ',1,15);


	}

	if (availableloc == 6)
	{LCD_SendChar(' ',1,12);
		LCD_SendChar(' ',1,13);
		LCD_SendChar(' ',1,14);
		LCD_SendChar( ' ',1,15);


	}

_delay_ms(1000);
motor_off();
	
	/**********************************************************************************************************************/
	
}



/*************************************************************************************************************/



void garage_update(void)
{
	

	re=Get_req();
	
switch(re)
{
	

	 case NO_REQ:
	no_req_function();
	break;
	
	case CHOOSE:
	choose_function();
	break;
		


	case ENTER:
	//show the user the available locations
	//then ask the to enter the location number 
	enter_function();
	
	break;
	
	case EXTRACT:
	// ask the user for locations number
	extract_function(); 
	break;
	
	

	default:
	break;	
		

}	
	
	
}

static void no_req_function(void)
{
	
	LCD_SendString("  Smart Garage     ",0);
	LCD_SendString("                  ", 1);

}



static void enter_function(void)
{
	
	
	tUByte counter=0;
	tBYTE key;
	availableloc = 0;
 	Notavailableloc=0;


	for(counter = LOCATION1 ; counter <= LOCATION6 ; counter++)

	{
		if(location_data[counter]== EMPTY)
		{
			
			available_locations[availableloc] = counter ;
			availableloc ++;
			

		}
		
		
		else if(location_data[counter] == FILL)
		{
			Notavailable_locations[Notavailableloc] = counter ;
			Notavailableloc ++ ;
			
		}
		
		
		
	}
	
	
	// scan the array
	
	
	
	// distinguish the available locations and the not available
	
	tUByte loc=0 ;
	
	// display the available locations number
	for(counter = 0 ; counter < availableloc ;counter++)
	{
		
		LCD_SendString("Please Enter N ",0);
		LCD_SendChar( available_locations[counter]+'0',1,loc);
		LCD_SendChar( ' ',1,loc+1);
		
		loc = loc +2;
		
	}

	loc =0;
	


	
	if (availableloc == 0)
	{

		LCD_SendString("Sorry The Garage  ",0);
		LCD_SendString("     Is Full      ",1);
	}


	else if (availableloc == 1)
	{
		
		LCD_SendChar(' ',1,2);
		LCD_SendChar(' ',1,3);
		LCD_SendChar(' ',1,4);
		LCD_SendChar(' ',1,5);
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		

	}

	if (availableloc == 2)
	{
		LCD_SendChar(' ',1,4);
		LCD_SendChar(' ',1,5);
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar( ' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);

		

	}

	
	if (availableloc == 3)
	{
		LCD_SendChar(' ',1,6);
		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar( ' ',1,11);
		LCD_SendChar( ' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		
		
		

	}

	
	if (availableloc == 4)
	{

		LCD_SendChar(' ',1,7);
		LCD_SendChar(' ',1,8);
		LCD_SendChar(' ',1,9);
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar(' ',1,12);
		LCD_SendChar( ' ',1,13);
		LCD_SendChar( ' ',1,14);
		LCD_SendChar( ' ',1,15);
		
	}

	if (availableloc == 5)
	{
		LCD_SendChar(' ',1,10);
		LCD_SendChar(' ',1,11);
		LCD_SendChar(' ',1,12);
		LCD_SendChar(' ',1,13);
		LCD_SendChar(' ',1,14);
		LCD_SendChar( ' ',1,15);


	}

	if (availableloc == 6)
	{LCD_SendChar(' ',1,12);
		LCD_SendChar(' ',1,13);
		LCD_SendChar(' ',1,14);
		LCD_SendChar( ' ',1,15);


	}

	counter =0;
	

	
	if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
	{
		while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1);
					Set_req_type( NO_REQ) ;
					
		
		availableloc =0;
		Notavailableloc =0;
		
		return;
		
	}
	
	
	
	key = KeyPad_Scan();
	
	if (key == available_locations[0])	
	
	{
 
		wled_on(); 
		detect_which_location_enter(available_locations[0]);
		wled_off();



	}
		
		
		
		
  else if (key == available_locations[1])
	{
		
		wled_on();
		detect_which_location_enter(available_locations[1]);
		wled_off();
	
		
	}
	



	else if (key == available_locations[2])
	{

		wled_on();
		detect_which_location_enter(available_locations[2]);
		wled_off();

	}
		
		
		
		
		
		
	else if (key == available_locations[3])
	{

		wled_on();
		detect_which_location_enter(available_locations[3]);
		wled_off();
	}
		
		
   else if (key == available_locations[4])
	{
		wled_on();
		detect_which_location_enter(available_locations[4]);
		wled_off();
	
	}
		
		
	else if (key == available_locations[5])
	{
		wled_on();
		detect_which_location_enter(available_locations[5]);
		wled_off();

	}
		
		

		else {
			
			if (key != 13 &&(key<=5) && (key>=0))
			
			{

				LCD_SendString ("WRONG NUMBER..... ",0);
				LCD_SendString ("PLEASE TRY AGAIN...",1);

				//location_data[Notavailable_locations[counter]] = EMPTY;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( ENTER) ;
				wled_off();
				motor_off();
				_delay_ms(500);
				return;

				
			}
			
		


}
}


/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
static void extract_function(void)
{
	
	

	tUByte counter =0;
	tBYTE key=13;

	Notavailableloc = 0;
	availableloc= 0;

	for(counter = LOCATION1 ; counter <= LOCATION6 ; counter++)

	{

	
		if(location_data[counter] == EMPTY)
		{
			
			available_locations[availableloc] = counter ;
			availableloc ++;
			

		}
		
		
		else if(location_data[counter] == FILL)
		{
			Notavailable_locations[Notavailableloc] = counter ;
			Notavailableloc ++ ;

		}
		
		
	}



	if (Notavailableloc == 0)
	{

		LCD_SendString("Sorry The Garage  ",0);
		LCD_SendString("     Is Empty     ",1);
		_delay_ms(800);
		Set_req_type(NO_REQ);
		return;

	}



	else if(Notavailableloc != 0)
	{
		

		tUByte loc=0 ;
		
		// display the available locations number
		for(counter = 0 ; counter < Notavailableloc ;counter++)
		{
			
			LCD_SendString("Enter Location N",0);
			LCD_SendChar( Notavailable_locations[counter]+'0',1,loc);
			LCD_SendChar( ' ',1,loc+1);
			
			loc = loc +2;
			
			
		}


		
		if (Notavailableloc == 1)
		{
			
			LCD_SendChar(' ',1,2);
			LCD_SendChar(' ',1,3);
			LCD_SendChar(' ',1,4);
			LCD_SendChar(' ',1,5);
			LCD_SendChar(' ',1,6);
			LCD_SendChar(' ',1,7);
			LCD_SendChar(' ',1,8);
			LCD_SendChar(' ',1,9);
			LCD_SendChar(' ',1,10);
			LCD_SendChar(' ',1,11);
			LCD_SendChar( ' ',1,12);
			LCD_SendChar( ' ',1,13);
			LCD_SendChar( ' ',1,14);
			LCD_SendChar( ' ',1,15);
			

		}

		if (Notavailableloc == 2)
		{
			
			LCD_SendChar(' ',1,4);
			LCD_SendChar(' ',1,5);
			LCD_SendChar(' ',1,6);
			LCD_SendChar(' ',1,7);
			LCD_SendChar(' ',1,8);
			LCD_SendChar(' ',1,9);
			LCD_SendChar(' ',1,10);
			LCD_SendChar( ' ',1,11);
			LCD_SendChar( ' ',1,12);
			LCD_SendChar( ' ',1,13);
			LCD_SendChar( ' ',1,14);
			LCD_SendChar( ' ',1,15);

			

		}


		if (Notavailableloc == 3)
		{
			
			LCD_SendChar(' ',1,5);
			LCD_SendChar(' ',1,6);
			LCD_SendChar(' ',1,7);
			LCD_SendChar(' ',1,8);
			LCD_SendChar(' ',1,9);
			LCD_SendChar(' ',1,10);
			LCD_SendChar( ' ',1,11);
			LCD_SendChar( ' ',1,12);
			LCD_SendChar( ' ',1,13);
			LCD_SendChar( ' ',1,14);
			LCD_SendChar( ' ',1,15);
			
			
			

		}


		if (Notavailableloc == 4)
		{

			LCD_SendChar(' ',1,7);
			LCD_SendChar(' ',1,8);
			LCD_SendChar(' ',1,9);
			LCD_SendChar(' ',1,10);
			LCD_SendChar(' ',1,11);
			LCD_SendChar(' ',1,12);
			LCD_SendChar( ' ',1,13);
			LCD_SendChar( ' ',1,14);
			LCD_SendChar( ' ',1,15);
			
		}

		if (Notavailableloc == 5)
		{
			LCD_SendChar(' ',1,10);
			LCD_SendChar(' ',1,11);
			LCD_SendChar(' ',1,12);
			LCD_SendChar(' ',1,13);
			LCD_SendChar(' ',1,14);
			LCD_SendChar( ' ',1,15);


		}

		if (Notavailableloc == 6)
		{LCD_SendChar(' ',1,12);
			LCD_SendChar(' ',1,13);
			LCD_SendChar(' ',1,14);
			LCD_SendChar( ' ',1,15);


		}




		if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
		{
			while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1);
			Set_req_type( NO_REQ) ;
						
			availableloc =0;
			Notavailableloc =0;
			return;	
		
		}

		
		
		
		key = KeyPad_Scan();


	if (key == Notavailable_locations[0])
		{
		
		wled_on();
		detect_which_location_extract( Notavailable_locations[0]);
 		wled_off();		
		
		}
		



		else if (key == Notavailable_locations[1])
		{
		
		wled_on();
		detect_which_location_extract( key);
		wled_off();
		
		}
		


		else if (key == Notavailable_locations[2])
		{
			
		wled_on();
		detect_which_location_extract( Notavailable_locations[2]);
		wled_off();
		
		}
		
		
		
		
		
		
		else if (key == Notavailable_locations[3])
		{
			
		wled_on();	
		detect_which_location_extract( Notavailable_locations[3]);
		wled_off();
		
		}
		
		
		
		else if (key == Notavailable_locations[4])
		{
		
		wled_on();
		detect_which_location_extract( Notavailable_locations[4]);
		wled_off();	
		
		}
	
	
		else if (key == Notavailable_locations[5])
		{
		
		wled_on();
		detect_which_location_extract( Notavailable_locations[5]);
		wled_off();
		
		}
	
	

	
	else {
	
 	
	 	if (key != 13 &&(key<=5) && (key>=0))
     
		{

 			LCD_SendString ("WRONG NUMBER..... ",0);
 			LCD_SendString ("PLEASE TRY AGAIN...",1);

 			//location_data[Notavailable_locations[counter]] = EMPTY;
 			availableloc =0;
 			Notavailableloc =0;
 			Set_req_type( EXTRACT) ;
 			_delay_ms(500);
 			return;

	
		}
			
	       }
	

				}
								
				
						}





static void choose_function(void)
{

	LCD_SendString("1-Enter Car         ",0);
	LCD_SendString("2-Extract Car         ", 1);
	

}


static void detect_which_location_enter(tUByte locarion)

{
	
	
	if (locarion == 0)
	{
		
		LCD_SendString("Wait Preparing ",0);
		LCD_SendString("Location 0 !!    ",1);
		

	while(1)
	{
		
		
		//wait until the car has been located
		motor_on();
		
		_delay_ms(200);
		
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
		motor_off();
		_delay_ms(600);
		
		// is that color is white color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
		
		{
							LCD_SendString("Location 0 Ready !  ",0);
							LCD_SendString("Please Enter Car    ",1);

			_delay_ms(100);
			// wait for car has been located successfully
			while(1)
			{
				
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
					
					LCD_SendString("Please Press OK  ",0);
					LCD_SendString("To Ensure order  ",1);

					
					motor_off(); // turn off the motor
					
					
					
					//wait till the user sure the request
					
					
					if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[0] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						
						motor_off();
						
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[0] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						motor_off();
						_delay_ms(500);
						return;
						
					}
					
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[0] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
					
					
				}
			}
		}
	
	
	
	 }	
  }
  
  
  
	if (locarion == 1)
	{

		
		LCD_SendString("Wait Preparing ",0);
		LCD_SendString("Location 1 !!    ",1);
		
		
		while(1)
		{
		
		
			//wait until the car has been located
			motor_on();
			
			_delay_ms(200);
			while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
			motor_off();
			_delay_ms(600);
			
		
			// is that color is black color
			if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
				(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
				(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
		
				{
					
					LCD_SendString("Location 1 Ready !  ",0);
					LCD_SendString("Please Enter Car    ",1);
		
				// wait for car has been located successfully
				while(1)
				{
				
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
					
	
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);

				motor_off(); // turn off the motor
					
					
					//wait till the user sure the request
					
					if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[1] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
					
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[1] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[1] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
					
					
				}
			}
		}
	} 
  }




if (locarion == 2)
{


LCD_SendString("Wait Preparing ",0);
LCD_SendString("Location 2 !!    ",1);

	while(1)
	{
		
		
		//wait until the car has been located
		motor_on();
		wled_on();
		_delay_ms(200);
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
		motor_off();
		_delay_ms(600);
		
		// is that color is Green color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
		
		{

				LCD_SendString("Location 2 Ready !  ",0);
				LCD_SendString("Please Enter Car    ",1);

	
			// wait for car has been located successfully
			while(1)
			{
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
				
					
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);
				
					motor_off(); // turn off the motor
					
					
				//wait till the user sure the request
		
				if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
				{
			
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[2] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[2] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();	
						_delay_ms(500);
						return;
						
					}
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[2] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
					
					
				}
			}
		}
	}
}



if (locarion == 3)
{


LCD_SendString("Wait Preparing ",0);
LCD_SendString("Location 3 !!    ",1);

	while(1)
	{
		
		
		//wait until the car has been located
		motor_on();
		_delay_ms(200);
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
		motor_off();
		_delay_ms(600);
		
		// is that color is white color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
		
		{


				LCD_SendString("Location 3 Ready !  ",0);
				LCD_SendString("Please Enter Car    ",1);
			
			wled_on();   //turn on the warning led
			// wait for car has been located successfully
			while(1)
			{
				
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
					
						
						LCD_SendString("Please Press OK  ",0);
						LCD_SendString("To Ensure order  ",1);
							
					motor_off(); // turn off the motor
					
					
					//wait till the user sure the request
					
					//wait till the user sure the request
					
					if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
		
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[3] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[3] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[3] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
					
					
				}
			}
		}
	}
}



if (locarion == 4)
{

LCD_SendString("Wait Preparing ",0);
LCD_SendString("Location 4 !!    ",1);

	while(1)
	{
		
		
		//wait until the car has been located
		motor_on();
		_delay_ms(200);
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
		motor_off();
		_delay_ms(600);
		
		// is that color is Yellow color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
		
		{
				
				LCD_SendString("Location 4 Ready !  ",0);
				LCD_SendString("Please Enter Car    ",1);
				
			wled_on();   //turn on the warning led
			// wait for car has been located successfully
			while(1)
			{
				
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
							
							LCD_SendString("Please Press OK  ",0);
							LCD_SendString("To Ensure order  ",1);
							
					
					motor_off(); // turn off the motor
					
					
					//wait till the user sure the request
					
						//wait till the user sure the request
						
					if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
					{
							
						while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
	
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[4] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[4] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[4] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
					
					
				}
			}
		}
	}
}



if (locarion == 5)
{
LCD_SendString("Wait Preparing ",0);
LCD_SendString("Location 5 !!    ",1);

	while(1)
	{
		
		
		//wait until the car has been located
		motor_on();
		_delay_ms(200);
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
		
		motor_off();
		_delay_ms(600);
		
		// is that color is Blue color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
		
		{
			
				LCD_SendString("Location 5 Ready !  ",0);
				LCD_SendString("Please Enter Car    ",1);
										
			
			// wait for car has been located successfully
			while(1)
			{
				
				ultrasonic();
				_delay_ms(50);
				if(GET_ULTRASONIC_DISTANCE() <= 6.00)
				{
					
										LCD_SendString("Please Press OK  ",0);
										LCD_SendString("To Ensure order  ",1);
		
					motor_off(); // turn off the motor
					
					
					//wait till the user sure the request
					
					if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
						
						LCD_SendString (" Success Process  ",0);
						LCD_SendString ("     Done!        ",1);
						
						location_data[5] = FILL;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();	
						_delay_ms(500);
						return;
						
					}
					
					
					
					if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
					{
						
						while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
						
						LCD_SendString ("Operation has   ",0);
						LCD_SendString ("Canceled !!!!   ",1);
						
						
						location_data[5] = EMPTY;
						availableloc =0;
						Notavailableloc =0;
						Set_req_type( NO_REQ) ;
						wled_off();
						_delay_ms(500);
						return;
						
					}
					

				}
				
				

				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[5] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();	
					_delay_ms(500);
					return;
					
					
					
				}
			}
	    }
	 }
  }
}




static void detect_which_location_extract(tUByte locarion)
{
	
	if (locarion == 0)

		{	LCD_SendString("Wait Preparing ",0);
			LCD_SendString("Location 0 !!    ",1);

		
		

	while(1)
	{
	
		// motor on 
		motor_on();
		wled_on(); //turn on the warning led
		_delay_ms(200);
		// wait tell the sensor see the location 
		while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	
		// motor off 
		motor_off();
		_delay_ms(600);
	
		// ask for which color 
		// if color is white so it okay 
	
	
		// is that color is white color
		if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
		(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
		(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	
		{
	

			LCD_SendString("Location 0 Ready !  ",0);
			LCD_SendString("PLZE Extract Car    ",1);

				_delay_ms(50);
		// wait for car has been located successfully
		while(1)
		{
		
			// get the distance 
			ultrasonic();
			_delay_ms(50);
		
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
				
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);

								
				//wait till the user sure the request
				
				if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)
				{
					
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
					
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					
					location_data[0] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[0] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[0] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
			  }
		   }
	    }
	 }
	
	}
	
	
		
	else if (locarion == 1)
	{
		
	 		LCD_SendString("Wait Preparing ",0);
	 		LCD_SendString("Location 1 !!    ",1);
	 		
	 
	 while(1)
	 {
		 
	 
	// motor on
	motor_on();

	_delay_ms(200);
	// wait tell the sensor see the location
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	// motor off
	motor_off();
	_delay_ms(600);
	
	// ask for which color
	// if color is white so it okay
	
	// is that color is black color
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	
	{
		
					LCD_SendString("Location 1 Ready !  ",0);
					LCD_SendString("PLZE Extract Car     ",1);

		_delay_ms(100);
		// wait for car has been located successfully
		while(1)
		{
			
			
			// get the distance
			ultrasonic();
			_delay_ms(50);
			
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
				
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);
		
				
				
			if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)
				
			 {
	
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					
					wled_off(); //turn off the warning led
					location_data[1] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[1] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[1] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
		   }
	    }	
	 }
  }
		
	}

	else if (locarion == 2)
	{
		
		
	LCD_SendString("Wait Preparing ",0);
	LCD_SendString("Location 2 !!    ",1);
		
		
	while (1)
	{
		
		
	// motor on
	motor_on();
	_delay_ms(100);
	// wait tell the sensor see the location
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	// motor off
	motor_off();
	_delay_ms(600);
	
	// ask for which color
	// if color is white so it okay
	
	// is that color is green color
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 0))
	
	{
		
				LCD_SendString("Location 2 Ready !  ",0);
				LCD_SendString("PLZE Extract Car     ",1);
	
			_delay_ms(100);
		// wait for car has been located successfully
		while(1)
		{
			
			// get the distance
			ultrasonic();
			
			_delay_ms(50);
			
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
				
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);
				
				
				
				//wait till the user sure the request
				
		  if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)	
			{
		
				while(GPIO_ReadPortPin(SW_OK_PIN_PORT , SW_OK_PIN) == 1);
	
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					wled_off(); //turn off the warning led
					location_data[2] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[2] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[2] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
			}
	 	}
	 }				 
  }

}


	else if (locarion == 3)
	
	{
		
	LCD_SendString("Wait Preparing ",0);
	LCD_SendString("Location 3 !!    ",1);


	while(1)
	
	{
		
	
	// motor on
	motor_on();
	
	_delay_ms(200);
	// wait tell the sensor see the location
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	// motor off
	motor_off();
	_delay_ms(600);
	// ask for which color
	// if color is white so it okay
	
	// is that color is red color
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
	
	{
		
		
		LCD_SendString("Location 3 Ready !  ",0);
		LCD_SendString("PLZE Extract Car       ",1);
	
		
		// wait for car has been located successfully
		while(1)
		{
			
			// get the distance
			ultrasonic();
			
			
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
				
				LCD_SendString("Please Press OK  ",0);
				LCD_SendString("To Ensure order  ",1);
				
				
				
				if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)
				{
					
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					
					wled_off(); //turn off the warning led
					location_data[3] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[3] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[3] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
			}
		}
	}					
 }	
	
	}
	
	else if (locarion == 4)
	{
		
		LCD_SendString("Wait Preparing ",0);
		LCD_SendString("Location 4 !!    ",1);
	
	while (1)
	{
	
		
	// motor on
	motor_on();
	_delay_ms(200);
	// wait tell the sensor see the location
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	// motor off
	motor_off();
	_delay_ms(600);
	// ask for which color
	// if color is white so it okay
	
	// is that color is white color
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
		
	{
			
			LCD_SendString("Location 4 Ready !  ",0);
			LCD_SendString("PLZE Extract Car     ",1);

		
		_delay_ms(100);
		
		// wait for car has been located successfully
		while(1)
		{
			
			// get the distance
			ultrasonic();
			
			
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
				
				
					LCD_SendString("Please Press OK  ",0);
					LCD_SendString("To Ensure order  ",1);
				
				
				//wait till the user sure the request
				if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)
				{
					
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					
					wled_off(); //turn off the warning led
					location_data[4] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[4] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[4] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
			}
		 }
	  }		
    }	
	}

	
	else if (locarion == 5)
	{
			LCD_SendString("Wait Preparing ",0);
			LCD_SendString("Location 5 !!    ",1);
			
	while(1)
	{
		
	// motor on
	motor_on();
	_delay_ms(200);
	
	// wait tell the sensor see the location
	while(GPIO_ReadPortPin(PROXSENSOR_PIN_PORT , PROXSENSOR_PIN) == 0);// test the proxsensor if seeing or not
	// motor off
	motor_off();
	_delay_ms(600);
	
	// ask for which color
	// if color is white so it okay
	
	
	// is that color is white color
	if ((GPIO_ReadPortPin(COLOR_PIN1_PIN_PORT , COLOR_PIN1_PIN) == 0) &&
	(GPIO_ReadPortPin(COLOR_PIN2_PIN_PORT , COLOR_PIN2_PIN) == 1) &&
	(GPIO_ReadPortPin(COLOR_PIN3_PIN_PORT , COLOR_PIN3_PIN) == 1))
		
	{
		
			
			LCD_SendString("Location 5 Ready !  ",0);
			LCD_SendString("PLZE Extract Car    ",1);

		
		_delay_ms(100);
		// wait for car has been located successfully
		while(1)
		{
			
			// get the distance
			ultrasonic();
			
			if(GET_ULTRASONIC_DISTANCE() > 7.00)
			{
								
					LCD_SendString("Please Press OK  ",0);
					LCD_SendString("To Ensure order  ",1);
		
				
				
				//wait till the user sure the request
				
				if (GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1)
				{
					
					while(GPIO_ReadPortPin(SW_OK_PIN_PORT ,SW_OK_PIN) == 1);
						
					
					LCD_SendString (" Success Process  ",0);
					LCD_SendString ("     Done!        ",1);
					
					wled_off(); //turn off the warning led
					location_data[5] = EMPTY;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				
				
				if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
				{
					
					while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
					
					LCD_SendString ("Operation has   ",0);
					LCD_SendString ("Canceled !!!!   ",1);
					
					
					location_data[5] = FILL;
					availableloc =0;
					Notavailableloc =0;
					Set_req_type( NO_REQ) ;
					wled_off();
					_delay_ms(500);
					return;
					
				}
				
				

			}
			
			

			if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
			{
				
				while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN) == 1);
				
				LCD_SendString ("Operation has   ",0);
				LCD_SendString ("Canceled !!!!   ",1);
				
				
				location_data[5] = FILL;
				availableloc =0;
				Notavailableloc =0;
				Set_req_type( NO_REQ) ;
				wled_off();
				_delay_ms(500);
				return;
				
				
			 }
		 }
	 }		
  }
	
}
	} 