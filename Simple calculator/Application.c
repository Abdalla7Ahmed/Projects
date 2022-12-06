 /*
  ==========================================================================
 *============= Created: 13/09/2022 05:24:07 am
 *============= Author : Abdallah Ahmed Mohammed
 *============= ======= Simple calculator ==================================
 */

#include <avr/io.h>
#include "LCD_driver/LCD.h"
#include "Kaypad_driver/Kaypad.h"

uint8_t K1=1;
uint8_t K2=1;
uint8_t number_of_digits1=0;
uint8_t number_of_digits2=0;
int8_t number_of_digits_sum=0;
uint8_t counter=0;
uint8_t Pressed_Kay;
uint8_t flag=0;
uint32_t temp1=0,temp2=0;
uint8_t Operation;
uint8_t complete_operation=0;
uint32_t calc;
uint8_t number1[10];
uint8_t number2[10];
uint8_t sum[20];
uint32_t return_n_of_digits(uint8_t Rnumber)
{
	int i,mul=1;
	for (i=1;i<Rnumber;i++)
	{
		mul *=10;
	}
	return mul;
}
void return_initial()
{
	counter = 0;
	flag =0;
	K1=1;
	K2=1;
	temp1=0;
	temp2=0;
	number_of_digits1 =0;
	number_of_digits2 =0;
	number_of_digits_sum=0;
	complete_operation =0;
	for (int i=0;i<10;i++)
	{
		number1[i]=0;
		number2[i]=0;

	}
	for (int i=0;i<20;i++)
	{
		sum[i]=0;
	}		
}

int main(void)
{
	
	LCD_INIT();
	KAYPAD_INIT();
	LCD_WRITE_STRING("Calculator is ");
	LCD_GOTO_XY(2,0);
	LCD_WRITE_STRING("ready");
	_delay_ms(100);
	LCD_clear_screen();
	

	while (1)
	{
		Pressed_Kay=GET_CHARACTER();
		if (Pressed_Kay >= 0 && Pressed_Kay <= 9)
		{
			LCD_DISPLAY_NUMBER(Pressed_Kay);
			if (flag ==0)
			{
				number1[counter]=Pressed_Kay;
				counter++;
				number_of_digits1++;
			}
			else if(flag == 1)
			{
				number2[counter]=Pressed_Kay;
				complete_operation=1;
				counter++;
				number_of_digits2++;
			}
		}
		switch(Pressed_Kay)
		{
		case '*':
			LCD_WRITE_CHAR(Pressed_Kay);
			Operation = Pressed_Kay;
			flag =1;
			counter=0;
			break;
		case '+':
			LCD_WRITE_CHAR(Pressed_Kay);
			Operation = Pressed_Kay;
			flag =1;
			counter=0;
			break;
		case '-':
			LCD_WRITE_CHAR(Pressed_Kay);
			Operation = Pressed_Kay;
			flag =1;
			counter=0;
			break;
		case '/':
			LCD_WRITE_CHAR(Pressed_Kay);
			Operation = Pressed_Kay;
			flag =1;
			counter=0;
			break;
		case '=':
			counter =0;
			flag=0;
			
			for (int j=0;j<10;j++)
			{
				temp1 +=number1[j]*return_n_of_digits(number_of_digits1); 
				number_of_digits1--;
				
			}
			for (int j=0;j<10;j++)
			{
				temp2 +=number2[j]*return_n_of_digits(number_of_digits2);
				number_of_digits2--;
			}
			if (Operation=='*') calc =temp1 * temp2;	
			else if (Operation == '+') calc=temp1+temp2;
			else if (Operation == '-') calc = temp1-temp2;
			else if (Operation == '/') calc = temp1 / temp2;
			if (complete_operation ==0)
			{
				LCD_clear_screen();
				LCD_WRITE_STRING("Syntax ERROR");
				LCD_GOTO_XY(2,1);
				LCD_WRITE_STRING("[C]  : Cancel");
			}
			else if (Operation == '/' && temp2 ==0 && complete_operation ==1)
			{
				LCD_clear_screen();
				LCD_WRITE_STRING("Math ERROR");
				LCD_GOTO_XY(2,1);
				LCD_WRITE_STRING("[C]  : Cancel");
			}
			else if(complete_operation ==1)
			{
				LCD_WRITE_CHAR(Pressed_Kay);
				uint8_t i=0;
				LCD_GOTO_XY(2,1);
 				while(calc !=0)
 				{
 					sum[i]=(calc %10);
 					calc /=10;
 					number_of_digits_sum ++;
 					i++;
 				}
				number_of_digits_sum--;

 				while(number_of_digits_sum >=0)
 				{
 					LCD_DISPLAY_NUMBER(sum[number_of_digits_sum]);
					 number_of_digits_sum--;
 				}
			}
			break;
		case 'C':
			return_initial();
			LCD_clear_screen();
			break;
		}
	}

}

