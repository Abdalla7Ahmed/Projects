/*
 * Sensor_pressure.h
 *
 *  Created on: 22/8/2022
 *      Author:Abdallah Ahmed
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
#include "driver.h"

/************** Automatic state function generated  ****************/
#define STATE_define(_statefunc_) void ST_##_statefunc_()
#define STATE_(_statefunc_) ST_##_statefunc_

/************** states connections ****************/
void Set_Sensor_pressure(uint32_t Pressure);
void Set_monitor_High_Pressure_Detection();
void Set_Alarm_Monitor(uint32_t Alarm);
void Start_Alarm();
void Stop_Alarm();


#endif /* STATE_H_ */
