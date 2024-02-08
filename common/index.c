/**
 * 
 * Ranvir Deshmukh
 * Lab 5
 * index.c
 * 
*/
#define _POSIX_C_SOURCE 200809L 
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../libcs50/file.h"
#include <string.h>



//making the local function prototype 
static void custom_counters_delete(void *item);
static void index_save_helper(void *arg, const char *key, void *item);



/*Creating a new and empty index structure */
index_t* index_new(const int num_slots){
    index_t* index = malloc(sizeof(*index));
    if (index !=NULL){
        index->hashtable = hashtable_new(num_slots);
        if (index->hashtable ==NULL){
            free(index);
            return NULL;

        }
    }
    return index;

}

// Adding words with docID to index.
bool index_add(index_t *index, const char *word, const int docID){
    if (index == NULL || word == NULL) {
        return false;
    }

    // Find the counters set associated with the word.
    counters_t *ctrs = hashtable_find(index->hashtable, word);

    // If the word is not in the index, add it.
    if (ctrs == NULL) {
        // Create a new counters set for this word.
        ctrs = counters_new();
        if (ctrs != NULL) {
            // Add the docID to the counters set.
            counters_add(ctrs, docID);
            // Insert the new word with its counters set into the hashtable.
            hashtable_insert(index->hashtable, word, ctrs);
        } else {
            // Failed to create a new counters set.
            return false;
        }
    } else {
        // If the word exists, update the counter for the docID.
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

    counters_print(ctrs, stderr);
    fprintf(file, "%s ", key);
    counters_print(ctrs, file);
    fprintf(file, "\n");
}

// function to load index from the file 
index_t* index_load(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    index_t *index = index_new(200);
    if (index == NULL) {
        fclose(file);
        return NULL;
    }

    char word[200];
    while (fscanf(file, "%s", word) != EOF) {
        // Allocate memory for the word and copy it.
        char *wordCopy = strdup(word);
        if (wordCopy == NULL) {
            index_delete(index);
            fclose(file);
            return NULL;
        }

        counters_t *ctrs = counters_new();
        if (ctrs == NULL) {
            free(wordCopy);
            index_delete(index);
            fclose(file);
            return NULL;
        }

        int docID, count;
        while (fscanf(file, "%d %d", &docID, &count) == 2) {
            counters_set(ctrs, docID, count);
        }

        // Check if insertion fails.
        if (!hashtable_insert(index->hashtable, wordCopy, ctrs)) {
            free(wordCopy);
            counters_delete(ctrs);
            index_delete(index);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return index;
}

// Function to retrieve counters for a word
counters_t* index_get(index_t *index, const char *word) {
    if (index == NULL || word == NULL) {
        return NULL;
    }
    return hashtable_find(index->hashtable, word);
}



/* Delete the index */
void index_delete(index_t *index) {
    hashtable_delete(index->hashtable, custom_counters_delete);
    free(index);
}

/* Wrapper function for counters_delete */
static void custom_counters_delete(void *item) {
    counters_delete((counters_t *)item);
}


