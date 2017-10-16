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
#include "header.h"

/********************************************************************************
* Function: display_menu()														*
* Date Created: 06/18/2017													    *
* Description: This function displays all options to the screen.			    *
* Input parameters: none														*
* Returns: none																	*
* Preconditions: at beginning of program.										*
* Postconditions: all 11 options are displayed on the screen.					*
********************************************************************************/
void display_menu()
{
	puts("***MENU***");
	puts("(1)  load");
	puts("(2)  store");
	puts("(3)  display");
	puts("(4)  insert");
	puts("(5)  delete");
	puts("(6)  edit");
	puts("(7)  sort");
	puts("(8)  rate");
	puts("(9)  play");
	puts("(10) shuffle");
	puts("(11) exit");
}

/********************************************************************************
* Function: get_option()														*
* Date Created: 06/18/2017													    *
* Description: This function promts the user for a valid option from the menu.  *
* Input parameters: pointer to option variable (int)							*
* Returns: updated option														*
* Preconditions: at beginning of program.										*
* Postconditions: a valid option is returned.									*
********************************************************************************/
void get_option(int *option)
{
	*option = 0;
	do
	{
		display_menu();
		puts("Please select an option from the menu: ");
		scanf("%d", option);
		if (*option < 1 || *option > 11)
		{
			puts("Your input is invalid. Please press any key to choose again.");
			getch();
			system("@cls||clear"); // clear screen
		}
	} while (*option < 1 || *option > 11); //check for input validation
}

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
void print_all_records(List l, int *count)
{
	List l1 = { NULL };
	//base: if the list is empty
	if (l.pHead == NULL)
	{
		if (*count == 0)
			puts("No record found.");
	}
	//recursive
	else
	{
		printf("%-25s%-25s%-20s%-10s%d:%-10d%-15d%d \n", l.pHead->info.artist,
			l.pHead->info.album_title, l.pHead->info.song_title,
			l.pHead->info.genre, l.pHead->info.dur.min, l.pHead->info.dur.sec,
			l.pHead->info.times_played, l.pHead->info.rating);
		(*count)++;
		l1.pHead = l.pHead->pNext;
		print_all_records(l1, count);
	}
}

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
void print_artist_songs(List l, char name[50], int *count)
{
	List l1 = { NULL };
	//base: if the list is empty
	if (l.pHead == NULL)
	{
		if (*count == 0)
			puts("No record of the artist found.");
	}
	//recursive
	else
	{
		if (strcmp(l.pHead->info.artist, name) == 0) //find a record of the artist
		{
			printf("%-25s%-25s%-20s%-10s%d:%-10d%-15d%d \n", l.pHead->info.artist,
				l.pHead->info.album_title, l.pHead->info.song_title,
				l.pHead->info.genre, l.pHead->info.dur.min, l.pHead->info.dur.sec,
				l.pHead->info.times_played, l.pHead->info.rating);
			(*count)++;
		}
		l1.pHead = l.pHead->pNext;
		print_artist_songs(l1, name, count);
	}
}

/********************************************************************************
* Function: edit_a_record()														*
* Date Created: 06/19/2017													    *
* Description: This function promts the user info to edit data of a node.	    *
* Input parameters: pointer to a Node to edit									*
* Returns: updated Node															*
* Preconditions: pointer to the node is not NULL.								*
* Postconditions: only info (Data) of the node is updated as user desires.		*
********************************************************************************/
void edit_a_record(Node *this_node)
{
	//variables to store info promted from user
	char str[50] = "";
	unsigned int num = 0;

	//promt info and update info
	puts("\nPlease enter new info for this record.");

	puts("New Artist:");
	scanf(" %[^\n]%*c", str);
	strcpy(this_node->info.artist, str);

	puts("New Album Title:");
	scanf(" %[^\n]%*c", str);
	strcpy(this_node->info.album_title, str);

	puts("New Song Title:");
	scanf(" %[^\n]%*c", str);
	strcpy(this_node->info.song_title, str);

	puts("New Genre:");
	scanf(" %[^\n]%*c", str);
	strcpy(this_node->info.genre, str);

	puts("New Duration:");
	scanf(" %[^\n]%*c", str);
	this_node->info.dur.min = (unsigned int)atof(strtok(str, ":"));
	this_node->info.dur.sec = (unsigned int)atof(strtok(NULL, ""));

	puts("New Times Played:");
	scanf(" %d", &num);
	this_node->info.times_played = num;

	puts("New Rating:");
	scanf(" %d", &num);
	this_node->info.rating = num;
}

