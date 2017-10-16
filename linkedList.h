/*****************************************************************************************************************
* Programmer: Ngoc Bao Duong																					 *
* Class: CptS 122.01                                                                                             *
* Programming Assignment: Assignment 3																			 *
* Date: 06/18/2017												                         						 *
* Updated: 06/26/2017																							 *
* Description: This assignment manipulates a music collection based on attributes such as artist, album title,	 *
*				song title, genre, song length, number times played, and rating.								 *
* Note: Assuming the csv data ends with an empty line.															 *
* Note: Change the time playing songs by: source.c -> play_a_song() -> delay(CHANGE NUMBER OF SECOND HERE)		 *
* EXTRA WORK: Choose method of sorting (selection/insertion) in source.c/runprogram/option 7					 *
*			still working on bubble sort																		 *
*			Add more 1 sorting method: sort by duration at each selection/insertion sort function.				 *
*****************************************************************************************************************/

#include <stdio.h>
#include <string.h>

//Duration struct
typedef struct duration
{
	unsigned int min;
	unsigned int sec;
}Duration; //size == 8

		   //Data struct
typedef struct data
{
	char *artist;
	char *album_title;
	char *song_title;
	char *genre;
	Duration dur;
	unsigned int times_played;
	unsigned int rating;
}Data; //size == 32

	   //Node struct
typedef struct node
{
	Data info;
	struct node *pNext;
	struct node *pPrev;
}Node; //size == 40

	   //Doubly linked list struct
typedef struct list
{
	Node *pHead;
}List; //size == 4

/********************************************************************************
* Function: make_data()															*
* Date Created: 06/18/2017													    *
* Description: This function creates a data using infomation provided.		    *
* Input parameters: artist (string), album_title (string), song_title (string),	*
*					genre (string), min (int), sec (int), time_played (int),	*
*					rating (int), pointer to a data (Data)						*
* Returns: success (int), updated data											*
* Preconditions: at beginning of program.										*
* Postconditions: all fields of the data are set to provided values. If there	*
*		is a field that can not be allocated, a noti will show up on the screen,*
*		and success == 0 is returned.											*
********************************************************************************/
int make_data(char *artist, char *album_title, char *song_title, char *genre,
	unsigned int min, unsigned int sec, unsigned int time_played,
	unsigned int rating, Data *pData);

/********************************************************************************
* Function: make_node()															*
* Date Created: 06/18/2017													    *
* Description: This function creates a Node for the given data.				    *
* Input parameters: a data (Data), pointer to success (int)						*
* Preconditions: make_data() is defined; make_data() succeeds.					*
* Postconditions: all fields of the data is copied to of the Node,				*
*				and pointers of the Node are set to NULL. If there is a field	*
*				or the node itself that can not be allocated, success will be	*
*				set to 0.														*
********************************************************************************/
Node *make_node(Data newData, int *success);

/********************************************************************************
* Function: print_list()														*
* Date Created: 06/18/2017													    *
* Description: This function prints out the entire list to the screen.		    *
* Input parameters: a list (List)												*
* Returns: none																	*
* Preconditions: at beginning of program.										*
* Postconditions: Content of the list is displayed to the screen.				*
********************************************************************************/
void print_list(List l);

/********************************************************************************
* Function: insert_front()														*
* Date Created: 06/18/2017													    *
* Description: This function inserts a new song (Data) at front of the list.	*
* Input parameters: pointer to a list (List), a data (Data)						*
* Returns: success (int)														*
* Preconditions: make_node() is defined.										*
* Postconditions: the new song is inserted at front of the list. If succeeds,	*
*				1 is returned, otherwise 0 is returned.							*
********************************************************************************/
int insert_front(List *l, Data newSong);