/*
 * LCD.c
 *
 * Created: 14/09/2022 01:27:34 AM
 *  Author: Abotaleb
 */ 

#include "lcd.h"


// =========================== initialization of LCD ===========================
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

// =========================== Lcd write command  ===========================
void LCD_WRITE_COMMAND(unsigned char command)
{
	
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_PORT = command;
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		LCD_lcd_kick();	
    #endif	
    #ifdef FOUR_BIT_MODE
		LCD_check_lcd_isbusy();
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		LCD_lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		CLEARBIT(LCD_CTRL,RS_SWITCH);
		LCD_lcd_kick();	
	 #endif

}
void LCD_Send_A_Character(unsigned char character)
{
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		SETBIT(LCD_CTRL,RS_SWITCH);
		LCD_PORT = ( ( (character  ) << DATA_shift)   )  ;
		SETBIT(LCD_CTRL,RS_SWITCH);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		LCD_lcd_kick();
    #endif
    #ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		SETBIT(LCD_CTRL,RS_SWITCH);
		CLEARBIT(LCD_CTRL,RW_SWITCH);
		LCD_lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (character <<4);
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
		counter++;
		LCD_Send_A_Character(*string++);
		if (counter==16)
		{
			LCD_GOTO_XY(1,0);
		}
		else if (counter==32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(0,0);
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
	asm volatile ("nop");
	asm volatile ("nop");
	_delay_ms(50);
	SETBIT(LCD_CTRL,EN_SWITCH);
}

// clear the screen 
void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN); 
}
void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 0)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}
void LCD_display_number (int Number )
{

	char  str[7];

	sprintf(str,"%d",Number);	// Adjust the formatting to your liking.

	LCD_WRITE_STRING (str) ;

}

void LCD_display_real_number (double  Number )
{

	char  str[16];


	char *tmpSign = (Number < 0) ? "-" : "";
	float tmpVal = (Number < 0) ? -Number : Number;

	int tmpInt1 = tmpVal;                 // Get the integer (678).
	float tmpFrac = tmpVal - tmpInt1;     // Get fraction (0.0123).
	int tmpInt2 = tmpFrac * 10000;        // Turn into integer (123).

	// Print as parts, note that you need 0-padding for fractional bit.

	sprintf (str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);



	LCD_WRITE_STRING (str) ;

}


// write in arabic

static uint32_t counter_arabic=15;
static address_begin=64;
static Char_number=0;

void LCD_Arabic_Char(uint8_t Character)
{
	
	LCD_WRITE_COMMAND(address_begin);
	switch(Character)
	{
		case 'H':   //ا
		case 'h':
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'F':  //ب
		case 'f':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x00);
			break;
		case 'J':  //ت
		case 'j':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x0D);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'E':  //ث
		case 'e':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x08);
			LCD_Send_A_Character(0x15);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '{':  //ج
		case '[':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x0E);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x00);
			break;
		case 'P':  //ح
		case 'p':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x0E);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'O':  //خ
		case 'o':
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x0E);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '}':  //د
		case ']':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '~':  //ذ
		case '`':
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'v':  //ر
		case 'V':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x18);
			LCD_Send_A_Character(0x00);
			break;
		case '>':  //ز
		case '.':
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x18);
			LCD_Send_A_Character(0x00);
			break;
		case 'S':  //س
		case 's':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x15);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'A':  //ش
		case 'a':
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x0A);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x15);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'W':  //ص
		case 'w':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x09);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'Q':  //ض
		case 'q':
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x09);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '"':  //ط
		case '\'':
			LCD_Send_A_Character(0x08);
			LCD_Send_A_Character(0x08);
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x09);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '?':  //ظ
		case '/':
			LCD_Send_A_Character(0x0A);
			LCD_Send_A_Character(0x08);
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x09);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'U':  //ع
		case 'u':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'Y':  //غ
		case 'y':
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'T':  //ف
		case 't':
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'R':  //ق
		case 'r':
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case ':':  //ك
		case ';':
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'G':  //ل
		case 'g':
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case 'L':  //م
		case 'l':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x00);
			break;
		case 'K':  //ن
		case 'k':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;	
		case 'I':  //ه
		case 'i':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x0F);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;
		case '<':  //و
		case ',':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x03);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x05);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x02);
			LCD_Send_A_Character(0x1C);
			break;
		case 'N':  //ى
		case 'n':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x04);
			LCD_Send_A_Character(0x07);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			break;
		case 'D':  //ي
		case 'd':
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x01);
			LCD_Send_A_Character(0x1F);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x06);
			LCD_Send_A_Character(0x00);
			break;
		case 32:  //space
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			LCD_Send_A_Character(0x00);
			break;	
	}
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+counter_arabic);
	LCD_Send_A_Character(Char_number);
	address_begin +=8;
	Char_number ++;
}

void LCD_WRITE_STRING_Arabic(char* string)
{
	
	while (*string >0)
	{
		counter_arabic--;
		LCD_Arabic_Char(*string++);
		if (counter_arabic==0)
		{
			LCD_GOTO_XY(1,15);
		}
		else if (counter_arabic==15)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(0,15);
			counter_arabic=0;
		}
	}
	counter_arabic =15;
	Char_number =0;
	address_begin =64;
	LCD_GOTO_XY(1,0);

}