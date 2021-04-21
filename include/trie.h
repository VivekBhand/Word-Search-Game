#ifndef TRIE_H
#define TRIE_H

// Define the character size
#define CHAR_SIZE 26

// Data structure to store a Trie node
typedef struct Trie {
    int isLeaf;             // 2 when the node is a leaf node
                            // 1 when contains letter
    struct Trie* character[CHAR_SIZE];
}TrieNode;

TrieNode* getNewTrieNode();

void insert_trie(TrieNode *head, char* str);

int search_trie(TrieNode* head, char* str);

int hasChildren(TrieNode* curr);

int deletion(TrieNode **curr, char* str);

void print_search(TrieNode* root, char* word);

void delete_trienode(TrieNode* node);


#endif // TRIE_H
