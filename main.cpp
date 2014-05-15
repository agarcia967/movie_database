/* Final Project (Movie Database)
   File Name:          main.cpp
   Programmer:         Anthony Garcia
   Date Last Modified: May 13, 2014
*/
#include "Movie.h"
#include <iomanip>
#include <vector>
#include <fstream>

// 0 - NR // 1 - G // 2 - PG // 3 - PG-13 // 4 - R // 5 - UR //

//// Function Prototypes ////
bool fileExists(string filename);
void pressEnter();
bool readModule();
bool writeModule();
bool writeSettings();
void choiceListMaker(string label, string list[], int size);

void searchDatabase();

template<typename T>
bool linearSearch(vector<T> vect, string search_key);
template<typename T>
int singleSearch(vector<T> vect, string search_key);
void showMovies();
void modifyDatabase();
	bool addMovie();
	bool editMovie();
	bool deleteMovie();
void options();
	void loadDatabase();
	void saveDatabase();
	void importCSV();
void autoSave();
bool exit();

//// Global Variables ////
vector<DVD> DVDList;
vector<VHS> VHSList;
string gl_filename;
const char SETTINGS_FILE[] = "settings.dat";
bool changesMade = false;

int main()
{
	if(fileExists(SETTINGS_FILE))
	{
		fstream readSFile(SETTINGS_FILE, ios::in);
		readSFile >> gl_filename;
		readSFile.close();
		if(fileExists(gl_filename))
			readModule();
		else
		{
			cout << "Settings file contents in error. Settings file removed." <<endl;
			gl_filename = "";
			remove(SETTINGS_FILE);
		}
	}
	while(true)
	{
		const int SIZE = 6;
		string list[] = {"Search database","Show all movies","Modify database","Options","Save & Exit","Exit without Saving"};
		choiceListMaker("MAIN MENU",list,SIZE);
		string input;
		getline(cin,input);
		const char one = '1';
		switch(input[0])
		{
			case '1': //Search a database
				searchDatabase();
				break;
			case '2': //Show all movies
				showMovies();
				break;
			case '3': //Modify database -->
				modifyDatabase();
				break;
			case '4': //Database options -->
				options();
				break;
			case '5': //Exit & Save
				autoSave();
				return 0;
			case '6': //Exit
				if(exit())
					return 0;
				else
					break;
			default:
				cout << "Enter a value in range 1-" << SIZE << "." <<endl;
		}
	}
	return 0;
}

bool fileExists(string filename)
{
	ifstream ifile(filename.c_str());
	if(ifile)
	{
		ifile.close();
		return true;
	}
	else
	{
		ifile.close();
		return false;
	}
}
void pressEnter()
{
	cout << "Press ENTER to continue." <<endl;
	string i;
	getline(cin,i);
}
bool readModule()
{
	cout << "Reading file '" << gl_filename << "'. Please wait... ";
	if(fileExists(gl_filename))
	{
		fstream inFile(gl_filename.c_str(), ios::in | ios::binary);
		if(!inFile.good())
		{
			cout << "File read error." <<endl;
			pressEnter();
			return false;
		}
		inFile.read(reinterpret_cast<char *>(&DVDList),sizeof(DVDList));
		inFile.read(reinterpret_cast<char *>(&VHSList),sizeof(VHSList));
		inFile.close();
		cout << "Complete." <<endl;
		return true;
	}
	else
	{
		cout << "File not found." <<endl;
		pressEnter();
		return false;
	}
}
bool writeModule()
{
	cout << "Writing file '" << gl_filename << "'. Please wait... ";
	fstream outFile(gl_filename.c_str(), ios::out | ios::binary);
	if(!outFile.good())
	{
		cout << "File write error. File not written." <<endl;
		pressEnter();
		return false;
	}
	outFile.write(reinterpret_cast<char *>(&DVDList),sizeof(DVDList));
	outFile.write(reinterpret_cast<char *>(&VHSList),sizeof(VHSList));
	outFile.close();
	cout << "Complete." <<endl;
	changesMade = false;
	return true;
}
bool writeSettings()
{
	fstream settingsFile(SETTINGS_FILE, ios::out);
	if(!settingsFile.good())
	{
		cout << "File write error. File not written." <<endl;
		pressEnter();
		return false;
	}
	settingsFile << gl_filename;
	settingsFile.close();
	return true;
}

void choiceListMaker(string label, string list[], int size)
{
	cout <<endl << label <<endl;
	if(gl_filename=="")
		cout << "**No database selected. Go to Options > Load Database.**";
	else
		cout << "Database selected: " << gl_filename;
	if(changesMade)
		cout << "[Changes Not Saved]";
	cout <<endl;
	for(int i = 0; i < size; i++)
		cout << " " << i+1 << " -" << list[i] <<endl;
	cout << "\nPlease make a selection." <<endl << "> ";
}
bool exit()
{
	string input;
	if(changesMade)
	{
		cout << "Do you want to save changes? (s/d/c) ";
		while(true)
		{
			getline(cin,input);
			switch(tolower(input[0]))
			{
				case 's':
					autoSave();
					return true;
				case 'd':
					return true;
				case 'c':
					return false;
				default:
					cout << "Please enter 's' to save changes, 'd' for don't save, or 'c' to return to the main menu." <<endl;
			}
		}
	}
	else
		return true;
}

