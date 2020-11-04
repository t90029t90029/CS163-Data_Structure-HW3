//Shang-Chun,Lin  CS163 program#3 assignment
#include "song.h"

using namespace std;

//the purpose of this file is to test the structs and classes that I have declared in .h file (working as client program)

int main()
{
	table smaller(5);
	table bigger(37);

	hold_a_song hold;	//representing to_add or retrieve as the argument what we have searched
	hold.artist = NULL;
	hold.title = NULL;
	hold.album = NULL;
	for(int i=0;i<3;++i)
	{
		hold.key[i] = NULL;
	}
	hold.descrip = NULL;
//--------this part is to allocate memories to a struct and make use of it to catch the data from the external file-------------------
	hold.artist = new char[SIZE];
	hold.title = new char[SIZE];
	hold.album = new char[SIZE];
	for(int i=0;i<3;++i)
	{	
		hold.key[i] = new char[SIZE];
	}
	hold.descrip = new char[SIZE];

	cout<<"We have read in "<<smaller.read_in(hold)<<" data in the size 5 table."<<endl;
	cout<<"We have read in "<<bigger.read_in(hold)<<" data in the size 37 table."<<endl;

	hold.artist = NULL;
	hold.title = NULL;
	hold.album = NULL;
	for(int i=0;i<3;++i)
	{
		hold.key[i] = NULL;
	}
	hold.descrip = NULL;
//-------------------------------------------------------------------------------------------------------------------------------------

	int answer = 0;
	cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
	<<"1 for adding a new song                       , 2 for searching for a particular key word, "<<endl
	<<"3 for removing by the artist name in the table, 4 for displaying all matches by the key word, "<<endl
	<<"5 for displaying all data in the table,       , 6 for quitting the program."<<endl;
	cin>>answer;
	cin.ignore(100,'\n');

	while(answer != 6)
	{
		hold.artist = new char[SIZE];
		hold.title = new char[SIZE];
		hold.album = new char[SIZE];
		for(int i=0;i<3;++i)
		{
			hold.key[i] = new char[SIZE];
		}
		hold.descrip = new char[SIZE];

		if(answer == 1)
		{
			cout<<"Please type in the artist name."<<endl;
			cin.get(hold.artist,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in the name of the song."<<endl;
			cin.get(hold.title,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in the name of the album."<<endl;
			cin.get(hold.album,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in three key words of the song."<<endl;
			for(int i=0;i<3;++i)
			{
				cin.get(hold.key[i],SIZE,'\n');
				cin.ignore(100,'\n');
			}

			cout<<"Please type in your description of the song."<<endl;
			cin.get(hold.descrip,SIZE,'\n');
			cin.ignore(300,'\n');

			cout<<"We have added "<<smaller.add(hold)<<" data in the size 5 table."<<endl;		//input the data from static to dynamic
			cout<<"We have added "<<bigger.add(hold)<<" data in the size 37 table."<<endl;
			
			cout<<"There are "<<smaller.display_all()<<" data in the size 5 table."<<endl;
			cout<<"There are "<<bigger.display_all()<<" data in the size 37 table."<<endl;
		}

		if(answer == 2)
		{
			cout<<"Please type in three key words of the song for searching."<<endl;
			cin.get(hold.key[0],SIZE,'\n');
			cin.ignore(100,'\n');

			if(smaller.search(hold))
			{
				cout<<"We find it in the smaller table !!"<<endl;

				cout<<"The information we have searched for the key is : "<<endl;
				cout<<"Artist : "<<hold.artist<<endl;
				cout<<"The song : "<<hold.title<<endl;
				cout<<"The album : "<<hold.album<<endl;
				for(int i=0;i<3;++i)
				{
					cout<<"The key word : "<<hold.key[i]<<endl;
				}
				cout<<"The description : "<<hold.descrip<<endl<<endl;
			}

			if(hold.artist)			//reset
			{
				delete []hold.artist;
				hold.artist = NULL;
			}
			if(hold.title)
			{
				delete []hold.title;
				hold.title = NULL;
			}
			if(hold.album)
			{
				delete []hold.album;
				hold.album = NULL;
			}
			for(int i=0;i<3;++i)
			{
				if(hold.key[i])
				{
					delete []hold.key[i];
					hold.key[i] = NULL;
				}
			}
			if(hold.descrip)
			{
				delete []hold.descrip;
				hold.descrip = NULL;
			}

			if(bigger.search(hold))
			{
				cout<<"We find it in the bigger table !!"<<endl;

				cout<<"The information we have searched for the key is : "<<endl;
				cout<<"Artist : "<<hold.artist<<endl;
				cout<<"The song : "<<hold.title<<endl;
				cout<<"The album : "<<hold.album<<endl;
				for(int i=0;i<3;++i)
				{
					cout<<"The key word : "<<hold.key[i]<<endl;
				}
				cout<<"The description : "<<hold.descrip<<endl<<endl;
			}
				
		}

		if(answer == 3)
		{
			cout<<"Please type in an artist name for removing the related data in the table."<<endl;
			cin.get(hold.artist,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"We have removed "<<smaller.remove(hold.artist)<<" data in the size 5 table."<<endl;
			cout<<"We have removed "<<bigger.remove(hold.artist)<<" data in the size 37 table."<<endl;

			cout<<"There are "<<smaller.display_all()<<" data in the size 5 table."<<endl;
			cout<<"There are "<<bigger.display_all()<<" data in the size 37 table."<<endl;
		}

		if(answer == 4)
		{
			cout<<"Please type in a key word to display all matched in the table."<<endl;
			cin.get(hold.key[0],SIZE,'\n');
			cin.ignore(100,'\n');
			
			cout<<"There are "<<smaller.display_match(hold.key[0])<<" matches in the size 5 table."<<endl;
			cout<<"There are "<<bigger.display_match(hold.key[0])<<" matches in the size 37 table."<<endl;
		}
		if(answer == 5)
		{
			cout<<"The smaller table with size 5 : "<<endl;
			cout<<"There are "<<smaller.display_all()<<" data in the size 5 table."<<endl;

			cout<<"The bigger table with size 37 : "<<endl;
			cout<<"There are "<<bigger.display_all()<<" data in the size 37 table."<<endl;
		}
		cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
		<<"1 for adding a new song                       , 2 for searching for a particular key word, "<<endl
		<<"3 for removing by the artist name in the table, 4 for displaying all matches by the key word, "<<endl
		<<"5 for displaying all data in the table,       , 6 for quitting the program."<<endl;
		cin>>answer;
		cin.ignore(100,'\n');

		if(hold.artist)			//reset
		{
			delete []hold.artist;
			hold.artist = NULL;
		}
		if(hold.title)
		{
			delete []hold.title;
			hold.title = NULL;
		}
		if(hold.album)
		{
			delete []hold.album;
			hold.album = NULL;
		}
		for(int i=0;i<3;++i)
		{
			if(hold.key[i])
			{
				delete []hold.key[i];
				hold.key[i] = NULL;
			}
		}
		if(hold.descrip)
		{
			delete []hold.descrip;
			hold.descrip = NULL;
		}
	}
	return 0;
}
