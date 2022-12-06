/*
 * Kaypad.h
 *
 * Created: 14/09/2022 07:35:53 ص
 *  Author: Abotaleb
 */ 


#ifndef KAYPAD_H_
#define KAYPAD_H_

#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>

/*=========================== User Layer ===================================*/
#define KAYPAD_PORT          PORTD
#define Data_Dir_KAYPAD_PORT DDRD
#define KAYPAD_PIN           PIND
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7	
/*=================================================================*/


/*===================Functions declaration======================*/
void KAYPAD_INIT();
char GET_CHARACTER();
/*=================================================================*/
 

/*======================= Bit Configration ======================*/
#define SETBIT(register,bit)     (register |=(1<<bit))

#define CLEARBIT(register,bit)   (register &=~(1<<bit))

#define TOGGLEBIT(register,bit)  (register ^=(1<<bit))

#define READBIT(register,bit)    ((register>>bit)&1)
/*=================================================================*/


#endif /* KAYPAD_H_ */