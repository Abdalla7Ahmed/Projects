/*
 * SIMS.c
 *
 *  Created on: 30/8/2022
 *      Author: Abdallah Ahmed Mohammed
 */
#include "SIMS.h"

/********************** global Variables **********************/
uint32_t Selected_roll_number;
uint32_t temp;

/********************** Variables information of students **********************/

/*********************************** FIFO init***********************************/

FIFO_STATUS_t fifo_init(FIFO_BUFF_t *fifo_buff ,Student_info_t *Students,uint32_t length)
{
	if (!Students)
	{
		return FIFO_NULL;
	}
	fifo_buff->base   = Students;
	fifo_buff->head   = Students;
	fifo_buff->tail   = Students;
	fifo_buff->length = length;
	fifo_buff->count  = 0;
	return FIFO_no_error;
}

/*********************************** PUSH ***********************************/

FIFO_STATUS_t PUSH_item(FIFO_BUFF_t *fifo_buff )
{
	if (fifo_null(fifo_buff)==FIFO_NULL)
	{
		return FIFO_NULL;
	}
	else if(fifo_full(fifo_buff)==FIFO_full)
	{
		return FIFO_full;
	}

	fifo_buff->count++;
	if(fifo_buff->head==(fifo_buff->base+(fifo_buff->length*sizeof(Students))))
	{
		fifo_buff->head=fifo_buff->base;
	}
	else
	{
		fifo_buff->head++;
	}
	return FIFO_no_error;
}

/*********************************** Check for full  ***********************************/

FIFO_STATUS_t fifo_full(FIFO_BUFF_t *fifo_buff )
{
	if (!fifo_buff->base||!fifo_buff->head||!fifo_buff->tail)
	{
		return FIFO_NULL;
	}
	else if (fifo_buff->count==fifo_buff->length)
	{
		return FIFO_full;
	}
	else
	{
		return FIFO_no_error;
	}
}

/*********************************** Check for empty  ***********************************/

FIFO_STATUS_t fifo_empty(FIFO_BUFF_t *fifo_buff)
{
	if (fifo_buff->count==0)
	{
		return FIFO_empty;
	}
	else
	{
		return FIFO_no_error;
	}

}

/*********************************** Check for Null  ***********************************/

FIFO_STATUS_t fifo_null(FIFO_BUFF_t *fifo_buff )
{
	if (!fifo_buff->base||!fifo_buff->head||!fifo_buff->tail)
	{
		return FIFO_NULL;
	}
	else
	{
		return FIFO_no_error;
	}
}


/********************** Functions of students **********************/

