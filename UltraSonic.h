/*
 * IncFile1.h
 *
 * Created: 5/11/2020 11:01:55 PM
 *  Author: Abdullah saeed
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include "LCD.h"
#include "Time.h"
#include "Port.h"

typedef enum 
			{
			OBJECT_DETECTED,
			OBJECT_NOT_DETECTED
	
	      	}tULTRASONIC_STATE;


void ultrasonic(void);
double GET_ULTRASONIC_DISTANCE(void);
void ultrasonic_init(void);

#endif /* INCFILE1_H_ */