/**
 * Ranvir Deshmukh 
 * lab 6 - Querier, 
 * file name - Querier.c
 * 
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/pagedir.h"
#include "../common/index.h"    
#include "../common/word.h"
#include "../libcs50/file.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include <ctype.h>



//Declaring all the functions:

/* Function to load the index from a file */
index_t* index_load(const char* indexFilename);

/*Function to handle the query procesing*/
void processQuery(const char* query, index_t* index, const char* pageDirectory);

char ** tokenize(const char* query, int* numWords);


/*Function for parsing and validating queries */
bool isValidQuery(char** words, int numWords);
char** parseQuery(const char* query, int* numWords);

/* Function to interact with the user and process queries */
void interactiveMode(index_t* index, const char* pageDirectory);

/* Functions to set operations on counters (for 'and' and 'or' queries) */
static void intersection_helper(void *arg, const int key, int count1);
counters_t* counters_union(counters_t* ctrs1, counters_t* ctrs2);

// main fucntion 
int main(int argc, char* argv[]);


int main(int argc, char* argv[]){
    //like every prev lab validate the command line argument 
    if (argc!=3){
        fprintf(stderr,"Usage: ./querier pageDirectory indexFilename\n");
        return 1;

    }

    char* pageDirectory =argv[1];
    char* indexFilename = argv[2];

    //loading the index.
    index_t* index = index_load(indexFilename);
    if (index == NULL) {
        fprintf(stderr, "Error while loading index from file %s\n", indexFilename);
        return 2;
    }

    //callign interative mode
    interactiveMode(index, pageDirectory);

    //cleanup
    index_delete(index);
    return 0;

}

// Helper function prototypes for the process query
static counters_t* and_sequence(char** words, int start, int end, index_t* index);
static counters_t* or_sequence(char** words, int numWords, index_t* index);
// counters_t* counters_union(counters_t* ctrs1, counters_t* ctrs2);
static void print_query_results(counters_t* results, const char* pageDirectory);

char ** tokenize(const char* query, int* numWords){
    if (query == NULL){
        numWords =0;
        return NULL;

    }

    // allocating the space for the words array
    int capacity =10;
    char ** words =  malloc(capacity * sizeof(char*));
    *numWords =0;

    const char* wordStart = query;
    while (*wordStart != '\0') {
        //skiping the white spaces
        while (isspace(*wordStart)){
            wordStart++;

        }
        const char* wordEnd = wordStart;
        while(*wordEnd!='\0' &&!isspace(*wordEnd)){
            wordEnd++;

        }
        //if we find the word, add it to the array
        if (wordEnd != wordStart) {
            int wordLength = wordEnd - wordStart;
            words[*numWords] = strndup(wordStart, wordLength);
            normalizeWord(words[*numWords]);
            (*numWords)++;

            // Resize the array if necessary
            if (*numWords == capacity) {
                capacity *= 2;
                words = realloc(words, capacity * sizeof(char*));
            }

            wordStart = wordEnd;
        }
        if (*wordStart != '\0') wordStart++; // Skip the space
    }
    return words;


    
}


void processQuery(const char* query, index_t* index, const char* pageDirectory){
    int numWords=0;
    char ** words =tokenize(query, &numWords);
    
    // Validate the tokenized query
    if (!isValidQuery(words, numWords)) {
        fprintf(stderr, "Invalid Query.\n");
        // Free the allocated words
        for (int i = 0; i < numWords; i++) {
            free(words[i]);
        }
        free(words);
        return;
    }

    

    if (numWords==0){
        free(words);
        return;

    }
    counters_t* results = or_sequence(words, numWords, index);

    // Print the results of the query
    print_query_results(results, pageDirectory);

    //clean up 
    for (int i=0; i <numWords; i++){
        free(words[i]);

    }
    free(words);
    // counters_delete(results);

}

static counters_t* or_sequence(char** words, int numWords, index_t* index){
    counters_t *result =counters_new();
    int start =0;

    for (int i=0; i<numWords; i++){
        if( strcmp(words[i], "or")==0){
            counters_t * subResult = and_sequence(words, start,i , index);
            counters_union(result, subResult);
            counters_delete(subResult);
            start= i+1;
        }
    }
    counters_t* subResult = and_sequence(words, start, numWords, index);
    counters_union(result, subResult);
    counters_delete(subResult);

    return result;

}

static counters_t* and_sequence(char** words, int start, int end, index_t* index) {
    if (words == NULL || index == NULL) {
        return NULL;
    }

    counters_t* result = counters_new();
    if (result == NULL) {
        return NULL;
    }

    counters_t* temp = index_get(index, words[start]);
    counters_iterate(temp, result, intersection_helper);

    for (int i = start + 1; i < end; i++) {
        if (strcmp(words[i], "and") != 0) {
            temp = index_get(index, words[i]);
            counters_iterate(temp, result, intersection_helper);
        }
    }

    return result;
}

