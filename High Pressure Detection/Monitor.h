/*
 * Monitor.h
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#ifndef MONITOR_H_
#define MONITOR_H_
#include "State.h"

enum
{
	Alarm_off,
	Alarm_on,
	Alarm_Waiting
}M_state_id;

/************** Declare state function  ****************/
STATE_define(Alarm_Waiting);
STATE_define(Alarm_off);
STATE_define(Alarm_on);

/***************** state pointer to function *********************/
extern void (*Monitor_STATE)();

#endif /* MONITOR_H_ */
