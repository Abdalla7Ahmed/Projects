/*
 * Main_AL.h
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#ifndef MAIN_AL_H_
#define MAIN_AL_H_
#include "State.h"

enum
{
	M_Waiting,
	M_Sending,
	M_Checking
}Main_AL_state_id;

/************** Declare state function ****************/
STATE_define(M_Checking);
STATE_define(M_Waiting);
STATE_define(M_Sending);


/***************** state pointer to function *********************/
extern void (*MAL_STATE)();


#endif /* MAIN_AL_H_ */
