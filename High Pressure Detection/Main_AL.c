/*
 * Main_AL.c
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#include "Main_AL.h"

/***************** variables *********************/
uint32_t MAL_Pressure_thresold=20;
uint32_t MAL_Pressure;
uint32_t MAL_clock;


/***************** state pointer to function *********************/
void (*MAL_STATE)();

/***************** Connection *********************/
void Set_Sensor_pressure(uint32_t Pressure)
{
	MAL_Pressure=Pressure;
	MAL_STATE=STATE_(M_Checking);
}
STATE_define(M_Checking)
{
	/***************** Event check *********************/
	if (MAL_Pressure<=MAL_Pressure_thresold)
	{
		MAL_STATE=STATE_(M_Waiting);

	}
	else if(MAL_Pressure>MAL_Pressure_thresold)
	{
		MAL_STATE=STATE_(M_Sending);
	}
}
STATE_define(M_Sending)
{
	/***************** State name *********************/
	Main_AL_state_id=M_Sending;

	/***************** State action *********************/
	Set_monitor_High_Pressure_Detection();
	MAL_STATE=STATE_(M_Waiting);

}

STATE_define(M_Waiting)
{
	/***************** State name *********************/
	Main_AL_state_id=M_Waiting;

	/***************** State action *********************/
	MAL_STATE=STATE_(M_Checking);
}