/********************************************************************************
* Function: delay()																*
* Date Created: 06/19/2017													    *
* Description: This function pause program execution for a given time.		    *
* Input parameters: amount of seconds to pause (int)							*
* Returns: none																	*
* Preconditions: at beginning of program										*
* Postconditions: no code is executed for a period of time.						*
********************************************************************************/
void delay(int seconds)
{
	const time_t starting_time = time(NULL);
	time_t ending_time, temp = 0;
	puts("");
	do
	{
		ending_time = time(NULL);
		if (ending_time != temp && temp != 0)
			printf("...%d...", ending_time - starting_time);
		temp = ending_time;
	} while (ending_time < starting_time + seconds);
	puts("");
}

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
void play_a_song(Node *current_node)
{
	puts("          PLAYING...\n");
	current_node->info.times_played++;
	//display a song
	printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
		"Album Title", "Song Title",
		"Genre", "Duration", "Time Played", "Rating");
	puts("------------------------------------------------------\
----------------------------------------------------------");
	printf("%-25s%-25s%-20s%-10s%d:%-10d%-15d%d \n", current_node->info.artist,
		current_node->info.album_title, current_node->info.song_title,
		current_node->info.genre, current_node->info.dur.min, current_node->info.dur.sec,
		current_node->info.times_played, current_node->info.rating);
	//hold for short period of time
	delay(3);
	// clear screen
	system("@cls||clear");
}

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
void load(char file_name[20], List *album)
{
	//variable declaration
	int option = 0;
	FILE *file = fopen(file_name, "r");
	char line[200];
	char artist[50] = "", album_title[70] = "",
		song_title[70] = "", genre[20] = "";
	unsigned int min = 0, sec = 0, times = 0, rating = 0;
	Data this_data;

	if (file == NULL)
		puts("File not found!");
	else //infile is opened successfully
	{
		while (!feof(file))
		{
			strcpy(line, "");

			//get a line
			fgets(line, 100, file);
			//stop reading when encounter an empty line
			if (strcmp(line, "") == 0)
				break;

			//get artist
			strcpy(artist, strtok(line, ",")); //get the first token
			strcpy(line, strtok(NULL, ""));  //get the rest of the line
			if (artist[0] == '"') //if the first token is not the full name
			{
				strcat(artist, ",");
				strcat(artist, strtok(line, ",")); //"Swift, Taylor"
				strcpy(line, strtok(NULL, ""));  //get the rest of the line
			}

			//get the rest of each record
			strcpy(album_title, strtok(line, ","));
			strcpy(song_title, strtok(NULL, ","));
			strcpy(genre, strtok(NULL, ","));
			min = (unsigned int)atof(strtok(NULL, ":"));
			sec = (unsigned int)atof(strtok(NULL, ","));
			times = (unsigned int)atof(strtok(NULL, ","));
			rating = (unsigned int)atof(strtok(NULL, ""));

			//combines all fields of each record to a data
			make_data(artist, album_title, song_title, genre, min, sec, times, rating, &this_data);
			insert_front(album, this_data);

			//free memory on heap
			free(this_data.artist);
			free(this_data.album_title);
			free(this_data.song_title);
			free(this_data.genre);
		}
		fclose(file);
		puts("Info loaded successfully!");
	}
}

