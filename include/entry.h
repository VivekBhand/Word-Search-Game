#ifndef ENTRY_H
#define ENTRY_H

void game_userEntry(char* word_file);
int game_matchesFound(int reset, int val,int no_of_words);
void gameFunction(char* word_file);
void print_coordIntArray(int **arr); //debugging only
void wordFoundColors(int word);


int **createCoordArray(int no_of_words);



#endif // ENTRY_H

