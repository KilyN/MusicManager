#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"


/*
Function: display
Description: Display the song 
Parameter:  list -- the node to display 
*/
void display(mylist* node)
{  
	if (node == NULL)
		return;

	printf("________________________________________\n");
	printf("Artist: %s\n", node->artist);
	printf("Album title: %s\n", node->album);
	printf("Song title: %s\n", node->title);
	printf("Genre: %s\n", node->genre);
	printf("Song length: %d:%02d\n", node->len.mins, node->len.secs);
	printf("Number times played: %d\n", node->times);  
	printf("Rating: %d\n", node->rating);  
	printf("________________________________________\n\n");
}

/*
Function: get_menu
Description: Display the menu, get the choice from the user
Return: choice
*/
char get_menu()
{
	char option;
	printf("**************** DIGITAL MUSIC MANAGER ****************\n");
	printf("L. Load from file\n");
	printf("S. Store to file\n");
	printf("A. Display all records\n"); 
	printf("H. Search and display record\n"); 
	printf("I. Insert record\n"); 
	printf("E. Edit record\n");
	printf("D. Delete record\n");    
	printf("T. Sort records\n");   
	printf("R. Rate\n"); 
	printf("X. Exit program\n");
	printf("Enter letter choice: ");

	option = getchar();

	
	while (getchar() != '\n') ;                             /* ignore other chars in this line */

 	
	return (char)toupper(option);                     // convert to upper case 
}


/*
Function: store_list
Description: Store the list of records to file
Parameter:  list -- the doubly linked list 
*/      
void store_list(mylist* list)
{  
	mylist* curr = list;
	FILE* file = fopen("records.txt", "w");

	if (curr != NULL)
	{
		do
		{   
			fprintf(file, "%d %d %d %d\n%s\n%s\n%s\n%s\n", 
				curr->len.mins, curr->len.secs, curr->times, curr->rating,
				curr->artist, curr->album, curr->title, curr->genre);

			curr = curr->pNext;
		} while (list != curr);   
	}

	fclose(file);
}  

/*
Function: free_list
Description: Destroy the list of records 
Parameter:  list -- the doubly linked list 
*/
void free_list(mylist* list)
{
	mylist* tmp;
	mylist* first = list;
	if (list != NULL)
	{
		do
		{   
			tmp = list;
			list = list->pNext;
			free(tmp->artist); 
			free(tmp->album);
			free(tmp->title);
			free(tmp->genre);
			free(tmp);
		} while (list != first);   
	}
}    

/*
Function: load_list
Description: Read records from the file 
Return: list loaded from the file
*/
mylist* load_list()
{

	FILE* file = fopen("records.txt", "r");
	mylist* list = NULL;
	mylist* tmp;
	char ch;
	int i, n;
	char* pstr;

	if (file == NULL)
		return NULL;

	tmp = (mylist*)malloc(sizeof(mylist));

	while (fscanf(file, "%d %d %d %d", &(tmp->len.mins),
		&(tmp->len.secs), &(tmp->times), &(tmp->rating)) == 4)
	{
		tmp->artist = (char*)malloc(128);      
		tmp->album = (char*)malloc(128);         
		tmp->title = (char*)malloc(128);               
		tmp->genre = (char*)malloc(128);

		/* ignore this line */
		while (fgetc(file) != '\n') ;

		/* read 4 line of text */
		for (n = 0; n < 4; n++)
		{ 
			if (n == 0)
				pstr = tmp->artist;  
			else if (n == 1)
				pstr = tmp->album;    
			else if (n == 2)
				pstr = tmp->title;  
			else 
				pstr = tmp->genre;

			i = 0;

			for (ch = fgetc(file); ch != '\n'; ch = fgetc(file))
			{
				if (ch != '\r') 
					pstr[i++] = ch;
			}
			pstr[i] = '\0';
		}          


		if (list == NULL)
		{
			list = tmp; 
			tmp->pNext = tmp->pPrev = tmp;
		}
		else
		{
			tmp->pNext = list;
			tmp->pPrev = list->pPrev;
			list->pPrev->pNext = tmp;
			list->pPrev = tmp;
		}

		tmp = (mylist*)malloc(sizeof(mylist));
	}

	fclose(file);
	free(tmp);

	return list;
}

/*
Function: delete_record
Description: Delete the record by sont title  
Parameter:  list -- the doubly linked list 
Return: result list
*/                  
mylist* delete_record(mylist* list)
{ 
	char title[128]; 
	mylist* tmp = list;

	if (list == NULL)
	{
		printf("Empty list\n");
		return list;
	}

	printf("Enter the song title to delete: ");
	gets(title);

	do
	{
		/* find the song */
		if (strcmp(title, tmp->title) == 0)
		{
			if (tmp == list)
			{
				if (list->pNext == list)
					list = NULL;
				else
					list = list->pNext;
			}

			tmp->pNext->pPrev = tmp->pPrev;
			tmp->pPrev->pNext = tmp->pNext;   
			free(tmp->artist); 
			free(tmp->album);
			free(tmp->title);
			free(tmp->genre);
			free(tmp);

			printf("Song %s deleted\n", title);
			return list;
		}

		tmp = tmp->pNext;
	} while (tmp != list);

	printf("Song not found\n");

	return list;
}

