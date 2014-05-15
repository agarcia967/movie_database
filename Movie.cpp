/* Final Project (Movie Database)
   File Name:          Movie.cpp
   Programmer:         Anthony Garcia
   Date Last Modified: May 13, 2014
*/
#include "Movie.h"
using namespace std;

Movie::Movie(string new_title, int new_year, int new_rating)
{
	title = new_title;
	year = new_year;
	rating = setRating(new_rating);
}
//// Accessors & Mutators ////
void Movie::setTitle(string new_title)
{
	title = new_title;
}
string Movie::getTitle()
{
	return title;
}

void Movie::setYear(int new_year)
{
	year = new_year;
}
string Movie::getYear()
{
	ostringstream ss;
    ss << year;
    return ss.str();
}

void Movie::setRating(Rating new_rating)
{
	rating = new_rating;
}
Rating Movie::setRating(int new_rating)
{
	try
	{
		if(new_rating>=6 || new_rating<0)
			throw InvalidRatingException();
		else if(new_rating==0)
			rating = NR;
		else if(new_rating==1)
			rating = G;
		else if(new_rating==2)
			rating = PG;
		else if(new_rating==3)
			rating = PG_13;
		else if(new_rating==4)
			rating = R;
		else if(new_rating==5)
			rating = UR;
	}
	catch(InvalidRatingException)
	{
		cout << "InvalidRatingException: Rating integer " << new_rating << " is invalid. Defaulted to 'NR'.\nReEnter integer in range 0-5." <<endl;
		rating = NR;
	}
	return rating;
}
string Movie::getRating()
{
	string s;
	switch(rating)
	{
	case NR:
		s = "NR"; break;
	case G:
		s = "G"; break;
	case PG:
		s = "PG"; break;
	case PG_13:
		s = "PG-13"; break;
	case R:
		s = "R"; break;
	case UR:
		s = "UR"; break;
	}
	return s;
}
//// Virtual Functions ////
string Movie::toString()
{
	string s = title;
	s += " (";
	s += getYear();
	s += ") - ";
	s += getRating();
	return s;
}
bool Movie::matchKey(string key)
{
	string lowerTitle = "";
	for(int i = 0; i < title.size(); i++)
	{
		lowerTitle += tolower(title[i]);
	}

	string lowerKey = "";
	for(int i = 0; i < title.size(); i++)
	{
		lowerKey += tolower(key[i]);
	}
    if(strstr(lowerTitle.c_str(), lowerKey.c_str()))
        return true;
    else if(strstr(getYear().c_str(), lowerKey.c_str()))
        return true;
    else
        return false;
}

/////////////// DVD Definition ///////////////

void DVD::setSortTitle()
{
	string trbl[] = {"a ", "an ", "the "};
	int size = 3;
	string sorted = "DVD ";
	string line = getTitle();
	bool flag = false;
	int position = line.find(' ');
	string firstWord = line.substr(0,position);
	for(int i = 0; i < size && !flag; i++)
	{
		for(int j = 0; j < firstWord.length(); j++)
		{
			if(tolower(firstWord[j])==trbl[i][j])
			{
				flag = true;
			}
			else
				flag = false;
		}
	}
	if(flag)
	{
		line = line.substr(position+1,line.length());
	}
	sorted += line;
	sorted += " ";
	sorted += getYear();
	
	sortTitle = sorted;
}

DVD::DVD(string new_title, int new_year, int new_rating) : Movie(new_title, new_year, new_rating)
{
	sortTitle = "";
	setSortTitle();
}

string DVD::getSortTitle()
{
	return sortTitle;
}

/////////////// VHS Definition ///////////////

void VHS::setSortTitle()
{
	string trbl[] = {"a ", "an ", "the "};
	int size = 3;
	string sorted = "VHS ";
	string line = getTitle();
	bool flag = false;
	int position = line.find(' ');
	string firstWord = line.substr(0,position);
	for(int i = 0; i < size && !flag; i++)
	{
		for(int j = 0; j < firstWord.length(); j++)
		{
			if(tolower(firstWord[j])==trbl[i][j])
			{
				flag = true;
			}
			else
				flag = false;
		}
	}
	if(flag)
	{
		line = line.substr(position+1,line.length());
	}
	sorted += line;
	sorted += " ";
	sorted += getYear();
	
	sortTitle = sorted;
}

VHS::VHS(string new_title, int new_year, int new_rating) : Movie(new_title, new_year, new_rating)
{
	sortTitle = "";
	setSortTitle();
}

string VHS::getSortTitle()
{
	return sortTitle;
}
