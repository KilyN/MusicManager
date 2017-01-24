#ifndef SONG_H
#define SONG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include <ctype.h>



// structure for the time 
typedef struct Songlength
{
	int mins;     // minutes 
	int secs;     // seconds 
} song_length;

// structure for the doubly linked list node     
typedef struct Mylist 
{        
	char* artist;
	char* album;    
	char* title;   
	char* genre;
	song_length len; 
	int times;    /* time played */
	int rating;

	/* link to previous and next node */
	struct Mylist * pPrev;
	struct Mylist * pNext;    
} mylist;

/*
Function: get_menu
Description: Display the menu, get the choice from the user
Return: choice
*/
char get_menu();


/*
Function: store_list
Description: Store the list of records to file
Parameter:  list -- the doubly linked list 
*/      
void store_list(mylist* list);  

/*
Function: free_list
Description: Destroy the list of records 
Parameter:  list -- the doubly linked list 
*/
void free_list(mylist* list);


/*
Function: load_list
Description: Read records from the file 
Return: list loaded from the file
*/
mylist* load_list();


/*
Function: delete_record
Description: Delete the record by sont title  
Parameter:  list -- the doubly linked list 
Return: result list
*/                  
mylist* delete_record(mylist* list);    

/*
Function: read_record
Description: Read new record from the user  
Return: result node
*/                  
mylist* read_record(); 

/*
Function: insert_record
Description: Insert new record   
Parameter:  list -- the doubly linked list 
tmp -- new record to insert
sortOpt -- sort option
Return: result list
*/                  
mylist* insert_record(mylist* list, mylist* tmp, char sortOpt);   

/*
Function: compare
Description: Compare two node   
Parameter:  node1 -- first node 
node2 -- second node  
sortOpt -- sort option
Return: 0 if same, <0 if node1 < node2, or >0 if node1 > node2
*/       
int compare(mylist* node1, mylist* node2, char sortOpt);

/*
Function: display
Description: Display the song 
Parameter:  list -- the node to display 
*/
void display(mylist* node);

/*
Function: search
Description: Search by a field  
Parameter:  list -- the doubly linked list 
Return: result node
*/                  
mylist* search(mylist* list);

/*
Function: sort_list
Description: Sort the list  
Parameter:  list -- the doubly linked list 
sortOpt -- sort option
Return: result list
*/    
mylist* sort_list(mylist* list, char sortOpt); 


/*
Function: edit_record
Description: Edit the record 
Parameter:  node -- the node to edit 
*/
void edit_record(mylist* node);


#endif





