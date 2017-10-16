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

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include <stdlib.h> //for atof()
#include <time.h> // used to delay time in play() and rand()

/********************************************************************************
* Function: display_menu()														*
* Date Created: 06/18/2017													    *
* Description: This function displays all options to the screen.			    *
* Input parameters: none														*
* Returns: none																	*
* Preconditions: at beginning of program.										*
* Postconditions: all 11 options are displayed on the screen.					*
********************************************************************************/
void display_menu();

/********************************************************************************
* Function: get_option()														*
* Date Created: 06/18/2017													    *
* Description: This function promts the user for a valid option from the menu.  *
* Input parameters: pointer to option variable (int)							*
* Returns: updated option														*
* Preconditions: at beginning of program.										*
* Postconditions: a valid option is returned.									*
********************************************************************************/
void get_option(int *option);

/********************************************************************************
* Function: print_all_records()													*
* Date Created: 06/18/2017													    *
* Date Edited: 06/26/2017														*
* Description: This function prints out all records to the screen				*
*				using recursive.											    *
* Input parameters: a list (List), pointer to count (int)						*
* Returns: updated count (total number of songs)								*
* Preconditions: at beginning of program.										*
* Postconditions: Content of the list is displayed to the screen.				*
********************************************************************************/
void print_all_records(List l, int *count);

/********************************************************************************
* Function: print_artist_songs()												*
* Date Created: 06/18/2017													    *
* Description: This function prints out the all records of a given artist		*
*				using recursive.											    *
* Input parameters: a list (List), an artist (char []), pointer to count (int)	*
* Returns: updated count (number of recored printed)							*
* Preconditions: at beginning of program.										*
* Postconditions: all records of the artist are displayed to the screen.		*
********************************************************************************/
void print_artist_songs(List l, char name[50], int *count);

/********************************************************************************
* Function: edit_a_record()														*
* Date Created: 06/19/2017													    *
* Description: This function promts the user info to edit data of a node.	    *
* Input parameters: pointer to a Node to edit									*
* Returns: updated Node															*
* Preconditions: pointer to the node is not NULL.								*
* Postconditions: only info (Data) of the node is updated as user desires.		*
********************************************************************************/
void edit_a_record(Node *this_node);

/********************************************************************************
* Function: delay()																*
* Date Created: 06/19/2017													    *
* Description: This function pause program execution for a given time.		    *
* Input parameters: amount of seconds to pause (int)							*
* Returns: none																	*
* Preconditions: at beginning of program										*
* Postconditions: no code is executed for a period of time.						*
********************************************************************************/
void delay(int seconds);

/********************************************************************************
* Function: play_a_song()														*
* Date Created: 06/19/2017													    *
* Date Edited: 06/26/2017													    *
* Description: This function display all content of a record for a period of	*
*				time then the screen is cleared out, and increases time played	*
*				of the song by 1.												*
* Input parameters: Pointer to a node (Node)									*
* Returns: updated pointer														*
* Preconditions: the pointer is not NULL										*
* Postconditions: recored is displayed then cleared out, time played is added 1.*
********************************************************************************/
void play_a_song(Node *current_node);

/********************************************************************************
* Function: load()																*
* Date Created: 06/18/2017													    *
* Date Edited: 06/26/2017														*
* Description: This function read all records from a file into a list (List).   *
* Input parameters: name of a file (char []), pointer to a list (List)			*
* Returns: updated list															*
* Preconditions: the list is empty; make_data() and insert_front() are defined.	*
* Postconditions: if the file is opened successfully, each record from the file	*
*				is copied to each node in the list as inserted at front;		*
*				otherwise, a noti will show up.									*
********************************************************************************/
void load(char file_name[20], List *album);

/********************************************************************************
* Function: store()																*
* Date Created: 06/18/2017													    *
* Description: This function writes all the records in a list (List) to a file.	*
* Input parameters: name of a file (char []), a list (List)						*
* Returns: none																	*
* Preconditions:at beginning of program											*
* Postconditions: all records in the list are writen into the file.				*
********************************************************************************/
void store(char file_name[20], List album);

/********************************************************************************
* Function: display()															*
* Date Created: 06/18/2017													    *
* Date Edited: 06/26/2017														*
* Description: This function displays either all records or all records matching*
*				an artist.													    *
* Input parameters: a list (List)												*
* Returns: none																	*
* Preconditions: print_all_records() and print_artist_songs are defined.		*
* Postconditions: displays either all records or all records matching an artist.*
********************************************************************************/
void display(List l);


