/* main.c
*
*  Created on: 22/8/2022
*      Author:Abdallah Ahmed
*/
#include "driver.h"
#include "Sensor_pressure.h"
#include "Main_AL.h"
#include "Monitor.h"
#include "Alarm.h"

void setup()
{
	/********** init all driveres **********/

	/********** init IRQ ...... **********/

	/********** init HAL (US_driver - DC_motor driver) **********/

	/********** init Block **********/
//	STATE_(Pressure_Sensor_Init);
//	STATE_define(Alarm_Init);
	/********** Set states pointers for each block **********/
	PSensor_STATE=STATE_(Pressure_Sensor_Init);
	MAL_STATE=STATE_(M_Waiting);
	Monitor_STATE=STATE_(Alarm_off);
	Alarm_STATE=STATE_(LED_off);
}

int main()
{
	GPIO_INITIALIZATION();
	setup();
	while(1)
	{
		/********** call state for each block**********/
		PSensor_STATE();
		MAL_STATE();
		Monitor_STATE();
		Alarm_STATE();
	}
	return 0;
}
