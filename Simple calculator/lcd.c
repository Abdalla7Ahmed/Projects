/*
 * LCD.c
 *
 * Created: 14/09/2022 01:27:34 AM
 *  Author: Abotaleb
 */ 

#include "lcd.h"

void LCD_INIT()
{
	_delay_ms(20);
	LCD_check_lcd_isbusy();
	SETBIT(DataDir_LCD_CTRL,EN_SWITCH);
	SETBIT(DataDir_LCD_CTRL,RW_SWITCH);
	SETBIT(DataDir_LCD_CTRL,RS_SWITCH);
		
	CLEARBIT(LCD_CTRL,EN_SWITCH);
	CLEARBIT(LCD_CTRL,RS_SWITCH);
	CLEARBIT(LCD_CTRL,RW_SWITCH);
		
	DataDir_LCD_PORT=0xFF;
	_delay_ms(15);
	LCD_clear_screen();	
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
   #endif
   #ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
   #endif
    	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
    	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
    	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

}
void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_check_lcd_isbusy();
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command;
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		_delay_ms(1);
		LCD_lcd_kick();	
    #endif	
    #ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		LCD_lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << DATA_shift);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		LCD_lcd_kick();	
	 #endif

}
void LCD_WRITE_CHAR(unsigned char character)
{
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_PORT = character;
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		SETBIT(LCD_CTRL,RS_SWITCH);
		_delay_ms(1);
		LCD_lcd_kick();
    #endif
    #ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		SETBIT(LCD_CTRL,RS_SWITCH);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		LCD_lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (character <<DATA_shift);
		SETBIT(LCD_CTRL,RS_SWITCH);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		LCD_lcd_kick();
    #endif

}

void LCD_WRITE_STRING(char* string)
{
	uint32_t counter=0;
	while (*string >0)
	{
		LCD_WRITE_CHAR(*string++);
		counter++;
		if (counter==16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (counter==32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			counter=0;
		}
	}

}

void LCD_check_lcd_isbusy(void)
{
	DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	SETBIT(LCD_CTRL,RW_SWITCH); // read mood
	CLEARBIT(LCD_CTRL,RS_SWITCH);
    LCD_lcd_kick();
    DataDir_LCD_PORT =0xFF;
	CLEARBIT(LCD_CTRL,RW_SWITCH); // Write mood
}
void LCD_lcd_kick(void)
{
	CLEARBIT(LCD_CTRL,EN_SWITCH);
	_delay_ms(50);
	SETBIT(LCD_CTRL,EN_SWITCH);
}
void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}
void LCD_DISPLAY_NUMBER(uint32_t number)
{
	char str[7];
	sprintf(str,"%d",number);
	LCD_WRITE_STRING(str);
	
}
void LCD_DISPLAY_REAL_NUMBER(double number)
{
	char str[16];
	char *tmpsign=(number<0)? "-" : "";
	float tmpval=(number<0) ? -number : number;
	uint32_t tmpint1=tmpval;
	float tmpfrac=tmpval-tmpint1;
	uint32_t tmpint2=tmpfrac*10000;
	sprintf(str,"%s%d.%02d",tmpsign,tmpint1,tmpint2);
	LCD_WRITE_STRING(str);
}