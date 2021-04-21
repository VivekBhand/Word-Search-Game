#include "puzzle_create.h"
#include <stdio.h>
#include <stdlib.h>

char **gameGrid; //is where all the work is done
char **copyGrid; // is what's actually displayed
int **coordArray; //stores all coordiantes of words added via addString
char **pointer;
char *word_file;

/*generates a 2D Array*/
char **create2DArray(){

	int i,j;
	char** array = {0};

	array = malloc(sizeof(char*) *ROWS);

	for(i=0; i < ROWS; i++){

		array[i] = (char *) malloc(sizeof(char) * COLS);
	}
	for(i=0;i<ROWS;i++){

		for(j=0;j<COLS;j++){

			array[i][j] = '.';
		}
	}
	return array;

	free(array);
}//end of create2DArray


/*prints a 2D array*/
void printArray(char **array){
    printf("\n\n");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i,j;
	for( i = 0; i < ROWS; i++){
        printf("\t\t\t");
		for (j = 0; j < COLS;j++){

				if(array[i][j] == '#'){
					SetConsoleTextAttribute(hConsole, YELLOW);
				}
				else
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				printf(" %c ", copyGrid[i][j]);
		}
		printf("\n\n");
	}
}//end of printArray

/*prints a 2D array*/
void printArray_after(char **array){
    printf("\n\n");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i,j;
	printf("\t\t\t");
	for( i = 0; i < COLS; i++){
        SetConsoleTextAttribute(hConsole, YELLOW);
        printf(" %d ",i+1);
	}
	printf("\n\t\t\t_____________________________________________\n");
	for( i = 0; i < ROWS; i++){
        printf("\t\t\t");
        printf("%d|",i+1);
		for (j = 0; j < COLS;j++){

				if(array[i][j] == '#'){
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				}
				else
                    SetConsoleTextAttribute(hConsole, YELLOW);
				printf(" %c ", copyGrid[i][j]);
		}
		printf("|\n\n");
	}
}//end of printArray

/*add Strings to gameGrid*/ //this func needs to spoof them into the color array
void addStringsToGrid(char** gameGrid,int no_of_words){

	int i = 0;
    int counter = 0;
    int horz;


    horz = (rand() % (no_of_words/2) );

    for (i=0; i < no_of_words; i++){

		//replace below with RNG based solution?
		if(counter <= horz){

            //addWord_vertical(gameGrid, i);
			addWord_horizontal(gameGrid, i);
			counter++;
			//i++;
		}
		else if(counter > horz && counter < (no_of_words-(rand() % no_of_words))){
            addWord_vertical(gameGrid, i);
            counter++;
		}
		else {
            addWord_diagonal(gameGrid, i);
            counter++;
		}
	}

}//end of addStrings

void addWord_horizontal(char** gameGrid ,int stringArrIndex){

    static int chaLoc = 0;
	int 	i, randRow, randCol;
	int 	wordPlaced = 0;
	int		spaceClear = 0;

	char *tempWord = pointer[stringArrIndex];

	while(wordPlaced == 0){

        i = 0;
		randRow = (rand()%ROWS);
		randCol = (rand()%COLS);


		if( (COLS - randCol) >= (strlen(tempWord)) ){

			spaceClear = checkSpace_horizontal(stringArrIndex, randCol, randRow);

			if(spaceClear == 1){
			//printf("index: %d\n", stringArrIndex);

				for(i=0; i < strlen(tempWord); randCol++, i++){

					gameGrid[randRow][randCol] = tempWord[i];
					coordArray[stringArrIndex][chaLoc] = randRow;
					//printf("Coord Row %d \n", coordArray[stringArrIndex][chaLoc]);
					++chaLoc;
					coordArray[stringArrIndex][chaLoc] = randCol;
					//printf("Coord Col %d\n", coordArray[stringArrIndex][chaLoc]);
					++chaLoc;
					//debugging

				}
				chaLoc = 0; //cleans static var
				wordPlaced = 1;
				//break;
			} else {

				continue;
			}
		}
	}
}

int checkSpace_horizontal(int stringArrIndex, int randCol, int randRow){

	int i = 0;
	int done = 0;
	int org = randCol;
	char *tempWord = pointer[stringArrIndex];

	while(done == 0){

		randCol = org;
		i = 0;

		for(i=0; i < strlen(tempWord); randCol++){

			if(gameGrid[randRow][randCol] != '.' || gameGrid[randRow][randCol] == tempWord[i]){ // || gameGrid[randRow][randCol] != tempWord[i]

				return 0;
				break;
			}
			else{

				++i;
				//printf("Char Slot: %d ,\n", i);
			}
		}
		done = 1;
		//break;
    }
    return 1;
}

