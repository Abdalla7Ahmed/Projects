/*
 * SIMS.h
 *
 *  Created on: 30/8/2022
 *      Author: Abdallah Ahmed Mohammed
 */

#ifndef SIMS_H_
#define SIMS_H_
#include <stdio.h>
#include "stdint.h"
#include "string.h"
#include "stdlib.h"


/**************************************************************/
#define DPRINTF(...)   {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}
/**************************************************************/
#define Total_number_courses_id 10
#define Curse_number_for_each_student 5
#define Students_number 50

/**************************************************************/
typedef struct
{
	uint8_t FirstName_m[20];
	uint8_t LastName_m[20];
	uint32_t RollNumber_m;
	float  GPA_m;
	uint32_t CID_m[10];
}Student_info_t;
typedef struct
{
	uint32_t            length;
	uint32_t             count;
	Student_info_t      *base;
	Student_info_t      *head;
	Student_info_t      *tail;
}FIFO_BUFF_t;

typedef enum
{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_NULL
}FIFO_STATUS_t;




/**************************************************************/
FIFO_BUFF_t Data_base;
Student_info_t Students[Students_number];

/********************** APIS **********************/
FIFO_STATUS_t fifo_init(FIFO_BUFF_t *fifo_buff ,Student_info_t *Students,uint32_t length);
FIFO_STATUS_t PUSH_item(FIFO_BUFF_t *fifo_buff );
FIFO_STATUS_t POP_item(FIFO_BUFF_t *fifo_buff ,uint32_t *item);
FIFO_STATUS_t fifo_full(FIFO_BUFF_t *fifo_buff );
FIFO_STATUS_t fifo_empty(FIFO_BUFF_t *fifo_buff );
FIFO_STATUS_t fifo_null(FIFO_BUFF_t *fifo_buff );

/**********************  ###################  **********************/
void Add_student_from_file(FIFO_BUFF_t *fifo_buff);
void Add_student_manually(FIFO_BUFF_t *fifo_buff);
void Find_by_roll(FIFO_BUFF_t *fifo_buff);
void Fine_by_FistName(FIFO_BUFF_t *fifo_buff);
void Find_by_cource_ID(FIFO_BUFF_t *fifo_buff);
void Find_total(FIFO_BUFF_t *fifo_buff);
void Delete_by_roll(FIFO_BUFF_t *fifo_buff);
void Update_by_roll(FIFO_BUFF_t *fifo_buff);
void Show_all_information(FIFO_BUFF_t *fifo_buff);
int Find_repeat_roll_number(FIFO_BUFF_t *fifo_buff,uint32_t Roll_number);
int Check_repeat_ID_course(uint32_t ID_recorded,uint32_t ID_check);
int Check_course_id(uint32_t number);


#endif /* SIMS_H_ */
