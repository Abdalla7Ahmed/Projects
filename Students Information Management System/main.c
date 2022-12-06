/*
 * main.c
 *
 *  Created on: 30/8/2022
 *      Author: Abdallah Ahmed Mohammed
 */


#include "SIMS.h"


int main ()
{
	fifo_init(&Data_base,Students,Students_number);
	DPRINTF("==============================================================\n");
	DPRINTF("========== Welcome to the student management system ==========\n");
	DPRINTF("==============================================================\n");
	uint32_t temp;
	while(1)
	{

		DPRINTF("\n\t Choose one from the following options ");
		DPRINTF("\n 1: Add the student details from file text ");
		DPRINTF("\n 2: Add the student details manually ");
		DPRINTF("\n 3: Find the student details by roll number ");
		DPRINTF("\n 4: Find the student details by his first name");
		DPRINTF("\n 5: Find the student details by course id");
		DPRINTF("\n 6: Delete the student details by roll number");
		DPRINTF("\n 7: Update the student details by roll number");
		DPRINTF("\n 8: Find the total number of students");
		DPRINTF("\n 9: Show all information of students");
		DPRINTF("\n 10: To exit");
		DPRINTF("\n\t Enter option number\n");
		scanf("%d",&temp);
		DPRINTF("==============================================================\n");
		switch(temp)
		{
		case 1:
			Add_student_from_file(&Data_base);
			break;
		case 2:
			Add_student_manually(&Data_base);
			break;
		case 3:
			Find_by_roll(&Data_base);
			break;
		case 4:
			Fine_by_FistName(&Data_base);
			break;
		case 5:
			Find_by_cource_ID(&Data_base);
			break;
		case 6:
			Delete_by_roll(&Data_base);
			break;
		case 7:
			Update_by_roll(&Data_base);
			break;
		case 8:
			Find_total(&Data_base);
			break;
		case 9:
			Show_all_information(&Data_base);
			break;
		case 10:
			exit(1);
		default :
			DPRINTF("Wrong option");
			break;
		}
	}
	return 0;
}