/********************************************************************************
* Function: store()																*
* Date Created: 06/18/2017													    *
* Description: This function writes all the records in a list (List) to a file.	*
* Input parameters: name of a file (char []), a list (List)						*
* Returns: none																	*
* Preconditions:at beginning of program											*
* Postconditions: all records in the list are writen into the file.				*
********************************************************************************/
void store(char file_name[20], List album)
{
	//variable declaration
	FILE *file = fopen(file_name, "w");

	//traverse throught the list to access info and write them to the file
	while (album.pHead != NULL) //not end of list
	{
		fprintf(file, "%s,%s,%s,%s,%d:%d,%d,%d\n", album.pHead->info.artist,
			album.pHead->info.album_title, album.pHead->info.song_title,
			album.pHead->info.genre, album.pHead->info.dur.min,
			album.pHead->info.dur.sec, album.pHead->info.times_played,
			album.pHead->info.rating);
		//move pHead to the next record
		album.pHead = album.pHead->pNext;
	}
	fclose(file);
	puts("Storing info to outfile successfully!");
}

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
void display(List l)
{
	int option = 0;
	char artist_name[50] = "";
	int count = 0, count1 = 0;

	puts("Please choose an option:\n\
		1) Display all records\n\
		2) Display all records of an artist\n");
	do
	{
		scanf("%d", &option);
		if (option != 1 && option != 2)
			puts("Please enter 1 or 2:");
	} while (option != 1 && option != 2);

	if (option == 1) //Display all records
	{
		printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
			"Album Title", "Song Title",
			"Genre", "Duration", "Time Played", "Rating");
		puts("------------------------------------------------------\
----------------------------------------------------------");
		print_all_records(l, &count1);
	}
	else if (option == 2) //Display all records of an artist
	{
		puts("Please enter the artist:");
		scanf(" %[^\n]%*c", artist_name);
		printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
			"Album Title", "Song Title",
			"Genre", "Duration", "Time Played", "Rating");
		puts("------------------------------------------------------\
----------------------------------------------------------");
		print_artist_songs(l, artist_name, &count);
	}
}

