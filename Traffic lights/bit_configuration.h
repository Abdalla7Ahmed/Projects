/*
 * bit_configuration.h
 *
 * Created: 27/10/2022 12:20:25 م
 *  Author: Abotaleb
 */ 


#ifndef BIT_CONFIGURATION_H_
#define BIT_CONFIGURATION_H_


#define SETB_BIT(register,bit)     (register |=(1<<bit))
#define CLEAR_BIT(register,bit)   (register &=~(1<<bit))

#define TOGGLE_BIT(register,bit)  (register ^=(1<<bit))
#define READ_BIT(register,bit)    ((register>>bit)&1)

#define SET_PORT(register)		  ((register &=0xFF))
#define CLEAR_PORT(register)	  ((register &=0x00))

#endif /* BIT_CONFIGURATION_H_ */