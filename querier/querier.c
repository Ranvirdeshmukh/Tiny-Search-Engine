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
static void counters_union(counters_t* result, counters_t* ctrs);
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
static void print_query_results(counters_t* results, const char* pageDirectory) {

    if (results !=NULL){
        while(counters_size(results>0)){
            find_and_print_max(results, pageDirectory);
        }

    }
    else{
        printf("No document found.\n");


    }
}
static void find_and_print_max(counters_t* results, const char* pageDirectory){
    struct{
        int docID;
        int count;

    } data={-1,0};

    //making a function to find the max scoring documents 
    void find_max(void* arg, const int key, const int count){
        struct {int docID; int count;}* data =arg;
        if ( count > data->count ){
            data->docID=key;
            data->count= count;


        }
    }

    //iterating over all the documents for finding hte highest scorer 
    counters_iterate(results, &data, find_max);

    if( data.docID != -1){
        char*url = pagedir_getURL(pageDirectory, data, docID);
        if (url !=NULL){
            printf("")
            free(url);

        }


        counters_set(results, data.docID, 0);
    }
    
}

bool isValidQuery(const char* query){
    if (query ==NULL){
        reutrn false;

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
            if (!=is)
        }
    }



}



