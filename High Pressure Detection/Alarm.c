/*
 * Alarm.c
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#include "Alarm.h"

/***************** variables *********************/
uint32_t LED_Check;

/***************** state pointer to function *********************/
void (*Alarm_STATE)();

/***************** initialization of Alarm_LED *********************/
STATE_define(LED_Init)
{
//	printf("================== Alarm_LED init ==================\n");
}
/***************** Connection *********************/

void Start_Alarm()
{
	LED_Check=0;
	Alarm_STATE=STATE_(LED_on);
}
void Stop_Alarm()
{
	LED_Check=1;
	Alarm_STATE=STATE_(LED_off);
}

/***************** functions defination*********************/
STATE_define(LED_on)
{
	/***************** State name *********************/
	Alarm_state_id=LED_on;

	/***************** State action *********************/
	Set_Alarm_actuator(LED_Check);
	Alarm_STATE=STATE_(LED_Waiting);


}
STATE_define(LED_off)
{
	/***************** State name *********************/
	Alarm_state_id=LED_off;

	/***************** State action *********************/
	Set_Alarm_actuator(LED_Check);
	Alarm_STATE=STATE_(LED_Waiting);
}

STATE_define(LED_Waiting)
{
	Delay(2000);
	Alarm_STATE=STATE_(LED_off);

}
