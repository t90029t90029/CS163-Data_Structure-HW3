//Shang Chun, Lin : CS163 program#3

//the purpose of this file is to build a hash table and store the data from the external file. Also it can modify the data by the program and let the user to search the data quickly.

#include "song.h"

using namespace std;

song::song()
{
	artist = NULL;
	title = NULL;
	album = NULL;
	for(int i=0;i<3;++i)
	{
		key[i] = NULL;
	}
	descrip = NULL;
}

song::~song()
{
	if(artist)
	{
		delete []artist;
	}
	if(title)
	{
		delete []title;
	}
	if(album)
	{
		delete []album;
	}
	if(key[0])
	{
		for(int i=0;i<3;++i)
		{
			delete []key[i];
			key[i] = NULL;
		}
	}
	if(descrip)
	{
		delete []descrip;
	}
	artist = NULL;
	title = NULL;
	album = NULL;
	descrip = NULL;
}

int song::add_a_song(hold_a_song & to_add)
{
	if(!to_add.artist)
	{
		return 0;
	}
	artist = new char[strlen(to_add.artist)+1];
	strcpy(artist,to_add.artist);
	title = new char[strlen(to_add.title)+1];
	strcpy(title,to_add.title);
	album = new char[strlen(to_add.album)+1];
	strcpy(album,to_add.album);
	for(int i=0;i<3;++i)
	{
		key[i] = new char[strlen(to_add.key[i])+1];
		strcpy(key[i],to_add.key[i]);
	}
	descrip = new char[strlen(to_add.descrip)+1];
	strcpy(descrip,to_add.descrip);

	return 1;
}

int song::search_a_song(hold_a_song & hold)
{
	if(!hold.key[0])
	{
		return 0;
	}
	int success = 0;
	int i = 0;
	while(i<3)
	{
		if(strcmp(hold.key[0],key[i]) == 0)
		{
			hold.artist = new char[strlen(artist)+1];
			strcpy(hold.artist,artist);
			hold.title = new char[strlen(title)+1];
			strcpy(hold.title,title);
			hold.album = new char[strlen(album)+1];
			strcpy(hold.album,album);
			for(int i=0;i<3;++i)
			{
				hold.key[i] = new char[strlen(key[i])+1];
				strcpy(hold.key[i],key[i]);
			}
			hold.descrip = new char[strlen(descrip)+1];
			strcpy(hold.descrip,descrip);
			success = 1;
			i = 3;
		}
		++i;
	}
	return success;
}

int song::remove_a_song(char * artist_to_remove)
{
	if(!artist_to_remove)
	{
		return 0;
	}
	if(strcmp(artist,artist_to_remove) == 0)
	{
		delete []artist;
		delete []title;
		delete []album;
		for(int i=0;i<3;++i)
		{
			delete []key[i];
			key[i] = NULL;
		}
		delete []descrip;
		artist = NULL;
		title = NULL;
		album = NULL;
		descrip = NULL;

		return 1;
	}
	return 0;
}

int song::display()
{
	if(!artist || !title || !album || !key[0] || !descrip)
	{
		return 0;
	}
	cout<<"Artist : "<<artist<<endl;
	cout<<"The song : "<<title<<endl;
	cout<<"The album : "<<album<<endl;
	for(int i=0;i<3;++i)
	{
		cout<<"The key word : "<<key[i]<<endl;
	}
	cout<<"The description : "<<descrip<<endl;
	return 1;
}

table::table(int size)
{
	hash_table = new node * [size];
	for(int i=0;i<size;++i)
	{
		hash_table[i] = NULL;
	}
	table_size = size;
}

table::~table()
{
	int size = table_size;
	for(int i=0;i<size;++i)
	{
		while(hash_table[i])
		{
			node * temp = hash_table[i]->next;
			hash_table[i]->data.~song();
			delete hash_table[i];
			hash_table[i] = temp;
		}
	}
	delete []hash_table;
	table_size = 0;
}

