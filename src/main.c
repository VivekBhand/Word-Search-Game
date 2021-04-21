
#include "puzzle_create.h"
#include "entry.h"


#define LSIZ 12
                                                                                                                                                                                                    char *citys[] = {"MUMBAI", "PUNE", "NASHIK", "KALYAN", "NAGPUR", "SOLAPUR", "THANE", "DADAR"};
                                                                                                                                                                                                    char *colours[] = {"BLACK", "PURPLE", "YELLOW", "ORANGE", "PINK", "GREEN", "BLUE", "RED"};//char *{"",};
                                                                                                                                                                                                    char *animals[] = {"DOG","CAT","COW","BULL","DEER","TIGER","HORSE","LION"};
//                                                                                                                                                                                                    char *animals[] = {"DOG","CAT","COW","BULL","DEER","TIGER","HORSE","LION","ELEPHANT","FOX","PENGUIN","WOLF","GIRAFFE","LEOPARD"};
int main(){

    srand(time(NULL));
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	int gameOver = FALSE;
	int choice = 0;
	int no_of_words;
    FILE *fp;


    printf("\n");
	printf("\t\t\t _ _ _           _    _____                 _   \n");
	printf("\t\t\t| | | |___ ___ _| |  |   __|___ ___ ___ ___| |_ \n");
	printf("\t\t\t| | | | . |  _| . |  |__   | -_| .'|  _|  _|   |\n");
	printf("\t\t\t|_____|___|_| |___|  |_____|___|__,|_| |___|_|_|\n");
	printf("\n\n\n\t\t\t\t\tVivek Bhand");
	Sleep(200);
	getchar();

	while(gameOver == FALSE){

		system("clear");
		printf("\t\t\t\t******************\n");
		printf("\t\t\t\tChoose a category:\n");
		printf("\t\t\t\t******************\n\n");
		printf("\t\t\t\t1:Animals\n");
		printf("\t\t\t\t2:Citys\n");
		printf("\t\t\t\t3:The Colours\n");
//		printf("\t\t\t\t4:Enter new text file\n");
		printf("\t\t\t\t0 To Quit\n\n");
		printf("\t\t\t\tChoice:> ");
		scanf("%d", &choice);
		getchar();

		//could've done switch here
		if(choice == 1){

            fp=fopen("animals.txt","r");
            if(!fp)
            printf("couldn't open\n");
            no_of_words = count_lines("textFile/animals.txt");
            char animal[no_of_words][LSIZ];			//max word length 10
            for (int i = 0; i < no_of_words; i++) {
                fgets(animal[i],12,fp);
            }
			pointer = animals;
			printf("\nFind 8 animals.\n\n");
			Sleep(1);


			gameFunction("textFile/animals.txt");
			fclose(fp);
		}
		if(choice == 2){


            fp=fopen("citys.txt","r");
            if(!fp)
            printf("couldn't open\n");
            no_of_words = count_lines("textFile/citys.txt");
            char city[no_of_words][10];			//max word length 10

            for (int i = 0; i < no_of_words; i++) {
                fgets(city[i],12,fp);
            }
			pointer = citys;
			printf("\nFind 8 City of the India!\n\n");
			Sleep(4);
			gameFunction("textFile/citys.txt");
			fclose(fp);
		}
		if(choice == 3){


            fp=fopen("colours.txt","r");
            if(!fp)
            printf("couldn't open\n");
            no_of_words = count_lines("textFile/colours.txt");
            char colour[no_of_words][LSIZ];			//max word length 10

            for (int i = 0; i < no_of_words; i++) {
                fgets(colour[i],12,fp);
            }
			pointer = colours;
			printf("\nFind 8 colours!");
            Sleep(2);
			gameFunction("textFile/colours.txt");
			fclose(fp);
		}
//		if(choice == 4){
//            printf("Enter file name:");
//            char input[20];
//           scanf("%s",input);
//            fp=fopen(input,"r");
//            if(!fp) {
//                printf("couldn't open\n");
//            }
//            else {
//                no_of_words = count_lines(input);
//                char* word[no_of_words][LSIZ];			//max word length 10
//                char* str =malloc(15);
//                for (int i = 0; i < no_of_words; i++) {
//                    fscanf(fp,"%s",str);
//                    strcpy(word[i],str);
//                }
//                char** words;
//                words = (char **)malloc(no_of_words * sizeof(char*));
//                for (int i = 0; i < no_of_words; i++)
//                    words[i] = malloc(256*sizeof(char));
//                for (int i = 0; i < sizeof(word)/sizeof(*word); i++)
//                    strcpy(words[i],word[i]);
//                for (int i = 0; i < no_of_words; i++){
//                    printf("%s ",word[i]);
//                }
//
//                pointer = word;
//                printf("\nFind words!\n");
//                Sleep(2);
//                printf("NOT WORKING NOW\n");
                //gameFunction(input);
//            }
//            getchar();
//            fclose(fp);
//		}
		if(choice == 0){

			gameOver = TRUE;
			system("clear");
			printf("\n\n\n\n\n");
			printf("\t\t\t\t****************************************************\n");
			printf("\t\t\t\t\t\tThank You!\n");
			printf("\t\t\t\t*************************************************\n");
			Sleep(15);
			break;
		}
	}

	return 0;

}//end of menu