/*
Function: read_record
Description: Read new record from the user  
Return: result node
*/                  
mylist* read_record()
{ 
	mylist* tmp = (mylist*)malloc(sizeof(mylist));

	printf("Please enter values for all attributes: \n");       
	printf("Artist: ");
	tmp->artist = (char*)malloc(128);
	gets(tmp->artist);

	printf("Album Title: ");  
	tmp->album = (char*)malloc(128);
	gets(tmp->album);

	printf("Song Title: ");  
	tmp->title = (char*)malloc(128);
	gets(tmp->title);

	printf("Genre: ");  
	tmp->genre = (char*)malloc(128);
	gets(tmp->genre);

	printf("Minutes (length): ");    
	scanf("%d", &(tmp->len.mins));
	printf("Seconds (length): ");
	scanf("%d", &(tmp->len.secs));

	printf("Times Played: ");
	scanf("%d", &(tmp->times));

	printf("Rating: ");
	scanf("%d", &(tmp->rating));

	/* ignore other chars in this line */
	while (getchar() != '\n') ;

	return tmp;
} 

/*
Function: insert_record
Description: Insert new record   
Parameter:  list -- the doubly linked list 
tmp -- new record to insert
sortOpt -- sort option
Return: result list
*/                  
mylist* insert_record(mylist* list, mylist* tmp, char sortOpt)
{    
	mylist* curr = list; 

	if (list == NULL)
	{
		list = tmp;
		tmp->pNext = tmp->pPrev = tmp;
	}
	else
	{
		/* find the position to insert */
		do
		{
			if (compare(tmp, curr, sortOpt) <= 0)
				break;
			curr = curr->pNext;
		} while (curr != list);

		/* insert before curr */
		tmp->pNext = curr;
		tmp->pPrev = curr->pPrev;
		curr->pPrev->pNext = tmp;
		curr->pPrev = tmp;

		if (curr == list && compare(tmp, curr, sortOpt) <= 0)
			list = tmp;
	}


	return list;
}


/*
Function: compare
Description: Compare two node   
Parameter:  node1 -- first node 
node2 -- second node  
sortOpt -- sort option
Return: 0 if same, <0 if node1 < node2, or >0 if node1 > node2
*/       
int compare(mylist* node1, mylist* node2, char sortOpt)
{
	/* sort by artist or genre or rating */ 
	if (sortOpt == 'G') 
		return strcmp(node1->genre, node2->genre);
	else if (sortOpt == 'R') 
		return node1->rating - node2->rating; 

	return strcmp(node1->artist, node2->artist);
}

/*
Function: search
Description: Search by a field  
Parameter:  list -- the doubly linked list 
Return: result node
*/                  
mylist* search(mylist* list)
{        
	char key[128];
	int value = 0;
	mylist* tmp = list;     

	if (list == NULL)
	{
		printf("Empty list\n");
		return NULL;
	}

	printf("Enter the search key: ");
	gets(key);

	value = atoi(key);

	do
	{
		if (strcmp(key, tmp->artist) == 0 ||
			strcmp(key, tmp->album) == 0 ||  
			strcmp(key, tmp->title) == 0 ||    
			strcmp(key, tmp->genre) == 0)
			return tmp;
		if (isdigit(key[0]))
		{
			if (tmp->len.mins == value || 
				tmp->len.secs == value ||
				tmp->times == value ||
				tmp->rating == value)
				return tmp;
		}
		tmp = tmp->pNext;

	} while (tmp != list);

	return NULL;
}

/*
Function: sort_list
Description: Sort the list  
Parameter:  list -- the doubly linked list 
sortOpt -- sort option
Return: result list
*/    
mylist* sort_list(mylist* list, char sortOpt)
{
	mylist* tmp = list;
	mylist* result = NULL;
	mylist* curr;

	if (list == NULL)
		return NULL;

	do
	{
		curr = tmp;
		tmp = tmp->pNext;

		result = insert_record(result, curr, sortOpt);

	} while (tmp != list);

	return result;
} 

/*
Function: edit_record
Description: Edit the record 
Parameter:  node -- the node to edit 
*/
void edit_record(mylist* node)
{     
	char ch[128];
	int val = 0;

	printf("\nOld artist: %s\n", node->artist);
	printf("Enter new artist(blank line to skip): ");
	gets(ch);
	if (ch[0] != '\0')
		strcpy(node->artist, ch);

	printf("\nOld album title: %s\n", node->album);
	printf("Enter new album title(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		strcpy(node->album, ch);

	printf("\nOld song title: %s\n", node->title);
	printf("Enter new song title(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		strcpy(node->title, ch);

	printf("\nOld genre: %s\n", node->genre);
	printf("Enter new genre(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		strcpy(node->genre, ch);

	printf("\nOld minutes: %d\n", node->len.mins);
	printf("Enter new minutes(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		node->len.mins = atoi(ch);

	printf("\nOld seconds: %d\n", node->len.secs);
	printf("Enter new seconds(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		node->len.secs = atoi(ch);

	printf("\nOld times played: %d\n", node->times);
	printf("Enter new times played(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		node->times = atoi(ch); 
	printf("\nOld rating: %d\n", node->rating);
	printf("Enter new rating(blank line to skip): "); 
	gets(ch);
	if (ch[0] != '\0')
		node->rating = atoi(ch);

}