int table::read_in(hold_a_song & to_add)
{
	int count = 0;
	ifstream file_in;
	file_in.open(file_name);

	if(file_in)
	{
		file_in.get(to_add.artist,SIZE,'|');
		file_in.ignore(100,'|');
		while(!file_in.eof())
		{
			file_in.get(to_add.title,SIZE,'|');
			file_in.ignore(100,'|');

			file_in.get(to_add.album,SIZE,'|');
			file_in.ignore(100,'|');
			
			for(int i=0;i<3;++i)
			{	
				file_in.get(to_add.key[i],SIZE,'|');
				file_in.ignore(100,'|');
			}

			file_in.get(to_add.descrip,SIZE,'\n');
			file_in.ignore(300,'\n');

			if(add(to_add))
			{
				++count;
			}

			if(to_add.artist)			//reset
			{
				delete []to_add.artist;
				to_add.artist = NULL;
			}
			if(to_add.title)
			{
				delete []to_add.title;
				to_add.title = NULL;
			}
			if(to_add.album)
			{
				delete []to_add.album;
				to_add.album = NULL;
			}
			for(int i=0;i<3;++i)
			{
				if(to_add.key[i])
				{
					delete []to_add.key[i];
					to_add.key[i] = NULL;
				}
			}
			if(to_add.descrip)
			{
				delete []to_add.descrip;
				to_add.descrip = NULL;
			}

			if(!file_in.eof())
			{
				to_add.artist = new char[SIZE];
				to_add.title = new char[SIZE];
				to_add.album = new char[SIZE];
				for(int i=0;i<3;++i)
				{
					to_add.key[i] = new char[SIZE];
				}
				to_add.descrip = new char[SIZE];
				file_in.get(to_add.artist,SIZE,'|');
				file_in.ignore(100,'|');
			}
		}
		file_in.close();
		file_in.clear();
	}
	return count;
}

int table::hash_function(char * key)
{
	if(!key)
	{
		return 0;
	}
	int i = strlen(key);
	int sum = 0;
	for(int k=0;k<i;++k)
	{
		sum += key[k] * key[k] + k * k;
	}
	sum = sum % table_size;
	if(sum < 0)
	{
		sum = -sum;
	}
	return sum;
}

int table::add(hold_a_song & to_add)
{
	if(!to_add.artist || !to_add.title || !to_add.album || !to_add.key[0] || !to_add.descrip)
	{
		return 0;
	}
	node * temp = new node;
	if(!temp->data.add_a_song(to_add))
	{
		delete temp;
		return 0;
	}
	int index = hash_function(to_add.key[0]);
	temp->next = hash_table[index];
	hash_table[index] = temp;

	return 1;
}

int table::search(hold_a_song & hold)
{
	if(!hold.key[0])
	{
		return 0;
	}
	int index = hash_function(hold.key[0]);
	if(!hash_table[index])
	{
		return 0;
	}
	return search(hash_table[index],hold);
}

int table::search(node*ptr,hold_a_song & hold)
{
	if(!ptr)
	{
		return 0;
	}
	if(ptr->data.search_a_song(hold))
	{
		return 1;
	}
	return search(ptr->next,hold);
}

int table::remove(char * artist)
{
	if(!artist)
	{
		return 0;
	}
	if(!hash_table)
	{
		return 0;
	}
	int i = 0;
	int count = 0;
	while(i<table_size)
	{
		if(hash_table[i])
		{
			count += remove(hash_table[i],artist);
		}
		++i;
	}
	return count;
}
int table::remove(node * & ptr,char * artist)
{
	if(!ptr)
	{
		return 0;
	}
	int count = 0;
	if(ptr->data.remove_a_song(artist))
	{
		node * temp = ptr->next;
		ptr->next = NULL;
		delete ptr;
		ptr = temp;
		++count;
		if(!ptr)
		{
			return 0;
		}
	}
	count += remove(ptr->next,artist);
	return count;
}

int table::display_match(char * key)
{
	if(!key)
	{
		return 0;
	}
	int index = hash_function(key);
	if(!hash_table[index])
	{
		return 0;
	}
	return display_match(hash_table[index],key);
}
int table::display_match(node * ptr,char * key)
{
	if(!ptr)
	{
		return 0;
	}
	int count = 0;
	count += ptr->data.display();
	return display_match(ptr->next,key) + count;
}

int table::display_all()
{
	if(!hash_table)
	{
		return 0;
	}
	int i = 0;
	int count = 0;
	while(i<table_size)
	{
		count += display_all(hash_table[i]);
		++i;
	}
	return count;
}

int table::display_all(node * ptr)
{
	if(!ptr)
	{
		return 0;
	}
	int count = 0;
	count += ptr->data.display();
	return display_all(ptr->next);
}