void searchDatabase()
{
	cout <<endl << "SEARCH DATABASE" <<endl;
	if(DVDList.empty() && VHSList.empty())
	{
		cout << "No database contents." <<endl;
		pressEnter();
		return;
	}
	cout << "\nEnter search terms: ";
	string input;
	getline(cin,input);
	if(!linearSearch(DVDList, input))
		cout << "\nNo matches found in the DVD List.\n" <<endl;
	if(!linearSearch(VHSList, input))
		cout << "\nNo matches found in the VHS List." <<endl;
	cout <<endl;
	pressEnter();
}

template<typename T>
bool linearSearch(vector<T> vect, string search_key)
{
    int flag = 0;
    for(int j = 0; j < vect.size(); j++)
    {
        if (vect[j].matchKey(search_key))
        {
			cout << vect[j].toString() << " - ";
			string z = vect[j].getSortTitle();
			for(int i = 0; i < 3; i++)
				cout << z[i];
			cout <<endl;
			flag += 1;
        }
    }
    return flag;
}
void showMovies()
{
	cout <<endl;
	cout << "SHOW ALL MOVIES" <<endl;
	if(DVDList.empty() && VHSList.empty())
	{
		cout << "No database contents." <<endl;
		pressEnter();
		return;
	}
	cout <<endl << "DVD List" << "--------" <<endl;
	for(int i = 0; i < DVDList.size(); i++)
	{
		cout <<left  <<setw(60) << DVDList[i].getTitle()
			 <<right <<setw(5)  << DVDList[i].getYear()
			 <<right <<setw(6)  << DVDList[i].getRating();
	}
	cout <<endl << "VHS List" << "--------" <<endl;
	for(int i = 0; i < VHSList.size(); i++)
	{
		cout <<left  <<setw(60) << VHSList[i].getTitle()
			 <<right <<setw(5)  << VHSList[i].getYear()
			 <<right <<setw(6)  << VHSList[i].getRating();
	}
}

/////////////// Modify Database ///////////////
void modifyDatabase()
{
	while(true)
	{
		const int SIZE = 3;
		string list[] = {"Add a Movie","Delete a Movie","Back to MAIN MENU"};
		choiceListMaker("MODIFY DATABASE",list,SIZE);
		string input;
		getline(cin,input);
		switch(input[0])
		{
			case '1': //Add a Movie
				changesMade = addMovie();
				break;
			case '2': //Delete a Movie
				changesMade = deleteMovie();
				break;
			case '3': //Back to Main Menu
				return;
			default:
				cout << "Enter a value in range 1-" << SIZE << "." <<endl;
		}
	}
}
bool addMovie()
{
	string input;
	DVD* tempMovie;
	string tempTitle;
	int tempYear;
	Rating tempRating;
	
	cout << "Enter movie title: ";
	getline(cin,tempTitle);
	
	cout << "Enter movie release year: ";
	getline(cin,input);
	istringstream iss;
	iss.str(input);
	iss >> tempYear;
	
	while(true)
	{
		cout << "Enter movie rating: ";
		getline(cin,input);
		if(input[0]=='0' || input=="NR")
		{
			tempRating = NR;
			break;
		}
		else if(input[0]=='1' || input=="G")
		{
			tempRating = G;
			break;
		}
		else if(input[0]=='2' || input=="PG")
		{
			tempRating = PG;
			break;
		}
		else if(input[0]=='3' || input=="PG-13")
		{
			tempRating = PG_13;
			break;
		}
		else if(input[0]=='4' || input=="R")
		{
			tempRating = R;
			break;
		}
		else if(input[0]=='5' || input=="UR")
		{
			tempRating = UR;
			break;
		}
		else
			cout << "Please enter a rating (NR, G, ... R, UR) or an integer (0-5)" <<endl;
	}
	cout << "Would you like the movie in DVD List or VHS List? (d/v) ";
	bool location; //true = DVD / false = VHS
	bool done = false;
	while(!done)
	{
		getline(cin,input);
		switch(tolower(input[0]))
		{
			case 'd':
				location = true;
				done = true;
				break;
			case 'v':
				location = false;
				done = true;
				break;
			default:
				cout << "Please enter 'd' for DVD or 'v' for VHS." <<endl;
		}
	}
	if(location)
	{
		DVD tempDVD(tempTitle,tempYear,tempRating);
		DVDList.push_back(tempDVD);
	}
	else
	{
	VHS tempVHS(tempTitle,tempYear,tempRating);
		VHSList.push_back(tempVHS);
	}
}
template<typename T>
int singleSearch(vector<T> vect, string search_key)
{
    for(int j = 0; j < vect.size(); j++)
    {
        if (vect[j].matchKey(search_key))
        {
            return j;
        }
    }
    return -1;
}
bool deleteMovie()
{
	if(DVDList.empty() && VHSList.empty())
	{
		cout << "No database contents." <<endl;
		pressEnter();
		return false;
	}
	cout << "\nEnter search terms: ";
	string input;
	getline(cin,input);
	
	int index = singleSearch(DVDList, input);
	if(index==-1)
		cout << "\nNo matches found in the DVD List.\n" <<endl;
	else
	{
		cout << DVDList[index].toString();
		cout <<endl << "Are you sure you want to delete this movie? (y/n) ";
		bool done = false;
		while(!done)
		{
			getline(cin,input);
			switch(tolower(input[0]))
			{
				case 'y':
					DVDList.erase(DVDList.begin()+index);
					return true;
				case 'n':
					return false;
				default:
					cout << "Please enter 'y' for Yes or 'n' for No." <<endl;
			}
		}
	}
	
	index = singleSearch(VHSList, input);
	if(index==-1)
		cout << "\nNo matches found in the VHS List.\n" <<endl;
	else
	{
		cout << VHSList[index].toString();
		cout <<endl << "Are you sure you want to delete this movie? (y/n) ";
		bool done = false;
		while(!done)
		{
			getline(cin,input);
			switch(tolower(input[0]))
			{
				case 'y':
					VHSList.erase(VHSList.begin()+index);
					return true;
				case 'n':
					return false;
				default:
					cout << "Please enter 'y' for Yes or 'n' for No." <<endl;
			}
		}
	}
}