/********************************************************************************
* Function: edit()																*
* Date Created: 06/19/2017													    *
* Description: This function lets user edit one chosen record.				    *
* Input parameters: pointer to a list (List)									*
* Returns: updated list															*
* Preconditions: edit_a_record(), print_artist_song() are defined.				*
* Postconditions: a chosen record from the list is updated as user desires.		*
********************************************************************************/
void edit(List *l)
{
	char artist_name[50] = "", song_name[50] = "";
	int count = 0;
	Node *current_node = l->pHead; //set to first node

	puts("Please enter the artist:");
	scanf(" %[^\n]%*c", artist_name);

	//search for all records of the artist
	printf("\nSearching for all songs of %s.\n\n", artist_name);
	printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
		"Album Title", "Song Title",
		"Genre", "Duration", "Time Played", "Rating");
	puts("------------------------------------------------------\
----------------------------------------------------------");
	print_artist_songs(*l, artist_name, &count);

	if (count == 0) //no record found, print_artist_songs will announce a message
	{
	}
	else if (count == 1) //there is only one record to edit
	{
		//search for address of the node containing the record
		while (strcmp(current_node->info.artist, artist_name) != 0)
		{
			current_node = current_node->pNext;
		}
		edit_a_record(current_node);
	}
	else //there are more than 1 record to edit
	{
		printf("\nWhich song of %s do you want to edit?\n", artist_name);
		scanf(" %[^\n]%*c", song_name);

		//search for address of the node containing the record
		while (current_node != NULL && (strcmp(current_node->info.artist, artist_name) != 0 ||
			strcmp(current_node->info.song_title, song_name) != 0))
		{
			current_node = current_node->pNext;
		}

		//check if record is found
		if (current_node == NULL)
			puts("No record found.");
		else
			edit_a_record(current_node);
	}
}

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
void rate(List *l)
{
	char song_name[50] = "";
	Node *current_node = l->pHead;
	int num = 0;

	printf("\nWhich song do you want to rate?\n");
	scanf(" %[^\n]%*c", song_name);

	//search for address of the node containing the song
	while (current_node != NULL && strcmp(current_node->info.song_title, song_name) != 0)
	{
		current_node = current_node->pNext;
	}
	//check if record is found
	if (current_node == NULL)
		puts("No record found.");
	else  //found the song -> rate it
	{
		puts("How do you want to rate the song (1-5)? ");
		scanf(" %d", &num);
		current_node->info.rating = num;

		//display the record after rating
		printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
			"Album Title", "Song Title",
			"Genre", "Duration", "Time Played", "Rating");
		puts("------------------------------------------------------\
----------------------------------------------------------");
		printf("%-25s%-25s%-20s%-10s%d:%-10d%-15d%d \n", current_node->info.artist,
			current_node->info.album_title, current_node->info.song_title,
			current_node->info.genre, current_node->info.dur.min, current_node->info.dur.sec,
			current_node->info.times_played, current_node->info.rating);
	}
}

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
void play(List l)
{
	char song_name[50] = "";
	Node *current_node = l.pHead;

	printf("\nPlease choose a song to start with:  ");
	scanf(" %[^\n]%*c", song_name);

	//search for address of the node containing the song
	while (current_node != NULL && strcmp(current_node->info.song_title, song_name) != 0)
	{
		current_node = current_node->pNext;
	}
	//check if record is found
	if (current_node == NULL)
		puts("No record found.");
	else  //found the song -> play the list
	{
		system("@cls||clear"); // clear screen
							   //display each record from the current record to the end of list
		while (current_node != NULL)
		{
			play_a_song(current_node);
			//update statement
			current_node = current_node->pNext;
		}

		//display each record from beginning of the list to before the promted song
		current_node = l.pHead;

		while (strcmp(current_node->info.song_title, song_name) != 0)
		{
			play_a_song(current_node);
			//update statement
			current_node = current_node->pNext;
		}

		puts("All songs have been played.");
	}
}

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
void insert(List *l)
{
	char artist[50] = "", album_title[50] = "",
		song_title[50] = "", genre[50] = "", temp[50] = "";
	unsigned int min = 0, sec = 0, time_played = 0, rating = 0;
	Data new_record;

	//ask user for a record
	puts("----Provide info of a record----");

	printf("Artist: ");
	scanf(" %[^\n]%*c", artist);
	printf("Album title: ");
	scanf(" %[^\n]%*c", album_title);
	printf("Song title: ");
	scanf(" %[^\n]%*c", song_title);
	printf("Genre: ");
	scanf(" %[^\n]%*c", genre);
	printf("Duration: ");
	scanf(" %[^\n]%*c", temp);
	min = (unsigned int)atof(strtok(temp, ":"));
	sec = (unsigned int)atof(strtok(NULL, ""));
	printf("Time played: ");
	scanf("%d", &time_played);
	printf("Rating: ");
	scanf("%d", &rating);

	//combine info to a data
	make_data(artist, album_title, song_title, genre,
		min, sec, time_played, rating, &new_record);
	//insert the data to the list
	insert_front(l, new_record);
}

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
void delete(List *l)
{
	Node *current_node = l->pHead;
	char song_name[50] = "";

	//ask for a song name
	printf("What song do you want to delete? ");
	scanf(" %[^\n]%*c", song_name);

	//check if the list is empty
	if (current_node == NULL)
		puts("The list is empty.");
	else
	{
		//search for address of the node containing the song
		while (current_node != NULL && strcmp(current_node->info.song_title, song_name) != 0)
		{
			current_node = current_node->pNext;
		}
		if (current_node == NULL)
			puts("No song found.");
		else // found the song -> remove it
		{
			//display content of the song
			puts("\nDeleting ....");
			printf("%-25s%-25s%-20s%-10s%-10s%-15s%s \n", "Artist",
				"Album Title", "Song Title",
				"Genre", "Duration", "Time Played", "Rating");
			puts("------------------------------------------------------\
----------------------------------------------------------");
			printf("%-25s%-25s%-20s%-10s%d:%-10d%-15d%d \n\n", current_node->info.artist,
				current_node->info.album_title, current_node->info.song_title,
				current_node->info.genre, current_node->info.dur.min, current_node->info.dur.sec,
				current_node->info.times_played, current_node->info.rating);
			//remove the node out of the list: 4 cases
			if (current_node->pNext == NULL && current_node->pPrev == NULL) //if the song is the only one song
			{
				l->pHead = NULL;
			}
			else if (current_node->pPrev == NULL) //the song is at front
			{
				l->pHead = current_node->pNext;
				current_node->pNext->pPrev = NULL;
			}
			else if (current_node->pNext == NULL) //the song is at end
			{
				current_node->pPrev->pNext = NULL;
			}
			else //the song is neither at front or at end
			{
				current_node->pPrev->pNext = current_node->pNext;
				current_node->pNext->pPrev = current_node->pPrev;
			}
			//free the node
			current_node->pNext = NULL;
			current_node->pPrev = NULL;
			free(current_node);
		}
	}
}

