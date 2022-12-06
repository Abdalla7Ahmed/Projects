/*
 * Monitor.c
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#include "Monitor.h"


/***************** variables *********************/
uint32_t M_Alarm_Value;


/***************** state pointer to function *********************/
void (*Monitor_STATE)();

/***************** Connection *********************/
void Set_monitor_High_Pressure_Detection()
{
	Monitor_STATE=STATE_(Alarm_on);
}

/***************** functions defination*********************/
STATE_define(Alarm_on)
{
	/***************** State name *********************/
	M_state_id=Alarm_on;

	/***************** State action *********************/
	Start_Alarm();
	Monitor_STATE=STATE_(Alarm_Waiting);
}
STATE_define(Alarm_off)
{
	/***************** State name *********************/
	M_state_id=Alarm_off;

	/***************** State action *********************/
	Stop_Alarm();
}

STATE_define(Alarm_Waiting)
{
	/***************** State name *********************/
	M_state_id=Alarm_Waiting;


	/***************** State action *********************/
	Delay(2000);
	Monitor_STATE=STATE_(Alarm_off);



}



