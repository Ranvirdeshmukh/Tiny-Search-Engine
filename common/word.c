/**
 * 
 * Ranvir Deshmukh 
 * lab 5
 * word.c
 * 
*/

#include "word.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// convert to lower case
char* normalizeWord(char* word) {
    if (word==NULL){
        return NULL;

    }

    char *normalized = malloc(strlen(word)+1);
    //^memory allocation fails
    if (normalized ==NULL){
        
        return NULL;
        
    }

    for (int i = 0; word[i] != '\0'; i++) {
        normalized[i] = tolower(word[i]);
    }
    normalized[strlen(word)] = '\0'; // Null-terminate the string

    return normalized;



}