// Helper function to find and print the highest-scoring document
static void find_and_print_max(counters_t* results, const char* pageDirectory);
static void find_max(void* arg, const int key, const int count);

// Helper function to check if there are any non-zero counts.
static void has_nonzero_count(void *arg, const int key, int count) {
    bool *hasNonZero = (bool *)arg;
    if (count > 0) {
        *hasNonZero = true;
    }
}

static void print_query_results(counters_t* results, const char* pageDirectory) {
    if (results != NULL) {
        bool hasNonZero = false;
        counters_iterate(results, &hasNonZero, has_nonzero_count);
        
        if (hasNonZero) {
            // As long as we find a non-zero counter, keep finding and printing max
            while (hasNonZero) {
                hasNonZero = false;
                find_and_print_max(results, pageDirectory);
                counters_iterate(results, &hasNonZero, has_nonzero_count);
            }
        } else {
            printf("No document found.\n");
        }
    }
    else {
        printf("No document found.\n");
    }
}

static void find_and_print_max(counters_t* results, const char* pageDirectory){
    struct{
        int docID;
        int count;
    } data = {-1, 0};

    // Iterate over all the documents to find the highest scorer
    counters_iterate(results, &data, find_max);

    if (data.docID != -1) {
        // Load the webpage using pagedir_load
        webpage_t* page = pagedir_load(pageDirectory, data.docID);
        if (page != NULL) {
            // Print the document ID, count, and URL
            printf("Doc ID: %d, Count: %d, URL: %s\n", data.docID, data.count, webpage_getURL(page));

            // Clean up
            webpage_delete(page); // Frees the memory allocated for the webpage
        } else {
            printf("Error retrieving webpage for document %d\n", data.docID);
        }

        // Reset the count for this document ID to 0
        counters_set(results, data.docID, 0);
    }
}

// Define find_max function before its usage
static void find_max(void* arg, const int key, const int count) {
    struct {int docID; int count;}* data = arg;
    if (count > data->count) {
        data->docID = key;
        data->count = count;
    }
}


bool isValidQuery(char** words, int numWords) {
    if (numWords == 0) return false;

    if (strcmp(words[0], "and") == 0 || strcmp(words[0], "or") == 0 ||
        strcmp(words[numWords - 1], "and") == 0 || strcmp(words[numWords - 1], "or") == 0) {
        return false;
    }

    for (int i = 0; i < numWords - 1; i++) {
        if ((strcmp(words[i], "and") == 0 || strcmp(words[i], "or") == 0) &&
            (strcmp(words[i + 1], "and") == 0 || strcmp(words[i + 1], "or") == 0)) {
            return false;
        }
    }

    return true;
}


char** parseQuery(const char* query, int* numWords) {
    return tokenize(query, numWords);

}

void interactiveMode(index_t* index, const char* pageDirectory){
    char *query;
    size_t len =0;

    printf("Enter query (or press Ctrl+D to exit): ");

    while (getline(&query, &len, stdin) != -1) {
        // Remove trailing newline character if present
        if (query[strlen(query) - 1] == '\n') {
            query[strlen(query) - 1] = '\0';
        }

        // Process and handle the query
        processQuery(query, index, pageDirectory);

        printf("\nEnter query (or press Ctrl+D to exit): ");
    }

    free(query); // Free the memory allocated by getline
}

static void intersection_helper(void *arg, const int key, int count1) {
    counters_t *ctrs2 = arg;
    int count2 = counters_get(ctrs2, key);
    if (count2 > 0) {
        int minCount = (count1 < count2) ? count1 : count2;
        counters_set(ctrs2, key, minCount);
    } else {
        counters_set(ctrs2, key, 0);
    }
}
// Union helper function declaration
static void union_helper(void *arg, const int key, int count);

// Implementation of counters_union
counters_t* counters_union(counters_t* ctrs1, counters_t* ctrs2) {
    counters_t *result = counters_new();
    if (result == NULL) {
        return NULL;

    }
    
    // Merge ctrs1 into result
    counters_iterate(ctrs1, result, union_helper);
    // Merge ctrs2 into result
    counters_iterate(ctrs2, result, union_helper);
    return result;
}

// Implementation of union_helper function
static void union_helper(void *arg, const int key, int count) {
    counters_t *result = arg;
    int existingCount = counters_get(result, key);
    counters_set(result, key, existingCount + count);
}



// // Adjusted counters_union function
// counters_t* counters_union(counters_t* ctrs1, counters_t* ctrs2) {
//     counters_t *result = counters_new();
//     if (result != NULL) {
//         counters_iterate(ctrs1, result, union_helper);
//         counters_iterate(ctrs2, result, union_helper);
//     }
//     return result;
// }