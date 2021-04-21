
#ifndef PUZZLE_CREATE_H
#define PUZZLE_CREATE_H

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <time.h>

#include <windows.h>
#define ROWS 12
#define COLS 12
#define FALSE 0
#define TRUE 1



char **create2DArray();
void printArray(char **array);
void addWord_horizontal(char** mainArray, int stringArrIndex);
void addStringsToGrid(char** gameGrid,int no_of_words);
int checkSpace_horizontal(int stringArrIndex, int randCol, int randRow);
void addWord_vertical(char** gameGrid ,int stringArrIndex);
int checkSpace_vertical(int stringArrIndex, int randCol, int randRow);
void addWord_diagonal(char** gameGrid ,int stringArrIndex);
int checkSpace_diagonal(int stringArrIndex, int randCol, int randRow);
void add_randomLetters(char** arr_2D);
void printArray_after(char **array);

extern char **gameGrid; //is where all the work is done
extern char **copyGrid; // is what's actually displayed
extern int **coordArray; //stores all coordiantes of words added via addString
extern char **pointer;
extern char *word_file;

typedef enum {
		RED=64,ORANGE=41,YELLOW=14, GREEN=160, BLUE=9, INDIGO=11, VIOLET=13
}colors;

void PuzzleToFile(char* filename,char** puzzle);
int count_lines(char* filename);
#endif // PUZZLE_CREATE_H


