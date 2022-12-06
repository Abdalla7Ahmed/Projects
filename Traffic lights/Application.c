/*
 * Application.c

 */ 
#include "Application.h"

void Traffic_lights_init(void)
{
	// Set pins 0 1 2 in PORTC as an output
	SETB_BIT(_TOP_ROAD_Control,_TOP_RED);
	SETB_BIT(_TOP_ROAD_Control,_TOP_YELLOW);
	SETB_BIT(_TOP_ROAD_Control,_TOP_GREEN);
	
	// Set pins 5 6 7 in PORTC as an output
	SETB_BIT(_LEFT_ROAD_Control,_LEFT_RED);
	SETB_BIT(_LEFT_ROAD_Control,_LEFT_YELLOW);
	SETB_BIT(_LEFT_ROAD_Control,_LEFT_GREEN);
	
	// Set pins 0 1 2 in PORTD as an output
	SETB_BIT(_BOTTOM_ROAD_Control,_BOTTOM_RED);
	SETB_BIT(_BOTTOM_ROAD_Control,_BOTTOM_YELLOW);
	SETB_BIT(_BOTTOM_ROAD_Control,_BOTTOM_GREEN);
	
	// Set pins 5 6 7 in PORTD as an output
	SETB_BIT(_RIGHT_ROAD_Control,_RIGHT_RED);
	SETB_BIT(_RIGHT_ROAD_Control,_RIGHT_YELLOW);
	SETB_BIT(_RIGHT_ROAD_Control,_RIGHT_GREEN);
	
	SETB_BIT(_Buzzer_Control,_Buzzer_Pin);
	
	SETB_BIT(_LEFT_ROAD_PORT,_LEFT_RED);
	SETB_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_RED);
	SETB_BIT(_RIGHT_ROAD_PORT,_RIGHT_RED);
	
	

}

