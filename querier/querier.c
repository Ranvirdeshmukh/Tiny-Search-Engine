/**
 * Ranvir Deshmukh 
 * lab 6 - Querier, 
 * file name - Querier.c
 * 
*/

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



/*Function for parsing and validating queries */
bool isValidQuery(const char* query);
char** parseQuery(const char* query, int* numWords);

/* Function to interact with the user and process queries */
void interactiveMode(index_t* index, const char* pageDirectory);

/* Functions to set operations on counters (for 'and' and 'or' queries) */
counters_t* counters_intersection(counters_t* ctrs1, counters_t* ctrs2);
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


void processQuery(const char* query, index_t* index, const char* pageDirectory){
    //assuming the parse query and isvalidquery are implemented 
    if (!isValidQuery(query)){
        fprintf(stderr,"Wrong Query.\n");
        return;


    }

    int numWords=0;
    char ** words =parseQuery(query, &numWords);

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
    counters_delete(results);

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

static counters_t* and_sequence(char** words, int start, int end, index_t* index){
    counters_t* result = index_get(index, words[start]);

    for (int i = start + 1; i < end; i++) {
        if (strcmp(words[i], "and") != 0) {
            counters_t* ctrs = index_get(index, words[i]);
            counters_t* temp = counters_intersection(result, ctrs);
            counters_delete(result);
            result = temp;
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
            while (!counters_is_empty(results)) {
                find_and_print_max(results, pageDirectory);
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

    } data={-1,0};

    //making a function to find the max scoring documents 
    
    //iterating over all the documents for finding hte highest scorer 
    counters_iterate(results, &data, find_max);

    if( data.docID != -1){
        char*url = pagedir_getURL(pageDirectory, data, data.docID);
        if (url !=NULL){
            printf("");
            free(url);

        }


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


bool isValidQuery(const char* query){
    if (query ==NULL){
        return false;

    }
    //checking for the empty query
    if (strlen(query) ==0){
        return false;

    }
    // now spliting the query in the words and then words to process each word.
    char *temp = strdup(query);
    char *word = strtok(temp,"");

    // to track if the last word was  the operator it wont work then.

    bool lastWasOperator = false;

    while (word!=NULL){
        //checking for the valid word.
        for (int i=0 ; word[i]!= '\0'; i++){
            if (!isalpha(word[i])){
                free(temp);
                return false;

            }
        }

        normalizeWord(word);



        //checking for the valid use of the 'and' 'or' operators
        if ((strncmp(word, "and", 3) == 0 || strncmp(word, "or", 2) == 0) && lastWasOperator) {
                free(temp);
                return false;
   

        }
        else{
            lastWasOperator= false;
            
        }
        
        word = strtok(NULL, " ");


    }
    // Ensure query does not end with an operator
    if (lastWasOperator) {
        free(temp);
        return false;
    }

    free(temp);
    return true;
}


char** parseQuery(const char* query, int* numWords) {
    char**words =NULL;
    *numWords=0;

    if (query == NULL){
        return NULL;

    }

    //copy the query to avoid moddiyfying the orginal string 
    char * temp = strdup(query);
    char * word = strtok(temp, "");

    while (word != NULL) {
        words = realloc(words, (*numWords + 1) * sizeof(char*));
        words[*numWords] = strdup(word); // Ensure strdup is correctly declared
        (*numWords)++;
        word = strtok(NULL, " ");
    }

    free(temp);
    return words;
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

static void intersection_helper(void *arg, const int key, int count) {
    counters_t *result = arg;
    int count2 = counters_get(result, key);
    if (count2 > 0) {
        counters_set(result, key, (count < count2) ? count : count2);
    } else {
        counters_set(result, key, 0);
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