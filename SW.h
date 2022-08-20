/*
 * sw1.h
 *
 * Created: 10/27/2019 11:09:36 AM
 *  Author: Abdullah saeed
 */ 


 #ifndef SW1_H_
 #define SW1_H_
 
#include "Port.h"

 typedef enum
             { 	 
	        SW_REQ ,
			SW_CANCEL,
			SW_PROXSENS,
   	         }tSW;
  
 
 typedef enum
			{
			SW_RELEASED ,
			SW_PRE_PRESSED ,
			SW_PRESSED ,
			SW_PRE_RELEASED
			}tSW_state;
			 
 void SW_init(tSW sw , tSW_state state);
 tSW_state GET_SW_STATE(tSW sw);
 void SW_update(void);
  
 
 #endif /* SW1_H_ */