void Add_student_from_file(FIFO_BUFF_t *fifo_buff)
{
	uint8_t Lines[50];
	uint32_t N_Lines=0,NParts=0;
	uint32_t Error_Count=0;
	uint32_t Roll_error=0;
	FILE *PtrFile;
	const char* GETDATA;
	PtrFile = fopen("Add_data_file.txt", "r");

	if (PtrFile == NULL) {
		DPRINTF("[ERROR]--> file can't be opened \n");
	}
	while(fgets(Lines ,sizeof(Lines),PtrFile ))
	{
		N_Lines++;Roll_error=0;NParts=0;
		GETDATA=strtok(Lines," ");
		while (GETDATA!=NULL)
		{
			++NParts;
			switch (NParts)
			{
			case 1:
				if (Find_repeat_roll_number(&Data_base,atoi(GETDATA))==1)
				{
					fifo_buff->head->RollNumber_m=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t[ERORR] --> Roll Number %d is already taken \n",atoi(GETDATA));
					DPRINTF("\t[INFO]  --> Student record failed \n");
					++Roll_error;
					++Error_Count;
				}
				break;
			case 2:
				strcpy(fifo_buff->head->FirstName_m,GETDATA);
				break;
			case 3:
				strcpy(fifo_buff->head->LastName_m,GETDATA);
				break;
			case 4:
				fifo_buff->head->GPA_m=atof(GETDATA);
				break;
			case 5:
				if (Check_course_id(atoi(GETDATA))==1)
				{
					fifo_buff->head->CID_m[0]=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t [Warning] --> There is no course with id %d \n",atoi(GETDATA));
					DPRINTF("\t [INFO]   ---> The ID course recorded as %d press 7 to update this\n",404);
					fifo_buff->head->CID_m[0]=404;
					Error_Count++;
				}
				break;
			case 6:
				if (Check_course_id(atoi(GETDATA))==1)
				{
					fifo_buff->head->CID_m[1]=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t [Warning] --> There is no course with id %d \n",atoi(GETDATA));
					DPRINTF("\t [INFO]   ---> The ID course recorded as %d press 7 to update this\n",404);
					fifo_buff->head->CID_m[1]=404;
					Error_Count++;
				}
				break;
			case 7:
				if (Check_course_id(atoi(GETDATA))==1)
				{
					fifo_buff->head->CID_m[2]=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t [Warning] --> There is no course with id %d \n",atoi(GETDATA));
					DPRINTF("\t [INFO]   ---> The ID course recorded as %d press 7 to update this\n",404);
					fifo_buff->head->CID_m[2]=404;
					Error_Count++;
				}
				break;
			case 8:
				if (Check_course_id(atoi(GETDATA))==1)
				{
					fifo_buff->head->CID_m[3]=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t [Warning] --> There is no course with id %d \n",atoi(GETDATA));
					DPRINTF("\t [INFO]   ---> The ID course recorded as %d press 7 to update this\n",404);
					fifo_buff->head->CID_m[3]=404;
					Error_Count++;
				}
				break;
			case 9:
				if (Check_course_id(atoi(GETDATA))==1)
				{
					fifo_buff->head->CID_m[4]=atoi(GETDATA);
				}
				else
				{
					DPRINTF("\t [Warning] --> There is no course with id %d \n",atoi(GETDATA));
					DPRINTF("\t [INFO]   ---> The ID course recorded as %d press 7 to update this\n",404);
					fifo_buff->head->CID_m[4]=404;
					Error_Count++;
				}
				break;
			}
			GETDATA = strtok(NULL ," \n");
		}
		if (Roll_error==1)
		{
			continue;
		}
		if (PUSH_item(&Data_base)==FIFO_no_error)
		{
			fifo_buff->head--;
			DPRINTF("[INFO]---> The details of %s %s added successfully \n",
					fifo_buff->head->FirstName_m,fifo_buff->head->LastName_m);
			fifo_buff->head++;
		}
		else if (PUSH_item(&Data_base)==FIFO_full)
		{
			DPRINTF("[ERROR] --> You filled all the free space \n");
		}
		else if (PUSH_item(&Data_base)==FIFO_NULL)
		{
			DPRINTF("[ERROR] --> There is no FIFO initialization \n");
		}

	}
	fclose(PtrFile);
	DPRINTF("=======================================================\n");
	Find_total(&Data_base);
	if (Error_Count==0)
	{
		DPRINTF("==================================================================\n");
		DPRINTF("[INFO] --> The all students recorded successfully without problems \n");
		DPRINTF("==================================================================\n");
	}
	else
	{
		DPRINTF("=========================================================\n");
		DPRINTF("[ATTENTION] --> The number of error is %d \n",Error_Count);
		DPRINTF("=========================================================\n");
	}
}
/*********************************************************************************/

void Add_student_manually(FIFO_BUFF_t *fifo_buff)
{
	uint32_t AMain_count,ATemp_count;
	uint32_t tempROLL;
	DPRINTF("Enter the first name : ");
	gets(fifo_buff->head->FirstName_m);
	DPRINTF("Enter the last name : ");
	gets(fifo_buff->head->LastName_m);
	DPRINTF("Enter the roll number : ");
	scanf("%d",&tempROLL);
	if (Find_repeat_roll_number(&Data_base,tempROLL)==0)
	{
		DPRINTF("==================================================================\n");
		DPRINTF("[ERROR] -> Roll number %d is already taken \n",tempROLL);
		DPRINTF("[INFO]  --> Student record failed \n");
		DPRINTF("==================================================================\n");

	}
	else if(Find_repeat_roll_number(&Data_base,tempROLL)==1)
	{
		fifo_buff->head->RollNumber_m=tempROLL;
		DPRINTF("Enter the GPA : ");
		scanf("%f",&fifo_buff->head->GPA_m);
		DPRINTF("Enter the course ID for each course : \n");
		for (AMain_count=0;AMain_count<Curse_number_for_each_student;AMain_count++)
		{
			DPRINTF("course %d id :",AMain_count+1);
			scanf("%d",&temp);
			if (Check_course_id(temp)==1)
			{
				fifo_buff->head->CID_m[AMain_count]=temp;
			}
			else if (Check_course_id(temp)==0)
			{
				DPRINTF("\t [ERROR] --> There is no course with id %d \n",temp);
				AMain_count--;
			}

		}
		if (PUSH_item(&Data_base)==FIFO_no_error)
		{
			DPRINTF("==================================================================\n");
			DPRINTF("[INFO] --> Add student done successfully\n");
			Find_total(&Data_base);
			DPRINTF("==================================================================\n");

		}
		else if (PUSH_item(&Data_base)==FIFO_full)
		{
			DPRINTF("[ERROR] --> You filled all the free space \n");
		}
		else if (PUSH_item(&Data_base)==FIFO_NULL)
		{
			DPRINTF("[ERROR] --> There is no FIFO initialization \n");
		}
	}
}

