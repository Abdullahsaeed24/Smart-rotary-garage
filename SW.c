/*
 * sw.c
 *
 * Created: 10/27/2019 11:09:24 AM
 *  Author: Abdullah saeed+
 */ 

 #include "sw.h"
 #include "Port.h"
 
 
 
 #define N_SW          (3)
 #define N_SAMPLES     (2)
 #define PRESSED_VOLT  (1)
 #define RELEASED_VOLT (0)
 #define SW_PERIOD	   (20)
 #define OS_PERIOD     (10)
 
  
 typedef struct
				{
		       tBYTE sw_samples[N_SAMPLES];
			   tSW_state sw_state;
				}SW_INFO;
 
 
 static SW_INFO sw_info[N_SW];
 
 
 void SW_init(tSW sw , tSW_state state)
 {
	switch(sw)
	{
		case SW_REQ:
		GPIO_InitPortPin(SW_REQ_CR, SW_REQ_PIN , GPIO_IN);
		break;
		
		case SW_CANCEL:
		GPIO_InitPortPin(SW_CANCEL_CR, SW_CANCEL_PIN , GPIO_IN);
		break;
		
		case SW_PROXSENS:
		GPIO_InitPortPin(PROXSENSOR_CR, PROXSENSOR_PIN , GPIO_IN);
		break;
			  
		default:
		/*do not come here */
		break;
	}
  
	switch(state)
	{
	case SW_RELEASED:
	case SW_PRE_RELEASED:
	sw_info[sw].sw_samples[0]=RELEASED_VOLT;
    sw_info[sw].sw_samples[1]=RELEASED_VOLT;
	break;
	
	case SW_PRESSED:
	case SW_PRE_PRESSED:
	sw_info[sw].sw_samples[0]=PRESSED_VOLT;
	sw_info[sw].sw_samples[1]=PRESSED_VOLT;	
	break;	
	
	default:
	/* do not come here*/
	break;
	}

 }



 tSW_state GET_SW_STATE(tSW sw)
 {
	tSW_state ret ;
	ret = sw_info[sw].sw_state;
	return ret ;
 
 }
 void SW_update(void)
{
	
 
tUByte INDEX = SW_REQ ;
	
	for (INDEX = SW_REQ ; INDEX <= SW_PROXSENS ; INDEX ++ )
	{
		
		sw_info[INDEX].sw_samples[0] = sw_info[INDEX].sw_samples[1];

		
		if (INDEX == SW_REQ)
		{
			sw_info[INDEX].sw_samples[1] = GPIO_ReadPortPin(SW_REQ_PIN_PORT, SW_REQ_PIN );
			
		}
		
	   
	   else if (INDEX == SW_CANCEL)
		{
			sw_info[INDEX].sw_samples[1] = GPIO_ReadPortPin(SW_CANCEL_PIN_PORT, SW_CANCEL_PIN );
			
		}


		else if (INDEX == SW_PROXSENS)
		{

			sw_info[INDEX].sw_samples[1] = GPIO_ReadPortPin(PROXSENSOR_PIN_PORT, PROXSENSOR_PIN );

			
		}
		

		else 
		{
		/*
		
		*/
		
		}

	switch(sw_info[INDEX].sw_state)
	{
		case SW_RELEASED:
		if ((sw_info[INDEX].sw_samples[0] == PRESSED_VOLT) && 
		   (sw_info[INDEX].sw_samples[1] == PRESSED_VOLT))
		{
			
			sw_info[INDEX].sw_state = SW_PRE_PRESSED ;
		
		}
		
		break;
		
		case SW_PRE_PRESSED:
		if  (sw_info[INDEX].sw_samples[1] == PRESSED_VOLT)
		{
			sw_info[INDEX].sw_state = SW_PRESSED ;
		
		}
		
		break;	
		
		case SW_PRESSED:
		if ((sw_info[INDEX].sw_samples[0] == RELEASED_VOLT) &&
		   (sw_info[INDEX].sw_samples[1] == RELEASED_VOLT))
		{
			
			sw_info[INDEX].sw_state = SW_PRE_RELEASED ;
		}
		
		break;
		
		case SW_PRE_RELEASED:
		if (sw_info[INDEX].sw_samples[1] == RELEASED_VOLT)
		{
			
			sw_info[INDEX].sw_state = SW_RELEASED ;
		}
		
		break;
		
		default:
		/**/
		break;
		
	}
	




	}
	
	
	
}
