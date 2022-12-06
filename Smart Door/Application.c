/*
 * LCD_Kaypad_drivers.c
 *
 * Created: 13/09/2022 05:24:07 ص
 * Author : Abotaleb
 */

#include <avr/io.h>
#include "LCD_driver/LCD.h"
#include "Kaypad_driver/Kaypad.h"
#define SETBIT(register,bit)     (register |=(1<<bit))
#define CLEARBIT(register,bit)   (register &=~(1<<bit))
#define OPENED     3
#define CLOSED     4
#define Wrong      5
#define THIEF      6
#define TOGGLEBIT(register,bit)  (register ^=(1<<bit))

uint8_t Pcreated_Password[4]={1,2,3,4};
uint8_t flag=0;
int main(void)
{
	SETBIT(DDRB,OPENED);
	SETBIT(DDRB,CLOSED);
	SETBIT(DDRB,Wrong);
	SETBIT(DDRB,THIEF);
	LCD_INIT();
	KAYPAD_INIT();
	uint8_t Pressed_Kay;
	uint32_t Writing_password=0;
	uint8_t *PWriting_password = &Writing_password;
	uint32_t counter=0 ;
	static uint32_t flag=0;
	SETBIT(PORTB,CLOSED);
	LCD_WRITE_STRING("Enter the ");
	LCD_GOTO_XY(2,0);
	LCD_WRITE_STRING("password : ");
	while (1)
	{
		Pressed_Kay = GET_CHARACTER();
		if (Pressed_Kay >=0 && Pressed_Kay <=9)
		{
			LCD_WRITE_CHAR('*');
			counter++;
			switch(counter)
			{
			case 1 :
				PWriting_password[0]=Pressed_Kay;
				break;
			case 2:
				PWriting_password[1]=Pressed_Kay;
				break;
			case 3 :
				PWriting_password[2]=Pressed_Kay;
				break;
			case 4 :
				PWriting_password[3]=Pressed_Kay;
				break;
			}
		}
		switch (Pressed_Kay)
		{
			case '=' :
				if (PWriting_password[0]==Pcreated_Password[0] && PWriting_password[1]==Pcreated_Password[1] && PWriting_password[2]==Pcreated_Password[2] && PWriting_password[3]==Pcreated_Password[3])
				{
					LCD_clear_screen();
					SETBIT(PORTB,OPENED);
					CLEARBIT(PORTB,CLOSED);
					LCD_WRITE_STRING("o p e n e d");	
					flag =0;
				}
				else 
				{
					if (flag ==3)
					{
						LCD_clear_screen();
						SETBIT(PORTB,THIEF);
						LCD_GOTO_XY(2,0);
						LCD_WRITE_STRING("????????????");
						_delay_ms(4000);
						CLEARBIT(PORTB,THIEF);
						flag=0;
					}
					else
					{
					LCD_clear_screen();
					SETBIT(PORTB,Wrong);
					flag++;
					LCD_WRITE_STRING("wrong password");
					}
					
				}
				break;	
			case 'C' : 		
				counter = 0;
				LCD_clear_screen();
				CLEARBIT(PORTB,OPENED);
				CLEARBIT(PORTB,Wrong);
				SETBIT(PORTB,CLOSED);
				LCD_WRITE_STRING("c l o s e d ");
				break;	
			case '+' :
				CLEARBIT(PORTB,Wrong);
				CLEARBIT(PORTB,OPENED);
				CLEARBIT(PORTB,THIEF);
				SETBIT(PORTB,CLOSED);
				counter = 0;
				LCD_clear_screen();	
				LCD_WRITE_STRING("Enter the ");
				LCD_GOTO_XY(2,0);
				LCD_WRITE_STRING("password : ");
		}
	}
	
}