/*********************************************************************************/

void Find_by_roll(FIFO_BUFF_t *fifo_buff)
{
	uint32_t RMain_count,RTemp_count;
	Student_info_t *FTemp=fifo_buff->tail;
	DPRINTF("Enter the roll number of student ");
	scanf("%d",&Selected_roll_number);
	for (RMain_count=0;RMain_count<fifo_buff->count;RMain_count++)
	{
		if (Selected_roll_number==FTemp->RollNumber_m)
		{
			DPRINTF("=====================================================\n");
			DPRINTF("Student first name --> %s  \n",FTemp->FirstName_m);
			DPRINTF("Student Last  name --> %s  \n",FTemp->LastName_m);
			DPRINTF("Student Roll number--> %d  \n",FTemp->RollNumber_m);
			DPRINTF("Student GPA        --> %.2f\n",FTemp->GPA_m);
			for(RTemp_count=0;RTemp_count<Curse_number_for_each_student;RTemp_count++)
			{
				DPRINTF("The course ID is   --> %d \n",FTemp->CID_m[RTemp_count]);
			}
			DPRINTF("=====================================================\n");
			break;
		}
		FTemp ++;
	}
	if (RMain_count==fifo_buff->count)
	{
		DPRINTF("[ERROR] --> Roll number %d not found\n",Selected_roll_number);
	}
}

/*********************************************************************************/

void Fine_by_FistName(FIFO_BUFF_t *fifo_buff)
{
	uint32_t NMain_count,NTemp_count;
	Student_info_t *NTemp=fifo_buff->tail;
	uint8_t Selected_first_name[10];
	DPRINTF("Enter the first name of student ");
	scanf("%s",Selected_first_name);

	for (NMain_count=0;NMain_count<fifo_buff->count;NMain_count++)
	{
		if (stricmp(Selected_first_name,NTemp->FirstName_m)==0)
		{
			DPRINTF("=====================================================\n");
			DPRINTF("Student first name --> %s  \n",NTemp->FirstName_m);
			DPRINTF("Student Last  name --> %s  \n",NTemp->LastName_m);
			DPRINTF("Student Roll number--> %d  \n",NTemp->RollNumber_m);
			DPRINTF("Student GPA        --> %.2f\n",NTemp->GPA_m);
			for(NTemp_count=0;NTemp_count<Curse_number_for_each_student;NTemp_count++)
			{
				DPRINTF("The course ID is   --> %d \n",NTemp->CID_m[NTemp_count]);
			}
			DPRINTF("=====================================================\n");
			break;
		}
		NTemp ++;
	}
	if (NMain_count==fifo_buff->count)
	{
		DPRINTF("[ERROR] --> First name %s not found\n",Selected_first_name);
	}

}

/*********************************************************************************/

void Find_by_cource_ID(FIFO_BUFF_t *fifo_buff)
{
	Student_info_t *IDTemp=fifo_buff->tail;
	uint32_t ID_number;
	uint32_t IDMiain_count,IDSec_count,IDTempcount,IDlocal_count=0;

	DPRINTF("Enter the ID course to search ");
	scanf("%d",&ID_number);
	for (IDMiain_count=0;IDMiain_count<fifo_buff->count;IDMiain_count++)
	{
		for(IDSec_count=0;IDSec_count<Curse_number_for_each_student;IDSec_count++)
		{
			if(ID_number==IDTemp->CID_m[IDSec_count])
			{
				DPRINTF("Student first name --> %s  \n",IDTemp->FirstName_m);
				DPRINTF("Student Last  name --> %s  \n",IDTemp->LastName_m);
				DPRINTF("Student Roll number--> %d  \n",IDTemp->RollNumber_m);
				DPRINTF("Student GPA        --> %.2f\n",IDTemp->GPA_m);
				DPRINTF("He records also in courses ID : ");
				for (IDTempcount=0;IDTempcount<Curse_number_for_each_student;IDTempcount++)
				{
					if (IDTemp->CID_m[IDTempcount]==ID_number)
					{
						continue;
					}
					DPRINTF("%d  ",IDTemp->CID_m[IDTempcount]);
				}
				DPRINTF("\n=====================================================\n");
				IDlocal_count++;
			}
		}
		IDTemp++;
	}
	if (IDMiain_count>fifo_buff->count)
	{
		DPRINTF("[ERROR] --> There is no course with ID number %d\n",ID_number);
		DPRINTF("==================================================================\n");
	}
	else
	{
		DPRINTF("[INFO] --> This ID course has %d records",IDlocal_count);
	}
}

