// updated 17/11/2020

//#define TEST  // uncomment this line to run with self graders

// PLEASE DON'T UPLOAD THIS FILE TO THE AUTOGRADER.
//-------------------------------------------------

// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.
// However, please read through this section and look at the declarations of the functions and data structures that you will use in your code

#define MaxRow  31		// The number of rows in the frame buffer
#define MaxCol 61		// The number of columns in the frame buffer

#define MaxStar 1891	// The maximum number of stars in a 'completely filled' universe
#define MaxPair 945		// The maximum number of star pairs that can be named in a universe

#define MaxX 60			// The length of the universe in light years
#define MaxY 30			// The width of the universe in light years

// A structure to store data about a star
typedef struct
{
	int id;					// A unique number (identifier) for this star. Identifiers start at 0.
	double x;				// The star's x coordinate in the universe, [0-60] light years
	double y;				// The star's y coordinate in the universe, [0-30] light years
	char name[30];			// The name of this star, maximum 30 chars including the \0 at the end
	int named;				// A flag that is set to true (1) if the star has a name, initially 0 for all stars
} Star;

// A structure to store data about a pair of named stars
typedef struct
{
	Star* h;					// A pointer to the first star in this pair
	Star* w;					// A pointer to the second star in this pair
	double d;					// The distance between the two stars of this pair
} Pair;

extern Star *stars[MaxStar];		// the array of stars
extern Pair *pairs[MaxPair];		// the array of named pairs
extern int numStars;				// number of stars in the universe
extern int numPairs;				// number of named star pairs

// prototypes of the functions that you will implementing
// the functions themselves are in the graph.c, logic.c, and main.c files

// graphics functions
void clearBuffer ();
void plot (int row, int col, char c);
char peek (int row, int col);
void writeAt (int row, int col, char* text);
void showBuffer ();
// program logic functions
Star* findStarByXY(double x, double y, double tolerance);
int bigBang (int n_stars);
double pointDistance (double x1, double y1, double x2, double y2);
Pair* closestPair ();
int nameStar (Star *s, char* first_name, char* sur_name);
Pair* findPairByName (char* name);
int saveUniverse ();
int loadUniverse();
// interface functions
void printStar (Star*);
void listStars ();
void listPairs ();
void drawUniverse ();
void tagPair (Pair* p);
