#ifndef SOLVE_H
#define SOLVE_H



#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

//Change this to match puzzle input size!
#define PUZZLESIZE 12

//Struct to keep track of direction of the words
typedef struct{
	int vertical;
	int horizontal;
	char direction[15];
}direction;


/* Prototypes
*/

void readPuzzle(char puzzleFile[], char puzzle[PUZZLESIZE][PUZZLESIZE]);
int findWord(char word[], char puzzle[PUZZLESIZE][PUZZLESIZE],  direction *dir, int *frow, int *fcol);
int searchRestOfWord(char word[], char puzzle[PUZZLESIZE][PUZZLESIZE],  direction dir, int row, int col, int index);
void printPuzzle(char puzzle[PUZZLESIZE][PUZZLESIZE]);
void clue(char* puzzleFile,char *word);

#endif // SOLVE_H