void addWord_vertical(char** gameGrid ,int stringArrIndex){

    static int chaLoc = 0; //location of char in stringArrindex of coordArray
	int i, randRow, randCol;
	int wordPlaced = 0;
	int spaceClear = 0;
	char *tempWord = pointer[stringArrIndex];

	while(wordPlaced == 0){

        i = 0;
		randRow = (rand()%ROWS);
		randCol = (rand()%COLS);


		if( (ROWS - randRow) >= (strlen(tempWord)) ){

			spaceClear = checkSpace_vertical(stringArrIndex, randCol, randRow);

			if(spaceClear == 1){

				for(i=0; i < strlen(tempWord); randRow++, i++){

					gameGrid[randRow][randCol] = tempWord[i];
					//saving coordinates to coord array
					coordArray[stringArrIndex][chaLoc] = randRow;
					++chaLoc; //1 step forward
					coordArray[stringArrIndex][chaLoc] = randCol;
                    ++chaLoc;
				}
                chaLoc = 0; //reset
				wordPlaced = 1;
				//break;
			} else {

				continue;
			}
		}
	}
}

int checkSpace_vertical(int stringArrIndex, int randCol, int randRow){

	int 	i = 0;
	int 	done = 0;
	int 	org = randRow;

	char *tempWord = pointer[stringArrIndex];

	while(done == 0){

		randRow = org;
		i = 0;

		for(i=0; i < strlen(tempWord); randRow++){

			if(gameGrid[randRow][randCol] == '.' || gameGrid[randRow][randCol] == tempWord[i]){

                ++i;
			}else{

				return 0;

			}
		}
		return 1;
    }
    return 1;
}//end of vertical



//must check for 2
void addWord_diagonal(char** gameGrid ,int stringArrIndex){

    static int chaLoc = 0;
	int i, randRow, randCol;
	int wordPlaced = 0;
	int spaceClear = 0;
	char *tempWord = pointer[stringArrIndex];

	while(wordPlaced == 0){

        i = 0;
		randRow = (rand()%ROWS);
		randCol = (rand()%COLS);


		if( (ROWS - randRow) >= (strlen(tempWord)) && (COLS - randCol) >= (strlen(tempWord))){

			spaceClear = checkSpace_diagonal(stringArrIndex, randCol, randRow);

			if(spaceClear == 1){

				for(i=0; i < strlen(tempWord); randRow++, randCol++, i++){

					gameGrid[randRow][randCol] = tempWord[i];
					coordArray[stringArrIndex][chaLoc] = randRow;
					++chaLoc;
					coordArray[stringArrIndex][chaLoc] = randCol;
					++chaLoc;

				}
                chaLoc = 0;
				wordPlaced = 1;
				//break;
			} else {

				continue;
			}
		}
	}
}

int checkSpace_diagonal(int stringArrIndex, int randCol, int randRow){

	int i = 0;
	int done = 0;
	int orgRow = randRow;
	int orgCol = randCol;
	char *tempWord = pointer[stringArrIndex];

	while(done == 0){

		randRow = orgRow;
		randCol = orgCol;
		i = 0;

		for(; i < strlen(tempWord); randRow++,randCol++){

			if(gameGrid[randRow][randCol] == '.' || gameGrid[randRow][randCol] == tempWord[i]){

				++i;
			}
			else{

                return 0;
				//printf("Char Slot: %d ,\n", i);
			}
		}
		return 1;
    }
    return 1;

}//end of checkspace diagonal

void add_randomLetters(char** arr_2D){

	int i, j;

	for(i=0;i<ROWS;i++){

		for(j=0;j<COLS;j++){

			if(gameGrid[i][j] == '.'){

				arr_2D[i][j] = (rand() % 25 + 65);	//mind the magic numbers
			}
		}
	}
}//end of random letters


void PuzzleToFile(char* filename,char** puzzle){
	char d;
	FILE *fp;

	fp = fopen(filename,"w");

	if(fp != NULL){

		//printf("Writing to file %s\n",filename);

		for(int i=0;i<ROWS;++i){

			for(int k=0;k<COLS;++k){
				if(k == ROWS-1){
					d = puzzle[i][k];
					fputc(d,fp);
					fputc('\n',fp);	//Append a newline if it is on the last column
				}
				else{
					d = puzzle[i][k];
					fputc(d,fp);
				}
			}
		}
	}
	else{
		printf("Cannot create output file");
	}
	fclose(fp);
}

int count_lines(char* filename) {
    FILE *fp;
    fp = fopen(filename,"r");


    char ch;
    int linesCount=0;
    //open file in read more

   if(fp) {

       while((ch=fgetc(fp))!=EOF) {
          if(ch=='\n')
             linesCount++;
       }
       //close the file
       fclose(fp);
   }
   //print number of lines

   return linesCount;
}
