#include "puzzle_create.h"
#include "solve.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reads in the puzzle from the file and stores it in a 2d array
 */
void readPuzzle(char puzzleFile[], char puzzle[PUZZLESIZE][PUZZLESIZE]){

	FILE *ifp;
	int row=0, col=0;
	int input;
	char in;

	//Attempt to open file
	if((ifp = fopen(puzzleFile, "r")) == NULL){
		fprintf(stderr, "Cannot open %s\n", puzzleFile);
	}

	do{
		input = fscanf(ifp, "%c", &in);
        if(isalpha(in)){    //ensure char we read in is a letter
			puzzle[row][col] = in;
			col++;
		}

		else if(in == '\n'){
			row++; col=0; //go to position 0 of next row, you're at the end of the line
		}

	} while(input != EOF && row < PUZZLESIZE);
	fclose(ifp);
}





/* findWord searches for a word in the puzzle and determines the  direction.
 * Args: char word[] -- the word we are searching for
 * char puzzle[][] -- the puzzle we are searching in
 *  direction -- where we will store the  direction of the word we find
 * int *frow, *fcol- where we will store the location of the found word.
 */
int findWord(char word[], char puzzle[PUZZLESIZE][PUZZLESIZE],  direction *dir, int *frow, int *fcol){
	//returns 0 if not found, 1 if found

	int row, col;

	//first look for the first letter of the word.

	for(row = 0; row < PUZZLESIZE; row++){
		for(col = 0; col < PUZZLESIZE; col++){
			if(puzzle[row][col] == word[0]){ //first letter found

				//now we need to search in all directions

				if(col!=PUZZLESIZE-1){ //if you are not all the way right (word cant be outside of puzzle)
					if(puzzle[row][col+RIGHT]==word[1]){ // checking for forward words
						dir->vertical=0; // not going up or down
						dir->horizontal=RIGHT; //word is going to right
						strcpy(dir->direction, "Forward");
					}
				}

				if(col!=0){ //not all the way left
					if(puzzle[row][col+LEFT] == word[1]){ //backwards
						dir->vertical=0;
						dir->horizontal=LEFT;
						strcpy(dir->direction, "Backwards");
					}
				}

				if(row!=PUZZLESIZE-1){ //not all the way down
					if(puzzle[row+DOWN][col] == word[1]){ //downwards
						dir->vertical=DOWN;
						dir->horizontal=0;
						strcpy(dir->direction, "Down");
					}
				}

				if(row!=0){ //not all the way upwards
					if(puzzle[row+UP][col] == word[1]){ //upwards
						dir->vertical=UP;
						dir->horizontal=0; //going straight up
						strcpy(dir->direction, "Upwards");
					}
				}


				//diagonals?
				if(row!=0 && col != PUZZLESIZE-1){ // if not in topright corner
					if(puzzle[row+UP][col+RIGHT] == word[1]){
						dir->vertical=UP;
						dir->horizontal=RIGHT;
						strcpy(dir->direction, "Up-Right");
					}
				}

				if(row!=0 && col!= 0){ //if not in top left corner
					if(puzzle[row+UP][col+LEFT] == word[1]){
						dir->vertical=UP;
						dir->horizontal=LEFT;
						strcpy(dir->direction, "Up-Left");
					}
				}





				if(row!=PUZZLESIZE-1 && col!= PUZZLESIZE-1){ //if not in bottom right
					if(puzzle[row+DOWN][col+RIGHT] == word[1]){
						dir->vertical=DOWN;
						dir->horizontal=RIGHT;
						strcpy(dir->direction, "Down-Right");
					}
				}


				if(row!=PUZZLESIZE-1 && col!= 0){ //if not in bottom left
					if(puzzle[row+DOWN][col+LEFT] == word[1]){
						dir->vertical=DOWN;
						dir->horizontal=LEFT;
						strcpy(dir->direction, "Down-Left");
					}
				}



				if(searchRestOfWord(word, puzzle, *dir, row+dir->vertical, col+dir->horizontal, 2) ==1){
					*frow=row; //row where word was found
					*fcol=col; //col where word was found
					return 1; //whole word found
				}
			}
		}
	}
	return 0; // NOT FOUND
}


/* Recursively searches the rest of the word once the  direction is found.
 * Args: char word[] -- the word we are searching for
 * char puzzle[PUZZLESIZE][PUZZLESIZE] -- the puzzle we are searching
 *  direction *dir -- the struct containing the  direction of the word given to us by function findWord(char char  direction int int)
 * int row, col -- where we will store the location of the found word.
 * int index -- keeps track of where in the word we are
 */

int searchRestOfWord(char word[], char puzzle[PUZZLESIZE][PUZZLESIZE], direction dir, int row, int col, int index){

	//base case
	if(word[index] == puzzle[row+dir.vertical][col+dir.horizontal]) { // next letter found in any direction


		return index == strlen(word)-1 ? 1 : searchRestOfWord(word, puzzle, dir, row+dir.vertical, col+dir.horizontal, index+1);

	}

	else{
		return 0; //letter didnt match
	}



}

/* Prints out the puzzle to standard output.
 * Args: char puzzle[][] -- puzzle we are printing out
 */
void printPuzzle(char puzzle[PUZZLESIZE][PUZZLESIZE]){

	int row, col;

	for(row = 0; row < PUZZLESIZE; row++){
		for(col = 0; col < PUZZLESIZE; col++){
			printf("%c ", puzzle[row][col]);
		}
		printf("\n");
	}
	return;
}






void clue(char* puzzleFile,char *wordlist){

	FILE* wordFile;
	char word[PUZZLESIZE]; // a word could be as large as the puzzle
	char puzzle[PUZZLESIZE][PUZZLESIZE];

	//our findWord function is going to want this stuff...
	direction dir;
	int row, col;

	//default values
	dir.vertical = 0;
	dir.horizontal = 0;
	row = 0;
	col = 0;

	//read puzzle
	readPuzzle(puzzleFile, puzzle);
	//open word file

	wordFile = fopen(wordlist,"r");
    if (!wordFile){
        printf("not created");
    }
    system("clear");
    printArray_after(gameGrid);
    printf("\n********************************************************************************\n");
    printf("\n\n\t\tHERE IS ANSWER TO THE PUZZLE FOR YOU!!\n\n\n");
	int input  = fscanf(wordFile, "%s", word);
	//loop through all of the words in our word list
	while(input != -1) {
		if(findWord(word, puzzle, &dir, &row, &col) == 1){ //if word found
			printf("Found word %s at location (%d,%d) going in the %s direction.\n", word, row+1, col+1, dir.direction);
		}
        else
            printf(" ");
		input = fscanf(wordFile,"%s",word); //look at another word, we're finished with the previous one
	}

	return;
}

