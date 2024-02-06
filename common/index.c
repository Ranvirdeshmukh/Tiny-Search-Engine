/**
 * 
 * Ranvir Deshmukh
 * Lab 5
 * index.c
 * 
*/

#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../libcs50/file.h"


//making the local function prototype 
static void custom_counters_delelete(void *item);
static void index_save_helper(void *arg, const char *key, void *item);


/*Creating a new and empty index structure */
index_t* index_new(const int num_slots){
    index_t* index = malloc(sizeof(*index));
    if (index !=NULL){
        index->hashtable = hashtable_new(num_slots);
        if (index->hastable ==NULL){
            free(index);
            return NULL;

        }
    }
    return index;

}

// adding words with docID to index.
bool index_add(index_t *index, const char *word, const int docID){
    if (index==NULL || word ==NULL ){
        return false;

    }

    counters_t * ctrs =hashtable_find(index->hashtable, word);
    // if the word is not in the index add it.
    if (ctrs ==NULL){
        ctrs = counters_new();
        if(ctrs != NULL){
            counters_add ( ctrs, docID);
            hashtable_insert(index->hashtable, word, ctrs);

        }
        else{
            return false;

        }


    }
    else{
        // if the word exists update the counter 
        counters_add(ctrs, docID);
    }
    return true;

}


// saving tyhe index to the file.
void index_save(const index_t *index, const char *filename){
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        hashtable_iterate(index->hashtable, file, index_save_helper);
        fclose(file);
    }
}

//using a helper functionfor index_save to handle each word.
static void index_save_helper(void *arg, const char *key, void *item) {
    FILE *file = (FILE *)arg;
    counters_t *ctrs = (counters_t *)item;

    fprintf(file, "%s ", key);
    counters_print(ctrs, file);
    fprintf(file, "\n");
}

// function to load index from the file 
index_t* index_load(const char *filename) {
    FILE*file= fopen(filename, "r");
    if (file==NULL){
        return NULL;

    }
    index_t *index = index_new(200);
    char word[200];

    while (fscanf(file, "%s", word) != EOF) {
        counters_t *ctrs = counters_new();
        int docID, count;

        while (fscanf(file, "%d %d", &docID, &count) == 2) {
            counters_set(ctrs, docID, count);
        }

        hashtable_insert(index->hashtable, word, ctrs);
    }

    fclose(file);
    return index;

}


/* Delete the index */
void index_delete(index_t *index) {
    hashtable_delete(index->hashtable, custom_counters_delelete);
    free(index);
}

/* Wrapper function for counters_delete */
static void custom_counters_delelete(void *item) {
    counters_delete((counters_t *)item);
}