/*********************************************************************************/

void Delete_by_roll(FIFO_BUFF_t *fifo_buff)
{
	uint32_t DMain_count,DTemp_count;
	Student_info_t *DTemp=fifo_buff->tail;
	Student_info_t *NextTemp=fifo_buff->tail;
	NextTemp++;

	DPRINTF("Enter the roll number of student to delete ");
	scanf("%d",&Selected_roll_number);
	for (DMain_count=0;DMain_count<fifo_buff->count;DMain_count++)
	{
		if (Selected_roll_number==DTemp->RollNumber_m)
		{
			DPRINTF("Student first name --> %s  \n",DTemp->FirstName_m);
			DPRINTF("Student Last  name --> %s  \n",DTemp->LastName_m);
			DPRINTF("Student Roll number--> %d  \n",DTemp->RollNumber_m);
			DPRINTF("Student GPA        --> %.2f",DTemp->GPA_m);
			DPRINTF("\t -----> Deleted successfully\n");
			DPRINTF("=====================================================\n");
			for (;DMain_count<fifo_buff->count;DMain_count++)
			{
				strcpy(DTemp->FirstName_m,NextTemp->FirstName_m);
				strcpy(DTemp->LastName_m,NextTemp->LastName_m);
				DTemp->RollNumber_m=NextTemp->RollNumber_m;
				DTemp->GPA_m=NextTemp->GPA_m;
				for (DTemp_count=0;DTemp_count<Curse_number_for_each_student;DTemp_count++)
				{
					DTemp->CID_m[DTemp_count]=NextTemp->CID_m[DTemp_count];
				}
				DTemp++;
				NextTemp++;
			}
			fifo_buff->count--;
			fifo_buff->head--;
			break;
		}
		DTemp++;
		NextTemp++;
	}
	if (DMain_count==fifo_buff->count)
	{
		DPRINTF("[ERROR] --> Roll number %d not found \n",Selected_roll_number);
	}

}

/*********************************************************************************/