/********************************************************************************
* Function: edit()																*
* Date Created: 06/19/2017													    *
* Description: This function lets user edit one chosen record.				    *
* Input parameters: pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: edit_a_record(), print_artist_song() are defined.				*
* Postconditions: a chosen record from the list is updated as user desires.		*
********************************************************************************/
void edit(List *l);

/********************************************************************************
* Function: rate()																*
* Date Created: 06/19/2017													    *
* Description: This function asks the user for a song and lets user				*
*			assign a value of 1 – 5 to the song.							    *
* Input parameters: pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: At beginning of program.										*
* Postconditions: Name of a song is promted, then its rating in the list is		*
*				updated as user desires, and the updated record is displayed.	*
********************************************************************************/
void rate(List *l);

/********************************************************************************
* Function: play()																*
* Date Created: 06/19/2017													    *
* Description: This function asks the user for a song, then displays content of	*
*				each song in the list starting from the promted song.			*
* Input parameters:	a list (List)												*
* Returns: none																	*
* Preconditions: At beginning of program.										*
* Postconditions: Each song's content is displayed in order in a short period	*
*			of time starting from a song promted from the user.					*
********************************************************************************/
void play(List l);

/********************************************************************************
* Function: insert()															*
* Date Created: 06/20/2017													    *
* Description: This function promts info of a record from user then inserts it	*
*				at beginning of the list.										*
* Input parameters:	pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: at beginning of program										*
* Postconditions: the list has one more node at front							*
********************************************************************************/
void insert(List *l);

/********************************************************************************
* Function: delete()															*
* Date Created: 06/20/2017													    *
* Description: This function promts user for a song name then deletes it from	*
*				the list.														*
* Input parameters:	pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: at beginning of program										*
* Postconditions: if the list is empty, a message will show up. If the list has *
*			the song, the song will be removed from the list; otherwise the list*
*			will remain the same.												*
********************************************************************************/
void delete(List *l);

/********************************************************************************
* Function: shuffle()															*
* Date Created: 06/26/2017													    *
* Description: This function plays all songs of the list randomly.				*
* Input parameters:	a list (List)												*
* Returns: none																	*
* Preconditions: print_all_records() and play_a_song() are defined.				*
* Postconditions: Each song of the list is displayed at randomly order.			*
********************************************************************************/
void shuffle(List l);

/********************************************************************************
* Function: move_node_insertion_sorting()										*
* Date Created: 06/26/2017													    *
* Description: This function supports insertion sort (ascending) for a linked	*
*		list by moving a node from its original position to the right position.	*
* Input parameters:	3 pointers to Nodes and a pointer to a List					*
* Returns: updated pointers														*
* Preconditions: the list has at least 2 nodes, pMem needs to be moved.			*
* Postconditions: mMem is moved to the right position in order of ascending.	*
********************************************************************************/
void move_node_insertion_sorting(Node *pPosition, Node *pMem,
	Node *pCur, List *l);

/********************************************************************************
* Function: insertion_sort()													*
* Date Created: 06/26/2017													    *
* Description: This function promts user for a method of sorting then uses		*
*			insertion sort to arrange all items of the list in ascending order.	*
* Input parameters:	pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: move_node_insertion_sorting() is defined.						*
* Postconditions: All items of the list are in ascending order based on			*
*			the promted sorting method.											*
********************************************************************************/
void insertion_sort(List *l);

/********************************************************************************
* Function: selection_sort()													*
* Date Created: 06/26/2017													    *
* Description: This function promts user for a method of sorting then uses		*
*			selection sort to arrange all items of the list in ascending order.	*
* Input parameters:	pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: at beginning of program										*
* Postconditions: All items of the list are in ascending order based on			*
*			the promted sorting method.											*
********************************************************************************/
void selection_sort(List *l);

/********************************************************************************
* Function: bubble_sort()														*
* Date Created: 06/26/2017													    *
* Description: This function promts user for a method of sorting then uses		*
*			bubble sort to arrange all items of the list in ascending order.	*
* Input parameters:	pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: at beginning of program										*
* Postconditions: All items of the list are in ascending order based on			*
*			the promted sorting method.											*
********************************************************************************/
void bubble_sort(List *l);

/********************************************************************************
* Function: run_program()														*
* Date Created: 06/19/2017													    *
* Description: This function asks user for options from the option menu then	*
*				executes the actions.										    *
* Input parameters: none														*
* Returns: none																	*
* Preconditions: all other functions must be defined.							*
* Postconditions: promts user for an option and execute it until user chooses	*
*				to exit. All changes in the list and file are saved.			*
********************************************************************************/
void run_program();

#endif

