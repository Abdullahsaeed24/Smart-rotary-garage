/*
 * request.h
 *
 * Created: 7/18/2020 5:32:07 PM
 *  Author: abdal
 */ 


#ifndef REQUEST_H_
#define REQUEST_H_



typedef enum
			{
		NO_REQ,
		CHOOSE,		
		ENTER ,
		EXTRACT,
 
			}tREQUEST;



   
 


void req_init(void);
void req_update(void);
tREQUEST Get_req(void);
void Set_req_type(tREQUEST request);

#endif /* REQUEST_H_ */