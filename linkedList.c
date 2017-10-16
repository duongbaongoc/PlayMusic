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

#include "linkedList.h"

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
	unsigned int rating, Data *pData)
{
	int success = 1;

	//update artist field
	pData->artist = (char *)malloc(strlen(artist) + 1);
	if (pData->artist == NULL)
	{
		puts("Can not allocate memory for artist field.");
		success = 0;
	}
	else
		strcpy(pData->artist, artist);
	//update album_title field
	pData->album_title = (char *)malloc(strlen(album_title) + 1);
	if (pData->album_title == NULL)
	{
		puts("Can not allocate memory for album_title field.");
		success = 0;
	}
	else
		strcpy(pData->album_title, album_title);
	//update song_title field
	pData->song_title = (char *)malloc(strlen(song_title) + 1);
	if (pData->song_title == NULL)
	{
		puts("Can not allocate memory for song_title field.");
		success = 0;
	}
	else
		strcpy(pData->song_title, song_title);
	//update genre field
	pData->genre = (char *)malloc(strlen(genre) + 1);
	if (pData->genre == NULL)
	{
		puts("Can not allocate memory for genre field.");
		success = 0;
	}
	else
		strcpy(pData->genre, genre);
	//update dur (duration) field
	pData->dur.min = min;
	pData->dur.sec = sec;
	//update times_played and rating fields
	pData->times_played = time_played;
	pData->rating = rating;

	return success;
}

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
Node *make_node(Data newData, int *success)
{
	Node *pMem = (Node *)malloc(sizeof(Node));
	*success = 1;

	if (pMem == NULL)
	{
		puts("Can not allocate memory for pMem.");
		success = 0;
	}
	else
	{
		//update artist field
		pMem->info.artist = (char *)malloc(strlen(newData.artist) + 1);
		if (pMem->info.artist == NULL)
		{
			puts("Can not allocate memory for artist field.");
			success = 0;
		}
		else
			strcpy(pMem->info.artist, newData.artist);
		//update album_title field
		pMem->info.album_title = (char *)malloc(strlen(newData.album_title) + 1);
		if (pMem->info.album_title == NULL)
		{
			puts("Can not allocate memory for album_title field.");
			success = 0;
		}
		else
			strcpy(pMem->info.album_title, newData.album_title);
		//update song_title field
		pMem->info.song_title = (char *)malloc(strlen(newData.song_title) + 1);
		if (pMem->info.song_title == NULL)
		{
			puts("Can not allocate memory for song_title field.");
			success = 0;
		}
		else
			strcpy(pMem->info.song_title, newData.song_title);
		//update genre field
		pMem->info.genre = (char *)malloc(strlen(newData.genre) + 1);
		if (pMem->info.genre == NULL)
		{
			puts("Can not allocate memory for genre field.");
			success = 0;
		}
		else
			strcpy(pMem->info.genre, newData.genre);
		//update dur (duration) field
		pMem->info.dur.min = newData.dur.min;
		pMem->info.dur.sec = newData.dur.sec;
		//update times_played and rating fields
		pMem->info.times_played = newData.times_played;
		pMem->info.rating = newData.rating;
		//init pNext and pPrev
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}

/********************************************************************************
* Function: print_list()														*
* Date Created: 06/18/2017													    *
* Description: This function prints out the entire list to the screen			*
*				using recursive.											    *
* Input parameters: a list (List)												*
* Returns: none																	*
* Preconditions: at beginning of program.										*
* Postconditions: Content of the list is displayed to the screen.				*
********************************************************************************/
void print_list(List l)
{
	List l1 = { NULL };
	//base: if the list is empty
	if (l.pHead == NULL)
		puts("-> NULL");
	//recursive
	else
	{
		//display content of the first node
		printf("-> %s/ %s/ %s/ %s/ %d:%d/ %d/ %d \n", l.pHead->info.artist,
			l.pHead->info.album_title, l.pHead->info.song_title,
			l.pHead->info.genre, l.pHead->info.dur.min, l.pHead->info.dur.sec,
			l.pHead->info.times_played, l.pHead->info.rating);

		l1.pHead = l.pHead->pNext;
		print_list(l1);
	}
}

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
int insert_front(List *l, Data newSong)
{
	int make_node_success, insert_front_success = 1;
	Node *pMem = make_node(newSong, &make_node_success);


	if (make_node_success == 0) //failed to make node
	{
		insert_front_success = 0;
		puts("Failed to make a node out of the given data.");
	}
	else //make node successfully
	{
		if (l->pHead == NULL) //insert front to an empty list
		{
			l->pHead = pMem;
		}
		else
		{
			pMem->pNext = l->pHead;
			l->pHead->pPrev = pMem;
			l->pHead = pMem;
		}
	}
	return insert_front_success;
}