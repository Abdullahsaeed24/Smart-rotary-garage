/*
 * garage.h
 *
 * Created: 7/18/2020 10:46:08 PM
 *  Author: abdal
 */ 


#ifndef GARAGE_H_
#define GARAGE_H_
#include "request.h"

 typedef enum
     		{
			LOCATION1, //WHITE	
			LOCATION2, //BLACK
			LOCATION3, //GREEN
			LOCATION4, //RED
			LOCATION5, //YALLOW
			LOCATION6, //BLUE
			
	     	}tGARAGE_LOCATION;
			 
// 			 
// 
// 	typedef enum
// 	{
// 		LOCATION1, //WHITE
// 		LOCATION2, //BLACK
// 		LOCATION3, //GREEN
// 		LOCATION4, //RED
// 		LOCATION5, //BLUE
// 		LOCATION6, //YALLOW
// 	
// 	}tGARAGE_LOCATION;


 typedef enum
		{
		EMPTY,
		FILL ,
		}tLOCATION_STATE;


			 

 typedef enum
 {
	 USER_PRESSED,
	 USER_NOTPRESSED ,
 }tUSER_PRESS__STATE;
			
			
			
void garage_scan(void);
void garage_update(void);			
			
			




#endif /* GARAGE_H_ */