/////////////// Options ///////////////
void options()
{
	while(true)
	{
		const int SIZE = 4;
		string list[] = {"Load Database","Save Database","Clear Cache","Back to MAIN MENU"};
		choiceListMaker("DATABASE OPTIONS",list,SIZE);
		string input;
		getline(cin,input);
		switch(input[0])
		{
			case '1': //Load a Database
				loadDatabase();
				break;
			case '2': //Save Current Database
				saveDatabase();
				break;
			case '3': //Clear Cache
				gl_filename = "";
				DVDList.clear();
				VHSList.clear();
				remove(SETTINGS_FILE);
				cout << "Cache cleared." <<endl;
				break;
			case '4': //Back to Main Menu
				return;
			default:
				cout << "Enter a value in range 1-" << SIZE << "." <<endl;
		}
	}
}
void loadDatabase()
{
	cout <<endl << "LOAD DATABASE" <<endl;
	cout << "Enter filename to load: ";
	string input;
	getline(cin,input);
	gl_filename = input;
	if(readModule())
		writeSettings();
	else
		gl_filename = "";
}
void saveDatabase()
{
	cout <<endl << "SAVE DATABASE" <<endl;
	bool setNewFile = false;
	string input;
	if(gl_filename=="")
	{
		cout << "No filename selected. ";
		setNewFile = true;
	}
	else
	{
		cout << "Set New or use Old filename (overwrite existing file)? (n = new/o = old) ";
		bool done = false;
		while(!done)
		{
			getline(cin,input);
			switch(tolower(input[0]))
			{
				case 'n':
					setNewFile = true;
					done = true;
					break;
				case 'o':
					setNewFile = false;
					done = true;
					break;
				default:
					cout << "Please enter 'n' to use a new filename or 'o' to use the old filename '" << gl_filename << "'." <<endl;
			}
		}
	}
	if(setNewFile)
	{
		bool writeFile = false;
		while(!writeFile)
		{
			cout << "Enter new filename: ";
			getline(cin,input);
			if(fileExists(input))
			{
				cout << "File already exists. Overwrite file? (y/n) ";
				bool done = false;
				string i;
				while(!done)
				{
					getline(cin,i);
					switch(tolower(i[0]))
					{
						case 'y':
							writeFile = true;
							done = true;
							break;
						case 'n':
							writeFile = false;
							done = true;
							break;
						default:
							cout << "Please enter 'y' or 'n'." <<endl;
					}
				}
			}
			else
				writeFile = true;
		}
		gl_filename = input;
	}
	writeModule();
	writeSettings();
}
void autoSave()
{
	bool setNewFile = false;
	if(gl_filename=="" && !changesMade)
		return;
	else if(gl_filename=="" && changesMade)
	{
		cout << "No filename selected. ";
		setNewFile = true;
	}
	while(setNewFile)
	{
		cout << "Enter new filename: ";
		string input;
		getline(cin,input);
		if(fileExists(input))
		{
			cout << "File already exists. Overwrite file? (y/n) ";
			bool done = false;
			string i;
			while(!done)
			{
				getline(cin,i);
				switch(tolower(i[0]))
				{
					case 'y':
						gl_filename = input;
						done = true;
						setNewFile = false;
						break;
					case 'n':
						done = true;
						setNewFile = true;
						break;
					default:
						cout << "Please enter 'y' or 'n'." <<endl;
				}
			}
		}
		else
		{
			gl_filename = input;
			setNewFile = false;
		}
	}
	writeModule();
	writeSettings();
}
