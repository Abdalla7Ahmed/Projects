/*
 * Sensor_pressure.h
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#ifndef SENSOR_PRESSURE_H_
#define SENSOR_PRESSURE_H_
#include "State.h"
enum
{
	PS_Waiting,
	PS_Reading
}PS_stete_id;
/************** Declare state function ****************/
STATE_define(PS_Waiting);
STATE_define(PS_Reading);
STATE_define(Pressure_Sensor_Init);

/***************** state pointer to function *********************/
extern void (*PSensor_STATE)();


#endif /* SENSOR_PRESSURE_H_ */
