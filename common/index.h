/**
 * Ranvir Deshmukh 
 * index.h
*/


#ifndef __INDEX_H
#define __INDEX_H

#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include <stdbool.h>

// The index is a wrapper for a hashtable.
typedef struct index {
    hashtable_t *hashtable;
} index_t;

// Function prototypes
index_t *index_new(const int num_slots);
bool index_add(index_t *index, const char *word, const int docID);
static void index_save_helper(void *arg, const char *key, void *item);
index_t* index_load(const char *filename);
void index_save(const index_t *index, const char *filename);
void index_delete(index_t *index);
static void custom_counters_delelete(void *item);
static void index_save_helper(void *arg, const char *key, void *item);

#endif // __INDEX_H