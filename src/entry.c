
#include "puzzle_create.h"
#include "entry.h"
#include "solve.h"
#include "trie.h"



//game function
void gameFunction(char* word_file){

    int gameOver = FALSE;
    gameGrid = create2DArray();
    int no_of_words = count_lines(word_file);
    copyGrid = create2DArray(); //used for printing only
	coordArray = createCoordArray(no_of_words);
    addStringsToGrid(gameGrid,no_of_words);
    add_randomLetters(gameGrid);
	//filling the shadow array for printing
    int rows;
	for(rows = 0; rows < ROWS; rows++){

		strcpy(copyGrid[rows], gameGrid[rows]);
	}

    while(gameOver == FALSE){

        system("clear");
        printArray(gameGrid);
        PuzzleToFile("output.txt",gameGrid);
        game_userEntry(word_file);
        gameOver = TRUE;
    }



} // end of game function



void game_userEntry(char *word_file){
    int i,j;
    int no_of_words = count_lines(word_file);
	float timeLimit = 300;
	clock_t start = clock();
	//float seconds = (float)(tick - start)
	char userInput[20]; //previously str1

	int matches = 0;
	int counter = 0;
	int gameOver = FALSE;
	//clock_t start = clock(); //starts the stopwatch
	//clock_t tick = clock();
	gameOver = game_matchesFound(1, 0,no_of_words);

	while(gameOver == FALSE){

		clock_t tick = clock();
		float seconds = (float)(tick - start) / CLOCKS_PER_SEC;
		timeLimit -= seconds;
		printf("\n%.f secs left\n", timeLimit);
		if(timeLimit <= 0){

			printf("Time out...");
			getchar();
			clue("output.txt",word_file);
			getchar();
			system("PAUSE");
			//sleep(2);
			break;
		}
		printf("Enter 1 to Quit OR Keep on Going!!\n");
		printf("\nPlease enter a word: ");
		scanf("%s", userInput);
		char* s;
		s="1";

		if (strcmp(s,userInput)==0){
            clue("output.txt",word_file);
            system("PAUSE");
            break;
		}


		//converts entered string to uppercase
		for(i = 0; i < strlen(userInput); i++){
			if(userInput[i] > 96 && userInput[i] < 123){
				userInput[i] -= 32;
			}
		}

		for(i = 0;i < no_of_words; i++){

			char *selectedString = pointer[i];  //proper pointer, formerly str2
			counter = 0;
			for(j = 0; j < strlen(selectedString); j++){
			//call that function with the i val

				if(userInput[j] == selectedString[j]){

					system("clear"); //clears screen after correct input PUT BACK IN
					printArray(gameGrid);
					counter++;
					//wordFoundColors(j);

				}
				else{
					system("clear");
					printArray(gameGrid);
					printf("\t\tWORD IS NOT PRESENT\n");
					break;
				}
			}
			if(counter==strlen(selectedString)){

				//printf("\nMatch detected in position %d.\n\n", i);
				gameOver = game_matchesFound(0, i,no_of_words);
				//print2DArray(array);
				matches++;
				break;
			}

		}
	}


} //end of void user entry


int game_matchesFound(int reset, int val,int no_of_words){

	static int matchCount = 0;
	static int* matchArray; //contains matches, rules out repeats
	matchArray = malloc(no_of_words*sizeof(int));
	int zeroFilled = FALSE;
	int i;
	int gameOver = FALSE;

	//resets from last game
	if(reset == 1){

		matchCount = 0;
		zeroFilled = FALSE;

		for(i = 0; i < no_of_words; i++){

            matchArray[i] = 0;
		}
		return FALSE;
	}
	while(gameOver == FALSE && reset == 0){ //think about using time func

		if(zeroFilled == FALSE && matchArray[0] == val){

            matchArray[0] = val;
            matchCount++;
            zeroFilled = TRUE;
            wordFoundColors(val);

        }
        else if(matchArray[val] != val){

            matchArray[val] = val;
            wordFoundColors(val);
            matchCount++;

        }
        else{

            printf("\nAlready entered.");
            Sleep(1);
        }

        if(matchCount == no_of_words){


            printf(" __ __ _____ _____    _ _ _ _____ _____ \n");
            printf("|  |  |     |  |  |  | | | |     |   | |\n");
            printf("|_   _|  |  |  |  |  | | | |  |  | | | |\n");
            printf("  |_| |_____|_____|  |_____|_____|_|___|\n");
            getchar();
            Sleep(5);
            system("clear");
            //static variable cleanup for next run: (there is a problem with this)
            matchCount = 0;
            zeroFilled = FALSE;
            for(i = 0; i < no_of_words; i++){

                matchArray[i] = 0;
            }

            return TRUE;
        }
        else{
            return FALSE;
        }
    }//end of while loop
    return TRUE;
} //end of matches found func

/*Adds # character to slot in gameGrid, where color will be added*/
void wordFoundColors(int word){
	//sHANDLE hConsole; hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int i = 0;
    int j = 0;
    int row, col;
    char *tempWord = pointer[word];
    int length = (strlen(tempWord)*2);
    char x = '#';

    for(j=0, i=0; j < length; j++, i++){

		row = coordArray[word][j];
        ++j;
        col = coordArray[word][j];
        gameGrid[row][col] = x;//+ system("COLOR 6C")
		system("clear");
        printArray(gameGrid);
    }
}


//char locations stored in this
int **createCoordArray(int no_of_words){

	int i, j, colWidth;
	int** arr_2D = { 0 };

	arr_2D = malloc(sizeof(int*) *no_of_words);

	for(i = 0; i < no_of_words; i++){
		//get string length of each string and multiply by 2 for j length
		colWidth = (strlen(pointer[i])*2);
		//printf("Index: %d, width: %d\n", i, colWidth);
		arr_2D[i] = (int *)malloc(sizeof(int) * colWidth);
	}

	for(i = 0; i < no_of_words; i++){

		colWidth = ((strlen(pointer[i]))*2);

		for(j = 0; j < colWidth; j++){

			arr_2D[i][j] = 0;
			//printf("%d", arr_2D[i][j]);
		}
	}
	return arr_2D;
	free(arr_2D);
}