void Update_by_roll(FIFO_BUFF_t *fifo_buff)
{

	Student_info_t *UTemp=fifo_buff->tail;
	uint32_t update_number;
	uint32_t UMain_count,UTemp_count;

	DPRINTF("Enter the roll number of student to update ");
	scanf("%d",&Selected_roll_number);

	for (UMain_count=0;UMain_count<fifo_buff->count;UMain_count++)
	{
		if (Selected_roll_number==UTemp->RollNumber_m)
		{
			DPRINTF("[1] --> First name :%s\n",UTemp->FirstName_m);
			DPRINTF("[2] --> Last name  :%s\n",UTemp->LastName_m);
			DPRINTF("[3] --> Roll number: %d \n",UTemp->RollNumber_m);
			DPRINTF("[4] --> GPA        : %.2f \n",UTemp->GPA_m);
			DPRINTF("[5] --> Courses ID : ");
			for(UTemp_count=0;UTemp_count<Curse_number_for_each_student;UTemp_count++)
			{
				DPRINTF("%d   ",UTemp->CID_m[UTemp_count]);
			}
			DPRINTF("\n");
			DPRINTF("[6] --> To exit without any update ");
			DPRINTF("\n What is your update  , Choose number : ");
			scanf("%d",&update_number);
			if (update_number==1)
			{
				DPRINTF("Enter the new first name ");
				gets(UTemp->FirstName_m);
				DPRINTF("[INFO] --> The update done successfully \n");
			}
			else if(update_number==2)
			{
				DPRINTF("Enter the new last name ");
				gets(UTemp->LastName_m);
				DPRINTF("[INFO] --> The update done successfully \n");
			}
			else if(update_number==3)
			{
				uint32_t old_roll_number;
				uint32_t new_roll_number;
				old_roll_number=UTemp->RollNumber_m;
				DPRINTF("Enter new the roll number ");
				scanf("%d",&new_roll_number);
				if (Find_repeat_roll_number(&Data_base,new_roll_number)==1)
				{
					UTemp->RollNumber_m=new_roll_number;
					DPRINTF("[INFO] --> The update done successfully \n");
				}
				else if (new_roll_number==old_roll_number)
				{
					DPRINTF("[ATTENTION] --> You entered the same roll number \n");
					DPRINTF("[INFO] --> The update failed \n");

				}
				else if (Find_repeat_roll_number(&Data_base,new_roll_number)==0)
				{
					DPRINTF("[ERROR] -> Roll number %d is already taken \n",new_roll_number);
					DPRINTF("[INFO] --> The update failed \n");
				}

			}
			else if(update_number==4)
			{
				DPRINTF("Enter the new GPA ");
				scanf("%f",&UTemp->GPA_m);
				DPRINTF("[INFO] --> The update done successfully \n");
			}
			else if(update_number==5)
			{
				uint32_t ID_course_number;
				uint32_t old_ID_course;
				uint32_t new_ID_course;
				for(UTemp_count=0;UTemp_count<Curse_number_for_each_student;UTemp_count++)
				{
					DPRINTF("\t [%d] The course ID is : %d \n",UTemp_count+1,UTemp->CID_m[UTemp_count]);
				}
				DPRINTF("Enter the number of course to update : \n");
				scanf("%d",&ID_course_number);
				switch(ID_course_number)
				{
				case 1:
					old_ID_course=UTemp->CID_m[0];
					DPRINTF("\t Enter the new id course : \n");
					scanf("%d",&new_ID_course);
					if(old_ID_course==new_ID_course)
					{
						DPRINTF("[ATTENTION] --> You entered the same ID course \n");
					}
					else if(Check_course_id(new_ID_course)==1)
					{
						UTemp->CID_m[0]=new_ID_course;
						DPRINTF("[INFO] --> The update done successfully \n");
					}
					else if(Check_course_id(new_ID_course)==0)
					{
						DPRINTF("[ERROR] --> There is no course with id %d\n",new_ID_course);
						UTemp->CID_m[0]=old_ID_course;
						DPRINTF("[INFO] --> The update failed \n");
					}
					break;
				case 2:
					old_ID_course=UTemp->CID_m[1];
					DPRINTF("Enter the new id course : \n");
					scanf("%d",&new_ID_course);
					if(old_ID_course==new_ID_course)
					{
						DPRINTF("[ATTENTION] --> You entered the same ID course \n");
					}
					else if(Check_course_id(new_ID_course)==1)
					{
						UTemp->CID_m[1]=new_ID_course;
						DPRINTF("[INFO] --> The update done successfully \n");
					}
					else if(Check_course_id(new_ID_course)==0)
					{
						DPRINTF("[ERROR] --> There is no course with id %d\n",new_ID_course);
						UTemp->CID_m[1]=old_ID_course;
						DPRINTF("[INFO] --> The update failed \n");
					}
					break;
				case 3:
					old_ID_course=UTemp->CID_m[2];
					DPRINTF("Enter the new id course : \n");
					scanf("%d",&new_ID_course);
					if(old_ID_course==new_ID_course)
					{
						DPRINTF("[ATTENTION] --> You entered the same ID course \n");
					}
					else if(Check_course_id(new_ID_course)==1)
					{
						UTemp->CID_m[2]=new_ID_course;
						DPRINTF("[INFO] --> The update done successfully \n");
					}
					else if(Check_course_id(new_ID_course)==0)
					{
						DPRINTF("[ERROR] --> There is no course with id %d\n",new_ID_course);
						UTemp->CID_m[2]=old_ID_course;
						DPRINTF("[INFO] --> The update failed \n");
					}
					break;
				case 4:
					old_ID_course=UTemp->CID_m[3];
					DPRINTF("Enter the new id course : \n");
					scanf("%d",&new_ID_course);
					if(old_ID_course==new_ID_course)
					{
						DPRINTF("[ATTENTION] --> You entered the same ID course \n");
					}
					else if(Check_course_id(new_ID_course)==1)
					{
						UTemp->CID_m[3]=new_ID_course;
						DPRINTF("[INFO] --> The update done successfully \n");
					}
					else if(Check_course_id(new_ID_course)==0)
					{
						DPRINTF("[ERROR] --> There is no course with id %d\n",new_ID_course);
						UTemp->CID_m[3]=old_ID_course;
						DPRINTF("[INFO] --> The update failed \n");
					}
					break;
				case 5:
					old_ID_course=UTemp->CID_m[4];
					DPRINTF("Enter the new id course : \n");
					scanf("%d",&new_ID_course);
					if(old_ID_course==new_ID_course)
					{
						DPRINTF("[ATTENTION] --> You entered the same ID course \n");
					}
					else if(Check_course_id(new_ID_course)==1)
					{
						UTemp->CID_m[4]=new_ID_course;
						DPRINTF("[INFO] --> The update done successfully \n");
					}
					else if(Check_course_id(new_ID_course)==0)
					{
						DPRINTF("[ERROR] --> There is no course with id %d\n",new_ID_course);
						UTemp->CID_m[4]=old_ID_course;
						DPRINTF("[INFO] --> The update failed \n");
					}
					break;
				default:
					DPRINTF("[ERROR] --> Wrong option \n");
					DPRINTF("[INFO] --> The update failed \n");
					break;
				}
			}
			break;
		}
		UTemp++;
	}
	if (UMain_count==fifo_buff->count)
	{
		DPRINTF("[ERROR] --> Roll number %d not found \n",Selected_roll_number);
	}
	else if (update_number==6)
	{
		DPRINTF("[INFO] --> You didin't change any thing \n");
	}

}

