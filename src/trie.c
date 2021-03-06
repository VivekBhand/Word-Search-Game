#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

// Function that returns a new Trie node
TrieNode* getNewTrieNode()
{
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }

    return node;
}

// Iterative function to insert a string into a Trie
void insert_trie(TrieNode *head, char* str)
{
    // start from the root node
    TrieNode* curr = head;
    while (*str)
    {
        // create a new node if the path doesn't exist
        if (curr->character[*str - 'a'] == NULL) {
            curr->character[*str - 'a'] = getNewTrieNode();
        }

        // go to the next node
        curr = curr->character[*str - 'a'];
        curr->isLeaf = 1;
        // move to the next character
        str++;
    }

    // mark the current node as a leaf
    curr->isLeaf = 2;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search_trie(TrieNode* head, char* str) {
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }

    TrieNode* curr = head;
    while (*str)
    {
        // go to the next node
        curr = curr->character[*str - 'a'];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL) {
            return 0;
        }

        // move to the next character
        str++;
    }

    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns 1 if a given Trie node has any children
int hasChildren(TrieNode* curr) {
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return 1;       // child found
        }
    }

    return 0;
}

// Recursive function to delete a string from a Trie
int deletion(TrieNode **curr, char* str) {
    // return 0 if Trie is empty
    if (*curr == NULL) {
        return 0;
    }

    // if the end of the string is not reached
    if (*str)
    {
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr))
        {
            free(*curr);    // delete the current node
            (*curr) = NULL;
            return 1;       // delete the non-leaf parent nodes
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0;       // don't delete its parent nodes
        }
    }

    return 0;
}

void print_search(TrieNode* root, char* word) {
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");

    else if(search_trie(root, word) == 2)
        printf("Found!\n");
}

void delete_trienode(TrieNode* node) {

    for(int i=0; i<CHAR_SIZE; i++) {
        if (!hasChildren(node)) {
            delete_trienode(node);
        }
        else {
            continue;
        }
    }
    free(node);
}

