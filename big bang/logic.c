/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: logic.c

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Yimin Zhao
Student ID: 201388904
Email: sc19yz3@leeds.ac.uk
Date Work Commenced: 2020/11/29
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.
// However, please read through this section and look at the declarations of arrays and global vars that you will be using in your program


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "uni.h"


int SerNum=0;			// a counter to create unique star numbers (identifiers)
int numStars = 0;		// the actual number of stars in the universe (not the same as the maximum)
int numPairs = 0;		// the number of pairs that have been named

Star *stars[MaxStar];		// the array of stars (an array of pointers to stars)
Pair *pairs[MaxPair];		// the array of named pairs (an array of pointers to pairs)

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// NOW IT IS YOUR TURN, YOU CAN DEFINE ANY OTHER GLOBAL VARIABLES YOU MAY NEED IN YOUR CODE BELOW THIS LINE

// int saved_numStars, saved_numPairs;			//Used to save the number of stars and the number of pairs


// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// Initially, some of these functions contain 'return 0' or 'return -99'. Before implementing a function you should delete this statement
// None of the functions should cause memory leaks


// The purpose of this function is to find a star through its coordinates.
// The first two parameters are the coordinates of the star we are looking for.
// Since the coordinates are double (real) numbers, we cannot compare them for exact equality,
// hence the 3rd parameter to this function is a very small number (e.g. 0.00000001) called the tolerance.
// If the absolute difference between the x (or y) coordinate of a star and the given x (or y) coordinate
// is less than the tolerance, we assume that the two values are equal.
// If a star with the given x and y coordinates is found, the function should return a pointer to this star
// otherwise the function returns 0 indicating failure to find a star with such coordinates.
// 4-6 lines of code.
Star* findStarByXY  (double x , double y, double tolerance)
{
	for ( int i = 0; i < numStars; ++i)
		if (fabs(x - stars[i]->x) < tolerance && fabs(y - stars[i]->y) < tolerance)
			return stars[i];

	return 0;
}

// The purpose of this function is to create a new universe containing stars only.
// The number of stars in this new universe is given by the parameter n_stars.
// The stars should be randomly scattered within the universe, i.e, each star should be assigned a random value
// for its x and y coordinates. x can take any random value from [0 - MaxX] inclusive,
// and y can take any random value from [0 - MaxY] inclusive.
// Although the x and y coordinates of a star are defined as double numbers, for simplicity we will only
// assign whole numbers to x and y. Every star should have its unique location, no two stars can have the same x and y coordinates.
// Hence the maximum number of stars in a completely filled universe that is 60 lights years long and 30 light years wide
// is 1891 stars (this is the value of MaxStar defined in uni.h). The minimum number of stars in a universe is 1.
// If the function fails to create the universe for any reason (including an invalid value of n_stars), it should return 0
// indicating failure, otherwise it should return 1 indicating success.
// Since this function is the start of a new universe, it should also initialise all global variables.
int bigBang (int n_stars)
{
	double tolerance = 0.00000001;
	int result = 0;
	double x = 0, y = 0;

	//to initialize the number of stars and the number of pairs every time that big bang occurs
	numStars = n_stars;
	numPairs = 0;

	if (0 < n_stars && n_stars <= MaxStar)
	{
		//to allocate space for every star and pair
		for (int i = 0; i < n_stars; ++i)
			stars[i] =(Star*) malloc(sizeof(Star));
		for (int i = 0; i < n_stars/2; ++i)
			pairs[i] =(Pair*) malloc(sizeof(Pair));

		for ( SerNum = 0; SerNum < n_stars; ++SerNum)
		{
			//generate random numbers and check repetition
			loop:
			x = rand() % (MaxX+1);
			y = rand() % (MaxY+1);

			for (int h = 0; h < SerNum; ++h)
				if (fabs(stars[h]->x - x) <= tolerance && fabs(stars[h]->y - y) <= tolerance )
					goto loop;

		
			
			//give information to stars
			stars[SerNum]->x = x;
			stars[SerNum]->y = y;
			stars[SerNum]->id = SerNum;
			stars[SerNum]->name[0] = '\0';
			stars[SerNum]->named = 0;


 	
		}

		result = 1;
	}
	return result;
}


