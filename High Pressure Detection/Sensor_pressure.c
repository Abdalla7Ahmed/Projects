/*
 * Sensor_pressure.c
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */
#include "Sensor_pressure.h"



/***************** variables *********************/
uint32_t PS_Pressure=0;
uint32_t counter_delay;

/***************** Get number by User *********************/
int getPressureVal();

/***************** state pointer to function *********************/
void (*PSensor_STATE)();

/***************** initialization of Pressure Sensor *********************/
STATE_define(Pressure_Sensor_Init)
{
//	printf("================== Pressure_sensor init ==================\n");
	PSensor_STATE=STATE_(PS_Reading);
}

/***************** functions defination*********************/
STATE_define(PS_Reading)
{
	/***************** State name *********************/
	PS_stete_id=PS_Reading;

	/***************** State action *********************/
	PS_Pressure=getPressureVal();
	Set_Sensor_pressure(PS_Pressure);

	PSensor_STATE=STATE_(PS_Waiting) ;
}
STATE_define(PS_Waiting)
{
	/***************** State name *********************/
	PS_stete_id=PS_Reading;

	/***************** State action *********************/
	Delay(2000);
	PSensor_STATE=STATE_(PS_Reading) ;
}







