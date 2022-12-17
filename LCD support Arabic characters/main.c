/*
 * ATMEG32_Drivers.c
 *
 * Created: 24/09/2022 11:06:07 AM
 * Author : Abdallah Ahmed Mohammed
 */ 
#include "SERVICES/Including_Services.h"
#include "MCAL/Including_MCAL_files.h"
#include "HAL/Including_HAL_files.h"

int main(void)
{
	LCD_INIT();
	
	while (1)
	{
		LCD_WRITE_STRING_Arabic("uf]hggi");
		_delay_ms(1000);
		LCD_GOTO_XY(1,0);
		LCD_WRITE_STRING("Abdallah");
		_delay_ms(1000);
		LCD_clear_screen();
		
	}

}