// The purpose of this function is to compute the distance between two points in a Cartesian plane.
// The coordinates of the first point are x1 , y1.
// The coordinates of the second point are x2, y2.
// The function returns the distance between the two points.
// 2 lines of code.
double pointDistance (double x1, double y1, double x2, double y2)
{
	double distance = sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));

	return distance;
}


// The purpose of this function is to find the closest pair of stars that have not been named yet.
// If a pair cannot be found (e.g. because all pairs have already been named) the function should return 0 (null),
// otherwise the function should return a pointer to a Pair structure initialised with h pointing to the first star in the pair
// and w pointing to the second star.
Pair* closestPair ()
{
	Pair *result = 0;
	double distance1;
	double distance2;
	int idh = 0, idw = 1;
	Pair *closest_pair = (Pair*)malloc(sizeof(Pair));

	if (0 <= numPairs && numPairs < numStars/2 && numStars > 1)
    {
    	distance1 = pointDistance(stars[0]->x, stars[0]->y, stars[1]->x, stars[1]->y);
    	//compare distence between every possiable pair
		for (int i = 0; i < numStars; ++i)
		{
			for (int j = i+1; j < numStars; ++j)
			{
				if (stars[i]->named != 1 && stars[j]->named != 1)
				{
					distance2 = pointDistance(stars[i]->x, stars[i]->y, stars[j]->x, stars[j]->y);
					distance1 = (distance2<distance1)?distance2:distance1;
					if (distance1 == distance2)
					{
						idh = i;
						idw = j;
					}
				}
			}
		}

		//give information for this closest pair
		closest_pair->h = stars[idh];
		closest_pair->w = stars[idw];
		closest_pair->d = distance1;

		result = closest_pair;
	}
	

	return result;	
}

// The purpose of this function is to assign the name of a person to a star.
// The first parameter is a pointer to the star to be named.
// The second parameter is the first name of the person.
// The last parameter is the surname of the person.
// The function should append the surname to the first name - with one single space in between - to create one single string for the full name.
// For example, if the first name is "Mr" and the surname is "Bean", the full name string will be "Mr Bean".
// If everything goes well and the star is named, the function returns 1 indicating success.
// The function also sets the named flag of the star to 1.
// If anything goes wrong (including invalid parameter values), the function should return 0 indicating failure.
int nameStar (Star *s, char* first_name, char* sur_name)
{
	char full_name[30];
	char space[2];
	space[0] = ' ';
	full_name[0] = '\0';

	if (s==0||first_name==0||sur_name==0||strlen(first_name)+strlen(sur_name)+1 > 29)
		return 0;

	strcat(strcat (strcat (full_name, first_name), space), sur_name);
	strcpy(s->name, full_name);
	
	s->named = 1;
	return 1;
}


// The purpose of this function is to find a pair by the name of either spouse (one of the owners of the pair).
// The parameter to this function is the full name of a person.
// If either star in a named pair have this name, the function returns a pointer to this pair,
// If no such pair is found the function returns 0
Pair* findPairByName (char* name)
{
	for ( int i = 0; i < numPairs; ++i)
		if (strcmp(pairs[i]->h->name, name) == 0 || strcmp(pairs[i]->w->name, name) == 0)
			return pairs[i];
	return 0;
}

// The purpose of this function is to save all the data of the program to a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1 indicating success in saving the universe
int saveUniverse ()
{
	FILE *save;

	if ((save = fopen("universe.bin","wb")) == NULL)
		return 0;

	//save the number of stars and pairs
	fwrite(&numStars, sizeof(int), 1, save);
	fwrite(&numPairs, sizeof(int), 1, save);

	fwrite(stars, sizeof(Star), numStars, save);
	fwrite(pairs, sizeof(Pair), numPairs, save);

	fclose(save);

	return 1;
}



// The purpose of this function is to load a universe from a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1, indicating success in loading the universe
int loadUniverse ()
{
	FILE *load;

	if ((load = fopen("universe.bin","rb")) == NULL)
		return 0;

	//load the number of stars and pairs
	fread(&numStars, sizeof(int), 1, load);
	fread(&numPairs, sizeof(int), 1, load);

	fread(stars, sizeof(Star), numStars, load);
	fread(pairs, sizeof(Pair), numPairs, load);
	fclose(load);

	return 1;
}



// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW
// WITH THEIR PROTOTYPES DEFINED IN THE GLOBAL VARS SECTION OF THIS FILE
//----------------------------------------------------------------------