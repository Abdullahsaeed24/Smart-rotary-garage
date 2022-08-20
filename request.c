/*
 * request.c
 *
 * Created: 7/18/2020 5:31:43 PM
 *  Author: abdal
 */ 

#define  F_CPU  8000000ul
#include <util/delay.h>
#include "request.h"
#include "SW.h"
#include "LCD.h"
#include "keypad.h"

#define LOC_NUM  (6)

static tREQUEST req = NO_REQ ;


 

	void req_update(void)
	{
	char key;
	
	
	switch(req)
	{
	
	case NO_REQ:

	if (GPIO_ReadPortPin(SW_REQ_PIN_PORT ,SW_REQ_PIN)==1)
	{
		while(GPIO_ReadPortPin(SW_REQ_PIN_PORT ,SW_REQ_PIN)==1);
	
	req = CHOOSE ;
	return;
	
	}
 
   break;

			

   case CHOOSE:
     if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
    {
	   while (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1);
	    
		req = NO_REQ ;
		return;
		
	}
   else{
   key = KeyPad_Scan();
   
   if (key == 1)
   {
   
   req = ENTER ;

	return ;
   }

   else if (key == 2)
   {
   req = EXTRACT ;
	return ;

   }

   }
   break;




   case ENTER:	

	if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
	  {
	
		while(GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1);
	
		   req = NO_REQ ;
		   return;
		   
	   }
	     
   break;



 
   case EXTRACT:

		if (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1)
		{
		
		while (GPIO_ReadPortPin(SW_CANCEL_PIN_PORT ,SW_CANCEL_PIN)==1);
	        req = NO_REQ ;
	        return;
	        
        } 

   break;
   
 
  default:

  break;


   }

        }




/**********************************************************************************************/

  tREQUEST Get_req(void)
  {
	
	return req;
	
	
  }


/*********************************************************************************************/
   void Set_req_type(tREQUEST request )
   {
 	
 	
 	req = request ;
 	 
 }  