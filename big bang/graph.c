/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: graph.c

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



#include <stdlib.h>
#include <stdio.h>
#include "uni.h"

char fbr[MaxRow][MaxCol];	// the frame buffer

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************


// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash


// Clear the frame buffer, i.e. fill all positions with the space character
// 3 lines of code
void clearBuffer ()
{
	for (int i = 0; i < MaxRow; ++i)
		for (int j = 0; j < MaxCol; ++j)
			fbr[i][j] = ' ';
}

// Plot a character into the frame buffer, i.e. store the character in the frame buffer at location row, col.
// Before attempting to plot the character the function should make sure that row and col are valid values (e.g. row is not < 0)
// If the location is not valid, the character is not plotted and the function should not cause the program to crash
// 3 lines of code
void plot (int row, int col, char c)
{
	if (0 <= row && row < MaxRow && 0 <= col && col < MaxCol)
		fbr[row][col] = c;
}

// Peek at the frame buffer's location given by row and column indices
// Before attempting to peek at a location the function should make sure that row and col are valid values (e.g. row is not < 0)
// If the location is not valid the function should return 0,
// otherwise the function returns the character stored at that location
// 3 lines of code
char peek (int row, int col)
{
	if (0 <= row && row < MaxRow && 0 <= col && col < MaxCol)
		return fbr[row][col];
	return 0;
}

// Write a string into the frame buffer starting at location row, col.
// The string is written horizontally starting at location row,col
// If the text is too long to fit into the frame buffer (e.g. we reach the edge of the frame before all chars of the string are written),
// the function should not crash and any remaining chars in the string are ignored (clipped)
// The function should not crash if any of the parameters are invalid
// 11 lines of code
void writeAt (int row, int col, char str[])
{
	if (0 <= row && row < MaxRow && 0 <= col && col < MaxCol)
		for (int j = 0; col < MaxCol && str[j] != '\0'; ++col, ++j)
			fbr[row][col] = str[j];

}

// Display (print) the whole frame buffer on the screen
// 6 lines of code
void showBuffer ()
{
	for (int i = 0; i < MaxRow; ++i)
	{
		for (int j = 0; j < MaxCol; ++j)
			printf("%c", fbr[i][j]);
		printf("\n");
	}
}