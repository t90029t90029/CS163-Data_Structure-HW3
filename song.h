//Shang Chun, Lin : CS163 program#3

//the purpose of this file is to build a hash table and store the data from the external file. Also it can modify the data by the program and let the user to search the data quickly.

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

const char file_name[] = "song.txt";
const int SIZE = 201;

struct hold_a_song
{
	char * artist;
	char * title;	//title of the song
	char * album;	//title of the album
	char * key[3];
	char * descrip; //description
};

class song
{
	public:
		song();
		~song();
		int add_a_song(hold_a_song & to_add);
		int search_a_song(hold_a_song & hold);
		int remove_a_song(char * artist_to_remove);
		int display();
	private:
		char * artist;
		char * title;	//title of the song
		char * album;	//title of the album
		char * key[3];
		char * descrip; //description
};

struct node
{
	song data;
	node * next;
};

class table
{
	public:
		table(int size);
		~table();
		int read_in(hold_a_song & to_add);
		int hash_function(char * key);
		int add(hold_a_song & to_add);
		int search(hold_a_song & hold);
		int remove(char * artist);
		int display_match(char * key);
		int display_all();
	
	private:
		int search(node*ptr,hold_a_song & hold);
		int remove(node * & ptr,char * artist);
		int display_match(node * ptr,char * key);
		int display_all(node * ptr);
		node ** hash_table;
		int table_size;
};
