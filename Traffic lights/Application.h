/*
 * Application.h
 *
 * Created: 17/10/2022 09:08:03 م
 *  Author: Abotaleb
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_
#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "../bit_configuration.h"

#define _TOP_ROAD_Control					DDRC
#define _LEFT_ROAD_Control					DDRC
#define _BOTTOM_ROAD_Control				DDRD
#define _RIGHT_ROAD_Control 				DDRD

#define _TOP_ROAD_PORT						PORTC
#define _LEFT_ROAD_PORT						PORTC
#define _BOTTOM_ROAD_PORT					PORTD
#define _RIGHT_ROAD_PORT					PORTD


#define _TOP_RED							2 
#define _TOP_YELLOW							1
#define _TOP_GREEN							0

#define _LEFT_RED							5
#define _LEFT_YELLOW						6
#define _LEFT_GREEN							7



#define _BOTTOM_RED							2
#define _BOTTOM_YELLOW						1
#define _BOTTOM_GREEN						0

#define _RIGHT_RED							7
#define _RIGHT_YELLOW						6
#define _RIGHT_GREEN						5


#define _Buzzer_Control						DDRB
#define _Buzzer_PORT						PORTB
#define _Buzzer_Pin							3



void Traffic_lights_init(void);





#endif /* APPLICATION_H_ */