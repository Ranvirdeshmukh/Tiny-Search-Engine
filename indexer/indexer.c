/**
 * Ranvir Deshmukh 
 * Lab-5 
 * Indexer.c 
 * 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
// #include "libcs50-given.a"

// Function prototyping 
void indexBuild(const char* pageDirectory, index_t* index);
void indexPage(webpage_t* page, int docID, index_t* index);


// main function
int main(int argc, char* argv[]){

    // checking of the command line argument 
    if (argc != 3){
        fprintf(stderr,"Usage: %s pageDirectory indexFilename\n", argv[0]);
        return 1;

    }
    const char* pageDirectory = argv[1];
    const char* indexFilename = argv[2];

    // validating page directory 
    if (!pagedir_validate(pageDirectory)){
        fprintf(stderr, " Wrong PageDirectory '%s'\n", pageDirectory);
        return 1;
    }

    // creating a new index 
    index_t *index =index_new(200);
    if (index ==NULL){
        fprintf( stderr, " Unable to make a new index \n");
        return 1;

    }

    //buidling the index from the page direcotry 
    indexBuild(pageDirectory, index);

    //save  index to file 
    index_save(index, indexFilename);

    //cleaniing up
    index_delete(index);
    return 0;
        

}

void indexBuild(const char* pageDirectory, index_t* index){
    int docID=1;
    webpage_t* page;

    while ((page = pagedir_load(pageDirectory, docID))!=NULL){
        indexPage(page, docID, index);
        webpage_delete(page);
        docID++;
    }
}


void indexPage(webpage_t* page, int docID, index_t* index) {
    int pos = 0;
    char* word;

    while ((word = webpage_getNextWord(page, &pos)) != NULL) {
        if (strlen(word) >= 3) {
            char* normalizedWord = normalizeWord(word);
             // Free original word after normalizing it.

            if (index_get(index, normalizedWord) == NULL) {
                // First occurrence of the word, add it to the index.
                index_add(index, normalizedWord, docID);
            } else {
                // Word already in index, just update counters.
                counters_t* ctrs = index_get(index, normalizedWord);
                counters_add(ctrs, docID);
            }

            free(normalizedWord); // Free normalized word after use.
        } 
        free(word);
    }
}
