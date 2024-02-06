/**
 * Ranvir Deshmukh 
 * Lab 5
 * indextest.c file
*/

#include <stdlib.h>
#include <stdio.h>
#include "../common/index.h"
#include "../libcs50/file.h"

int main(int argc, char* argv[]) {
    //checking the command line argument 
    if (argc != 3){
        fprintf(stderr,"Usage: %s pageDirectory indexFilename\n", argv[0]);
        return 1;

    }

    const char* oldIndexFilename =argv[1];
    const char* newIndexFilename = argv[2];

    index_t *index = index_load(oldIndexFilename);
    if (index == NULL){
        fprintf(stderr, " Unable to load index from '%s' \n", oldIndexFilename);
        return 1;

    }

    //saving the index to the new files
    if (!index_save(index, newIndexFilename)) {
        fprintf(stderr, "Failed to write index to '%s'\n", newIndexFilename);
        index_delete(index);
        return 1;
    }

    // Clean up
    index_delete(index);
    return 0;
}




