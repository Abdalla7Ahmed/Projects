/*
 * Alarm.h
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#ifndef ALARM_H_
#define ALARM_H_
#include "State.h"
enum
{
	LED_off,
	LED_on,
	LED_Waiting
}Alarm_state_id;

/************** Declare state function  ****************/
STATE_define(LED_Waiting);
STATE_define(LED_off);
STATE_define(LED_on);
STATE_define(LED_Init);


/***************** state pointer to function *********************/
extern void (*Alarm_STATE)();


#endif /* ALARM_H_ */
