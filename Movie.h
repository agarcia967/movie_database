/* Final Project (Movie Database)
   File Name:          Movie.h
   Programmer:         Anthony Garcia
   Date Last Modified: May 13, 2014
*/
#ifndef MOVIE
#define MOVIE

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

enum Rating { NR, G, PG, PG_13, R, UR };

/////////////// Movie Definition ///////////////
class Movie
{
private:
	string title;
	int year;
	Rating rating;
	class InvalidRatingException
	{  };
public:
  //// Constructors ////
	Movie(string new_title, int new_year, int new_rating);
  //// Accessors & Mutators ////
  	void setTitle(string new_title);
  	string getTitle();
  	
  	void setYear(int new_year);
  	string getYear();
  	
  	void setRating(Rating new_rating);
  	Rating setRating(int new_rating);
    string getRating();
  //// Virtual Functions ////
	virtual string toString();
	virtual void setSortTitle() = 0;
	virtual bool matchKey(string key);
};

/////////////// DVD Definition ///////////////
class DVD : public Movie
{
private:
	virtual void setSortTitle();
	string sortTitle;
public:
	DVD(string new_title, int new_year, int new_rating);
	string getSortTitle();
};

/////////////// VHS Definition ///////////////
class VHS : public Movie
{
private:
	virtual void setSortTitle();
	string sortTitle;
public:
	VHS(string new_title,int,int);
	string getSortTitle();
};

#endif
