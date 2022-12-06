/*
 * LCD_Kaypad_drivers.c
 *
 * Created: 13/09/2022 05:24:07 ص
 * Author : Abotaleb
 */

#include <avr/io.h>
#include "Application/Application.h"
#include "LCD_driver/lcd.h"
int main(void)
{
	LCD_INIT();
	Traffic_lights_init();
	LCD_GOTO_XY(1,3);
	LCD_WRITE_STRING("Count down");
	LCD_GOTO_XY(2,7);
	int i;
	while(1)
	{
		
		CLEAR_BIT(_TOP_ROAD_PORT,_TOP_YELLOW);
		CLEAR_BIT(_RIGHT_ROAD_PORT,_RIGHT_YELLOW);
		SETB_BIT(_RIGHT_ROAD_PORT,_RIGHT_RED);
		SETB_BIT(_TOP_ROAD_PORT,_TOP_GREEN);
		for (i=7;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		SETB_BIT(_Buzzer_PORT,_Buzzer_Pin);
		_delay_ms(1000);
		CLEAR_BIT(_Buzzer_PORT,_Buzzer_Pin);
		
		
		
		CLEAR_BIT(_TOP_ROAD_PORT,_TOP_GREEN);
		CLEAR_BIT(_LEFT_ROAD_PORT,_LEFT_RED);
		SETB_BIT(_TOP_ROAD_PORT,_TOP_YELLOW);
		SETB_BIT(_LEFT_ROAD_PORT,_LEFT_YELLOW);
		for (i=1;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		
		CLEAR_BIT(_TOP_ROAD_PORT,_TOP_YELLOW);
		CLEAR_BIT(_LEFT_ROAD_PORT,_LEFT_YELLOW);
		SETB_BIT(_TOP_ROAD_PORT,_TOP_RED);
		SETB_BIT(_LEFT_ROAD_PORT,_LEFT_GREEN);
		for (i=7;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		SETB_BIT(_Buzzer_PORT,_Buzzer_Pin);
		_delay_ms(1000);
		CLEAR_BIT(_Buzzer_PORT,_Buzzer_Pin);
		
		
		
		CLEAR_BIT(_LEFT_ROAD_PORT,_LEFT_GREEN);
		CLEAR_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_RED);
		SETB_BIT(_LEFT_ROAD_PORT,_LEFT_YELLOW);
		SETB_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_YELLOW);
		for (i=1;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
	
		
		CLEAR_BIT(_LEFT_ROAD_PORT,_LEFT_YELLOW);
		CLEAR_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_YELLOW);
		SETB_BIT(_LEFT_ROAD_PORT,_LEFT_RED);
		SETB_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_GREEN);
		for (i=7;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		SETB_BIT(_Buzzer_PORT,_Buzzer_Pin);
		_delay_ms(1000);
		CLEAR_BIT(_Buzzer_PORT,_Buzzer_Pin);
		
		
		CLEAR_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_GREEN);
		CLEAR_BIT(_RIGHT_ROAD_PORT,_RIGHT_RED);
		SETB_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_YELLOW);
		SETB_BIT(_RIGHT_ROAD_PORT,_RIGHT_YELLOW);
		for (i=1;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		
		
		CLEAR_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_YELLOW);
		CLEAR_BIT(_RIGHT_ROAD_PORT,_RIGHT_YELLOW);
		SETB_BIT(_RIGHT_ROAD_PORT,_RIGHT_GREEN);
		SETB_BIT(_BOTTOM_ROAD_PORT,_BOTTOM_RED);
		for (i=7;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}
		SETB_BIT(_Buzzer_PORT,_Buzzer_Pin);
		_delay_ms(1000);
		CLEAR_BIT(_Buzzer_PORT,_Buzzer_Pin);
		
		
		SETB_BIT(_TOP_ROAD_PORT,_TOP_YELLOW);
		SETB_BIT(_RIGHT_ROAD_PORT,_RIGHT_YELLOW);
		CLEAR_BIT(_RIGHT_ROAD_PORT,_RIGHT_GREEN);
		CLEAR_BIT(_TOP_ROAD_PORT,_TOP_RED);
		for (i=1;i>=0;i-- )
		{
			LCD_DISPLAY_NUMBER(i);
			_delay_ms(1000);
			LCD_GOTO_XY(2,7);
		}	
	}
}