/********************************************************************************
* Function: shuffle()															*
* Date Created: 06/26/2017													    *
* Description: This function plays all songs of the list randomly.				*
* Input parameters:	a list (List)												*
* Returns: none																	*
* Preconditions: print_all_records() and play_a_song() are defined.				*
* Postconditions: Each song of the list is displayed at randomly order.			*
********************************************************************************/
void shuffle(List l)
{
	int num_songs = 0; //count how many songs there are
	int r = 0;
	List shuffled_list = { NULL };
	Node *cur;

	//print out the orginal order
	puts("Order of songs in the list: ");
	print_all_records(l, &num_songs); //num_songs == 9
	puts("");

	while (l.pHead != NULL)
	{
		cur = l.pHead;
		//Get a random node from the current list
		r = rand() % num_songs; // r == 0 to 8
		for (int i = 0; i < r; i++)
		{
			cur = cur->pNext;
		}
		//remove the node out of the list: 4 cases
		if (cur->pNext == NULL && cur->pPrev == NULL) //if the song is the only one song
		{
			l.pHead = NULL;
		}
		else if (cur->pPrev == NULL) //the song is at front
		{
			l.pHead = cur->pNext;
			cur->pNext->pPrev = NULL;
		}
		else if (cur->pNext == NULL) //the song is at end
		{
			cur->pPrev->pNext = NULL;
		}
		else //the song is neither at front or at end
		{
			cur->pPrev->pNext = cur->pNext;
			cur->pNext->pPrev = cur->pPrev;
		}
		//insert this node at front of the shuffled list
		if (shuffled_list.pHead == NULL) //insert front to an empty list
		{
			shuffled_list.pHead = cur;
			cur->pNext = NULL;
		}
		else
		{
			cur->pNext = shuffled_list.pHead;
			shuffled_list.pHead->pPrev = cur;
			shuffled_list.pHead = cur;
		}
		cur->pPrev = NULL;
		//update statements
		num_songs--;
	}

	puts("\n\nThis is the shuffled list:");
	print_all_records(shuffled_list, &r);
	//play the suffled order
	if (shuffled_list.pHead != NULL)
	{
		puts("Please press any key to play...");
		getch();
		system("@cls||clear"); // clear screen
		cur = shuffled_list.pHead;
		while (cur != NULL)
		{
			play_a_song(cur);
			//update statement
			cur = cur->pNext;
		}
		puts("All songs have been played.");
	}
}

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
	Node *pCur, List *l)
{
	//take pMem out
	if (pMem->pNext == NULL) //the song is at end
	{
		pCur->pNext = NULL;
	}
	else //the song is neither at front or at end
	{
		pCur->pNext = pMem->pNext;
		pMem->pNext->pPrev = pCur;
	}
	//insert pMem at front of pPosition
	if (l->pHead == pPosition) //inserting at front of the list
	{
		pMem->pNext = pPosition;
		pMem->pPrev = NULL;
		pPosition->pPrev = pMem;
		l->pHead = pMem;
	}
	else //insert not at front of the list
	{
		pMem->pPrev = pPosition->pPrev;
		pMem->pNext = pPosition;
		pPosition->pPrev->pNext = pMem;
		pPosition->pPrev = pMem;
	}
}

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
void insertion_sort(List *l)
{
	int method = 0;
	Node *pCur = l->pHead, *pMem = l->pHead,
		*pPosition = l->pHead;

	//if the list contains no song or 1 song -> list remains order, else:
	if (l->pHead != NULL && l->pHead->pNext != NULL)
	{
		//promt user for method of sorting
		do
		{
			printf("1.    Sort based on artist (A-Z)\n\
2.    Sort based on album title(A - Z)\n\
3.    Sort based on rating(1 - 5)\n\
4.    Sort based on times played(largest - smallest)\n\
5.    Sort based on duration(largest - smallest)\n\n\
Please enter number of the sorting method: ");
			scanf("%d", &method);
		} while (method <= 0 || method >= 6);

		// Sort based on artist (A-Z)
		if (method == 1)
		{
			while (pCur->pNext != NULL)
			{
				pPosition = l->pHead; //reset pPosition
				pMem = pCur->pNext; //take the next node
				if (strcmp(pCur->info.artist, pMem->info.artist) > 0)
				{
					while (strcmp(pPosition->info.artist, pMem->info.artist) < 0 &&
						pPosition != pCur) //find the right position for pMem
					{
						pPosition = pPosition->pNext;
					}
					move_node_insertion_sorting(pPosition, pMem, pCur, l);
				}
				//update statement
				else
					pCur = pCur->pNext;
			}
		}//end of method 1

		 // Sort based on album title(A - Z)
		else if (method == 2)
		{
			while (pCur->pNext != NULL)
			{
				pPosition = l->pHead; //reset pPosition
				pMem = pCur->pNext; //take the next node
				if (strcmp(pCur->info.album_title, pMem->info.album_title) > 0)
				{
					while (strcmp(pPosition->info.album_title, pMem->info.album_title) < 0 &&
						pPosition != pCur) //find the right position for pMem
					{
						pPosition = pPosition->pNext;
					}
					move_node_insertion_sorting(pPosition, pMem, pCur, l);
				}
				//update statement
				else
					pCur = pCur->pNext;
			}
		}//end of method 2

		 // Sort based on rating(1 - 5)
		else if (method == 3)
		{
			while (pCur->pNext != NULL)
			{
				pPosition = l->pHead; //reset pPosition
				pMem = pCur->pNext; //take the next node
				if (pCur->info.rating > pMem->info.rating)
				{
					while (pPosition->info.rating < pMem->info.rating &&
						pPosition != pCur) //find the right position for pMem
					{
						pPosition = pPosition->pNext;
					}
					move_node_insertion_sorting(pPosition, pMem, pCur, l);
				}
				//update statement
				else
					pCur = pCur->pNext;
			}
		}//end of method 3

		 // Sort based on times played(largest - smallest)
		else if (method == 4)
		{
			while (pCur->pNext != NULL)
			{
				pPosition = l->pHead; //reset pPosition
				pMem = pCur->pNext; //take the next node
				if (pCur->info.times_played > pMem->info.times_played)
				{
					while (pPosition->info.times_played < pMem->info.times_played &&
						pPosition != pCur) //find the right position for pMem
					{
						pPosition = pPosition->pNext;
					}
					move_node_insertion_sorting(pPosition, pMem, pCur, l);
				}
				//update statement
				else
					pCur = pCur->pNext;
			}
		}//end of method 4

		 // Sort based on duration(largest - smallest)
		else
		{
			while (pCur->pNext != NULL)
			{
				pPosition = l->pHead; //reset pPosition
				pMem = pCur->pNext; //take the next node
				if ((pCur->info.dur.min * 60 + pCur->info.dur.sec) >
					(pMem->info.dur.min * 60 + pMem->info.dur.sec))
				{
					while ((pPosition->info.dur.min * 60 + pPosition->info.dur.sec) <
						(pMem->info.dur.min * 60 + pMem->info.dur.sec) &&
						pPosition != pCur) //find the right position for pMem
					{
						pPosition = pPosition->pNext;
					}
					move_node_insertion_sorting(pPosition, pMem, pCur, l);
				}
				//update statement
				else
					pCur = pCur->pNext;
			}
		}//end of method 5
	}
	puts("Sorting completed.");
}

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
void selection_sort(List *l)
{
	int method = 0;
	Node *pCur = l->pHead, *pMax = l->pHead,
		*pPosition = l->pHead;

	//if the list contains no song or 1 song -> list remains order, else:
	if (l->pHead != NULL && l->pHead->pNext != NULL)
	{
		//promt user for method of sorting
		do
		{
			printf("1.    Sort based on artist (A-Z)\n\
2.    Sort based on album title(A - Z)\n\
3.    Sort based on rating(1 - 5)\n\
4.    Sort based on times played(largest - smallest)\n\
5.    Sort based on duration(largest - smallest)\n\n\
Please enter number of the sorting method: ");
			scanf("%d", &method);
		} while (method <= 0 || method >= 6);

		// Sort based on artist (A-Z)
		if (method == 1)
		{
			while (pCur != NULL)
			{
				pPosition = pCur;
				//find the maximum value node from pCur to end
				pMax = pCur; //reset pMax
				while (pPosition != NULL)
				{
					if (strcmp(pPosition->info.artist, pMax->info.artist) > 0)
						pMax = pPosition;
					pPosition = pPosition->pNext;
				}
				if (pMax == pCur)
					pCur = pCur->pNext;
				//remove the node out of the list
				if (pMax->pPrev == NULL) //the song is at front
				{}
				else if (pMax->pNext == NULL) //the song is at end
				{
					pMax->pPrev->pNext = NULL;
				}
				else //the song is neither at front or at end
				{
					pMax->pPrev->pNext = pMax->pNext;
					pMax->pNext->pPrev = pMax->pPrev;
				}
				//insert this node at front of the list
				pMax->pNext = l->pHead;
				l->pHead->pPrev = pMax;
				l->pHead = pMax;
				pMax->pPrev = NULL;
			}
		}//end of method 1

		// Sort based on album title(A - Z)
		else if (method == 2)
		{
			while (pCur != NULL)
			{
				pPosition = pCur;
				//find the maximum value node from pCur to end
				pMax = pCur; //reset pMax
				while (pPosition != NULL)
				{
					if (strcmp(pPosition->info.album_title, pMax->info.album_title) > 0)
						pMax = pPosition;
					pPosition = pPosition->pNext;
				}
				if (pMax == pCur)
					pCur = pCur->pNext;
				//remove the node out of the list
				if (pMax->pPrev == NULL) //the song is at front
				{
				}
				else if (pMax->pNext == NULL) //the song is at end
				{
					pMax->pPrev->pNext = NULL;
				}
				else //the song is neither at front or at end
				{
					pMax->pPrev->pNext = pMax->pNext;
					pMax->pNext->pPrev = pMax->pPrev;
				}
				//insert this node at front of the list
				pMax->pNext = l->pHead;
				l->pHead->pPrev = pMax;
				l->pHead = pMax;
				pMax->pPrev = NULL;
			}
		}//end of method 2

		// Sort based on rating(1 - 5)
		else if (method == 3)
		{
			while (pCur != NULL)
			{
				pPosition = pCur;
				//find the maximum value node from pCur to end
				pMax = pCur; //reset pMax
				while (pPosition != NULL)
				{
					if (pPosition->info.rating > pMax->info.rating)
						pMax = pPosition;
					pPosition = pPosition->pNext;
				}
				if (pMax == pCur)
					pCur = pCur->pNext;
				//remove the node out of the list
				if (pMax->pPrev == NULL) //the song is at front
				{
				}
				else if (pMax->pNext == NULL) //the song is at end
				{
					pMax->pPrev->pNext = NULL;
				}
				else //the song is neither at front or at end
				{
					pMax->pPrev->pNext = pMax->pNext;
					pMax->pNext->pPrev = pMax->pPrev;
				}
				//insert this node at front of the list
				pMax->pNext = l->pHead;
				l->pHead->pPrev = pMax;
				l->pHead = pMax;
				pMax->pPrev = NULL;
			}
		}//end of method 3

		 // Sort based on times played(largest - smallest)
		else if (method == 4)
		{
			while (pCur != NULL)
			{
				pPosition = pCur;
				//find the maximum value node from pCur to end
				pMax = pCur; //reset pMax
				while (pPosition != NULL)
				{
					if (pPosition->info.times_played > pMax->info.times_played)
						pMax = pPosition;
					pPosition = pPosition->pNext;
				}
				if (pMax == pCur)
					pCur = pCur->pNext;
				//remove the node out of the list
				if (pMax->pPrev == NULL) //the song is at front
				{
				}
				else if (pMax->pNext == NULL) //the song is at end
				{
					pMax->pPrev->pNext = NULL;
				}
				else //the song is neither at front or at end
				{
					pMax->pPrev->pNext = pMax->pNext;
					pMax->pNext->pPrev = pMax->pPrev;
				}
				//insert this node at front of the list
				pMax->pNext = l->pHead;
				l->pHead->pPrev = pMax;
				l->pHead = pMax;
				pMax->pPrev = NULL;
			}
		}//end of method 4

		 // Sort based on duration(largest - smallest)
		else
		{
			while (pCur != NULL)
			{
				pPosition = pCur;
				//find the maximum value node from pCur to end
				pMax = pCur; //reset pMax
				while (pPosition != NULL)
				{
					if ((pPosition->info.dur.min * 60 + pPosition->info.dur.sec) >
						(pMax->info.dur.min * 60 + pMax->info.dur.sec))
						pMax = pPosition;
					pPosition = pPosition->pNext;
				}
				if (pMax == pCur)
					pCur = pCur->pNext;
				//remove the node out of the list
				if (pMax->pPrev == NULL) //the song is at front
				{
				}
				else if (pMax->pNext == NULL) //the song is at end
				{
					pMax->pPrev->pNext = NULL;
				}
				else //the song is neither at front or at end
				{
					pMax->pPrev->pNext = pMax->pNext;
					pMax->pNext->pPrev = pMax->pPrev;
				}
				//insert this node at front of the list
				pMax->pNext = l->pHead;
				l->pHead->pPrev = pMax;
				l->pHead = pMax;
				pMax->pPrev = NULL;
			}
		}//end of method 5
	}
	puts("Sorting completed."); 
}

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
void bubble_sort(List *l)
{
	int method = 0;
	Node *pTail = l->pHead, *pCur = l->pHead;

	//if the list contains no song or 1 song -> list remains order, else:
	if (l->pHead != NULL && l->pHead->pNext != NULL)
	{
		//find the end node
		while (pTail->pPrev != NULL)
		{
			pTail = pTail->pNext;
		}
		//promt user for method of sorting
		do
		{
			printf("1.    Sort based on artist (A-Z)\n\
2.    Sort based on album title(A - Z)\n\
3.    Sort based on rating(1 - 5)\n\
4.    Sort based on times played(largest - smallest)\n\
5.    Sort based on duration(largest - smallest)\n\n\
Please enter number of the sorting method: ");
			scanf("%d", &method);
		} while (method <= 0 || method >= 6);

		// Sort based on artist (A-Z)
		if (method == 1)
		{
			while (pTail != l->pHead)
			{
				while (pCur != pTail)
				{
					if(strcmp(pCur->info.artist, pCur->pNext->info.artist) > 0) //swap
					{

					}
				}
				//update pTail
				pTail = pTail->pPrev;
			}
		}
	}
}

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
void run_program()
{
	//variable declaration
	int option = 0;
	List album = { NULL };

	srand(time(NULL));   // for rand()

	do
	{
		//display menu and prompt user for an option
		get_option(&option);
		switch (option)
		{
		case 1:
			load("musicPlayList.csv", &album);
			break;
		case 2:
			store("musicPlayList.csv", album);
			break;
		case 3:
			display(album);
			break;
		case 4:
			insert(&album);
			break;
		case 5:
			delete(&album);
			break;
		case 6:
			edit(&album);
			break;
		case 7:
			//insertion_sort(&album);
			selection_sort(&album);
			break;
		case 8:
			rate(&album);
			break;
		case 9:
			play(album);
			break;
		case 10:
			shuffle(album);
			break;
		case 11:
			store("musicPlayList.csv", album);
			break;
		}

		if (option != 11)
		{
			puts("Please press any key to continue...");
			getch();
			system("@cls||clear"); // clear screen
		}
	} while (option < 11); // run program until "exit" is selected
}
