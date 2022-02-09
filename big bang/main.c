/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: main.c

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Yimin Zhao
Student ID: 201388904
Email: sc19yz3@leeds.ac.uk
Date Work Commenced: 2020/12/5
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uni.h"


// Use the following format strings in your printf statements so that your program output will be identical to mine
//-----------------------------------------------------------------------------------------------------------------
/*

"star %i\n"
"name: %s\n"
"coords: (%.3f,%.3f)\n"
"Pair %i:\n"
"distance: %f\n"
"**************************\n"
"The Big Bang has occurred!\n"
"Sorry, unable to bang!\n"
"Sorry no pairs were found!\nWish you a better luck in the next universe\n"
"The closest pair of stars are no. %i and %i\n"
"They are %.3f light years apart\n"
"Would you like to name this pair (y/n)?"
"Enter your full name:"
"Enter your spouse full name:"
"Congratulations a pair of stars has been named after you and your spouse\n"
"Thanks, you have saved the universe!\n"
"Congratulations, your saved universe was restored!\n"
"No such command!\n"

*/


// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************



// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// initially, some of these functions contain 'return 0'. Before implementing a function you should delete this statement



// Print the details of a star
void printStar (Star* s)
{
	printf("star %i\n", s->id);
	if (s->named)
		printf("name: %s\n", s->name);
	printf("coords: (%.3f,%.3f)\n", s->x, s->y);
}

// Display a list of all stars in the universe
void listStars ()
{
	for (int i = 0; i < numStars; ++i)
		printStar(stars[i]);
}

// List all named pairs
void listPairs ()
{
	for (int i = 0; i < numPairs; ++i)
	{
		printf("Pair %i:\n",i);
		printf("distance: %f\n",pairs[i]->d);
		printf("star %i\n",pairs[i]->h->id);
		printf("name: %s\n",pairs[i]->h->name);
		printf("coords: (%.3f,%.3f)\n",pairs[i]->h->x,pairs[i]->h->y);
		printf("star %i\n",pairs[i]->w->id);
		printf("name: %s\n",pairs[i]->w->name);
		printf("coords: (%.3f,%.3f)\n",pairs[i]->w->x,pairs[i]->w->y);
		printf("**************************\n");
	}

}

// Draw the entire universe
void drawUniverse ()
{
	for (int i = 0; i < numStars; ++i)
	{
		if (stars[i]->named == 0)
			plot(stars[i]->y, stars[i]->x, '.');
		else if (stars[i]->named == 1)
			plot(stars[i]->y, stars[i]->x, '*');
	}
	//showBuffer();
}

// Tag a named pair of stars by writing a string comprising the names of the couple that own the pair
// underneath this pair in the frame buffer (see assignment brief)
// The names of the 2 owners should be concatenated into one string with an & sign in between.
// The name of the h star should be first followed by the name of the w star (by the way, h stands for husband and w stands for wife).
// For example, if the the h star name is "Mr Bean" and the w star name is "Irma Gobb", the string will be "Mr Bean & Irma Gobb"
// with exactly one space before and after the &.
// The string should be positioned one row below the h star's row, with the middle of the string aligned with the h star's column
// Calling this function will NOT cause the frame buffer to be redisplayed on the screen, if you need to show the frame buffer, you must
// call showBuffer (but NOT inside this function)

void tagPair (Pair* p)
{
	char middle[4] = " & ";
	char tag[30];
	int len = 0;
	tag[0] = '\0';

	strcat(tag, p->h->name);
	strcat(strcat(tag, middle), p->w->name);
	len = strlen(tag);

	writeAt(p->h->y+1, p->h->x-len/2, tag);
}

// DON'T CHANGE THE FOLLOWING 3 LINES
#ifndef TEST
int  main (int argc, char* argv[])
{
	// ENTER THE CODE OF YOUR main FUNCTION BELOW
	

	char command[15];
	char* p;
	char para[10];

	

	do
	{
		//input prompt of command
		printf(">>>");
		gets(command);
		p = command;

		//if the command is "bang x", split it into "bang" and "x"
		if (*p == 'b')
		{
			para[0] = '\0';
			for (; *p != '\0'; ++p)
				if (*p == ' ')
				{
					*p = '\0';
					strcpy(para, ++p);
					break;
				}
		}

		//for command "bang x"
		if (strcmp(command, "bang") == 0)
		{
			time_t t;
			srand((unsigned) time(&t));

			for (int i = 0; para[i] != '\0'; ++i)
			{
				if (para[i] < '0' || '9' < para[i])
				{
					para[0] = '\0';
					break;
				}
			}

			if (bigBang(atoi(para)) == 1)
				printf("The Big Bang has occurred!\n");
			else
				printf("Sorry, unable to bang!\n");
			continue;
		}

		//for command "list"
		if (strcmp(command, "list") == 0)
		{
			listStars();
			continue;
		}

		//for command "name"
		if (strcmp(command, "name") == 0)
		{
			char fn[10], ln[10];
			char yORn;
			Pair *pair;
			pair = closestPair();

			if (pair == 0)
			{
				printf("Sorry no pairs were found!\nWish you a better luck in the next universe\n");
				continue;
			}

			printf("The closest pair of stars are no. %i and %i\nThey are %.3f light years apart\nWould you like to name this pair (y/n)?", pair->h->id, pair->w->id, pair->d);
			scanf("%c", &yORn);
			if (yORn == 'y')
			{
				printf("Enter your full name:");
				scanf("%s", fn);
				scanf("%s", ln);
				

				if (nameStar(pair->h, fn, ln) == 1)
				{
					printf("Enter your spouse full name:");
					scanf("%s", fn);
					scanf("%s", ln);
					if (nameStar(pair->w, fn, ln) == 1)
					{
						pairs[numPairs] = pair;
						numPairs++;
						printf("Congratulations a pair of stars has been named after you and your spouse\n");
						getchar();
						continue;
					}
				}
			}
			else if (yORn == 'n')
			{
				getchar();
				continue;
			}

			else
			{
				printf("No such command!\n");
				continue;
			}
		}

		//for command "pairs"
		if (strcmp(command, "pairs") == 0)
		{
			listPairs();
			continue;
		}

		//for command "draw"
		if (strcmp(command, "draw") == 0)
		{
			clearBuffer();
			drawUniverse();
			showBuffer();
			continue;
		}

		//for command "show"
		if (strcmp(command, "show") == 0)
		{
			Pair *pair;
			char your_name[10];
			printf("Enter your full name:");
			gets(your_name);


			pair = findPairByName(your_name);
			if (pair != 0)
			{
				clearBuffer();
				drawUniverse();
				tagPair(pair);
				showBuffer();
				continue;
			} 
			else
			{
				printf("Sorry no pairs were found!\nWish you a better luck in the next universe\n");
				continue;
			}

		}

		//for command "save"
		if (strcmp(command, "save") == 0)
		{
			saveUniverse();
			printf("Thanks, you have saved the universe!\n");
			continue;
		}

		//for command "load"
		if (strcmp(command, "load") == 0)
		{
			loadUniverse();
			printf("Congratulations, your saved universe was restored!\n");
			continue;
		}

		//for command "quit"
		if (strcmp(command, "quit") == 0)
			break;
		else
			printf("No such command!\n");
	}

	while(1);

	

// DON'T CHANGE THE FOLLOWING 2 LINES
}
#endif
// DON'T WRITE ANYTHING BELOW THIS LINE