/*********************************************************************************/

void Find_total(FIFO_BUFF_t *fifo_buff)
{

	DPRINTF("[INFO]---> The total number of students : %d \n",fifo_buff->count);
	DPRINTF("[INFO]---> You can add up to %d Students \n",fifo_buff->length);
	DPRINTF("[INFO]---> You can add %d more students \n",fifo_buff->length-fifo_buff->count);
	DPRINTF("Press 9 to show the all information \n");
}

/*********************************************************************************/

void Show_all_information(FIFO_BUFF_t *fifo_buff )
{
	uint32_t SMain_count,STemp_count;
	Student_info_t *STemp=fifo_buff->tail;
	uint8_t i;
	if (fifo_buff->count == 0)
	{
		DPRINTF("[ATENTION] --> Your list is empty\n");
	}
	else
	{
		for(SMain_count=0;SMain_count<fifo_buff->count;SMain_count++)
		{
			DPRINTF("Student first name --> %s  \n",STemp->FirstName_m);
			DPRINTF("Student Last  name --> %s  \n",STemp->LastName_m);
			DPRINTF("Student Roll number--> %d  \n",STemp->RollNumber_m);
			DPRINTF("Student GPA        --> %.2f\n",STemp->GPA_m);
			for(STemp_count=0;STemp_count<Curse_number_for_each_student;STemp_count++)
			{
				DPRINTF("The course ID is   --> %d \n",STemp->CID_m[STemp_count]);
			}
			DPRINTF("############################################################# \n");
			STemp++;
		}
		printf("========= printing all students finished ========= \n");
		DPRINTF("############################################################# \n");
	}
}

/*********************************************************************************/

int Find_repeat_roll_number(FIFO_BUFF_t *fifo_buff,uint32_t Roll_number)
{
	uint32_t RRMain_count;

	Student_info_t *RTemp=fifo_buff->tail;
	for(RRMain_count=0;RRMain_count<fifo_buff->count;RRMain_count++)
	{
		if (Roll_number==RTemp->RollNumber_m)
		{
			return 0;
			break;
		}
		RTemp++;
	}
	return 1;
}

/*********************************************************************************/

int Check_course_id(uint32_t number)
{
	uint32_t CMain_count;
	uint32_t Count_Check;
	uint32_t Courses_ID[10]={1,2,3,4,5,6,7,8,9,10};
	for(CMain_count=0;CMain_count<Total_number_courses_id;CMain_count++)
	{
		if (number==Courses_ID[CMain_count])
		{
			return 1;
			break;
		}
	}
	return 0;
}

/*********************************************************************************/
/*********************************************************************************/
/************* ########## T #### H ### E ### E ### N ### D ########## ************/
/*********************************************************************************/
/*********************************************************************************/

