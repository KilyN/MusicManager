/*******************************************************************************
   NAME: Kily Nhan
   DATE: 07/07/2015
   CLASS: CptS 122
   HOMEWORK: PA2
   DESCRIPTION: This program allows user to edit,sort,rate,delete,search a record
                 of songs. It also reads from the file and save to txt file.
 ********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include "functions.h"

int main()
{
	char menu;
	char sortOpt = 'A';    
	mylist* list = NULL;
	mylist* tmp;

	menu = get_menu();

	while (menu != 'X')
	{
		
		if (menu == 'L')         // to load record
		{            
			free_list(list); 
			list = load_list(); 
			printf("Records loaded\n");
		}
		else if (menu == 'S')
		{        
			store_list(list);
			printf("Records stored\n");
		}
		else if (menu == 'A')
		{
			if (list == NULL)
				printf("Empty list\n");
			else
			{
				tmp = list;
				do
				{
					display(tmp);
					tmp = tmp->pNext;
				} while (tmp != list);
			}
		}              
		else if (menu == 'H')
		{
			if (list == NULL)
				printf("Empty list\n");
			else
			{
				tmp = search(list);
				if (tmp == NULL)
					printf("Song not found\n");
				else
					display(tmp);
			}
		} 
		else if (menu == 'I')
		{
			tmp = read_record();
			list = insert_record(list, tmp, sortOpt);
		}     
		else if (menu == 'D')
		{
			list = delete_record(list);            
		}     
		else if (menu == 'E')
		{  
			tmp = search(list);
			if (tmp == NULL)
				printf("Song not found\n");
			else
				edit_record(tmp);
		}     
		else if (menu == 'T')
		{
			printf("Select option('G'=genre,'R'=rating,'A'=artist): ");
			sortOpt = toupper(getchar());
			while (getchar() != '\n') ;
			list = sort_list(list, sortOpt);
			printf("List sorted\n");
		}     
		else if (menu == 'R')
		{    
			tmp = search(list);
			if (tmp == NULL)
				printf("Song not found\n");
			else
			{
				printf("Old rating: %d, enter new rating: ", tmp->rating);
				scanf("%d", &(tmp->rating)); 
				while (getchar() != '\n') ;
			}
		}
		else
		{
			printf("Invalid choice\n");
		} 
		printf("\n");
		menu = get_menu();
	}

	store_list(list);
	free_list(list); 

	return 0;
}



