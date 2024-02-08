/**
 * Ranvir Deshmukh
 * Lab-4
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/pagedir.h"
#include "../libcs50/mem.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include <stdbool.h>
#include "../libcs50/webpage.h"
#include <string.h>



//declaration of the function
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

static bool validateURL(const char* url);

int main(const int argc, char*argv[]){
    char *seedURL;
    char *pageDirectory;
    int maxDepth;

    //parse and validat ethe command line arugment
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    // //start crawling 
    crawl(seedURL,pageDirectory, maxDepth);

    //free the space
    
    // free (pageDirectory);

    return 0;


}



char* copystr(char* str) {
    char* copy = mem_malloc(strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s seedURL pageDirectory maxDepth\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Assign the command-line arguments directly
    *seedURL = argv[1];
    *pageDirectory = argv[2];
    *maxDepth = atoi(argv[3]);

    char* normalizedURL;
    normalizedURL = normalizeURL(*seedURL);
    if (normalizedURL == NULL || !isInternalURL(normalizedURL)) {
        fprintf(stderr, "Invalid or non-internal URL: %s\n", *seedURL);
          // Free if normalization was successful but URL is not internal
        exit(EXIT_FAILURE);
    }
    free(normalizedURL);
    

    if (!pagedir_init(*pageDirectory)) {
        fprintf(stderr, "Invalid page directory: %s\n", *pageDirectory);
        exit(EXIT_FAILURE);
    }
    

    // Additional checks can be added here if necessary
    // For example, check if maxDepth is within a reasonable range
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "maxDepth must be between 0 and 10\n");
        exit(EXIT_FAILURE);
    }
}

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
    bag_t* pagesToCrawl = bag_new();
    hashtable_t* pagesSeen = hashtable_new(200);
    int docID =0;

    if (!pagesToCrawl || !pagesSeen) {
        // Handle memory allocation error for pagesToCrawl or pagesSeen
        exit(EXIT_FAILURE);
    }
    char* seedURLcopy = (char*) malloc(strlen(seedURL) + 1);
    strcpy(seedURLcopy, seedURL);

    webpage_t* seedPage = webpage_new(seedURLcopy, 0, NULL);
    if (!seedPage) {
        // Handle memory allocation error for seedPage
        bag_delete(pagesToCrawl, NULL);
        hashtable_delete(pagesSeen, NULL);
        exit(EXIT_FAILURE);
    }

    bag_insert(pagesToCrawl, seedPage);

    webpage_t* currentPage;
    while ((currentPage = bag_extract(pagesToCrawl)) != NULL) {
        printf("Page found: %s\n", webpage_getURL(currentPage));
        

        if (webpage_fetch(currentPage)) {
            printf("Page fetched: %s\n", webpage_getURL(currentPage));

            pagedir_save(currentPage, pageDirectory, ++docID);

            if (webpage_getDepth(currentPage) < maxDepth) {
                printf("Page scanned: %s\n", webpage_getURL(currentPage));
                pageScan(currentPage, pagesToCrawl, pagesSeen);
                // webpage_delete(currentPage);
            } else {
                // webpage_delete(currentPage);

            }
        } else {
            // webpage_delete(currentPage);

        }
        webpage_delete(currentPage);


    }

    printf("------------------ crawler done ------------------\n\n\n");

    bag_delete(pagesToCrawl, webpage_delete);
    hashtable_delete(pagesSeen, mem_free);
}



static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
    int pos = 0;
    char* result;

    while ((result = webpage_getNextURL(page, &pos)) != NULL) {
        if (validateURL(result)) {
            if (hashtable_insert(pagesSeen, result, result)) {
                webpage_t* newPage = webpage_new(copystr(result), webpage_getDepth(page) + 1, NULL);
                bag_insert(pagesToCrawl, newPage);
            } else {
                // If the URL was not inserted, free it
                free(result);
            }
        } else {
            // If the URL is not valid, free it
            free(result);
        }
        
    }
}


static bool validateURL(const char* url) {
    return url != NULL && isInternalURL(url);
}





// static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){

//     if (argc!= 4){
//         fprintf(stderr, "%s seedURL pageDirectory maxDepth\n", argv[0]);
//         exit(EXIT_FAILURE);

//     }
// //     //normalise and validate the seedurl
//     char *normalizedURL = normalizeURL(argv[1]);
//     if (normalizedURL==NULL || !isInternalURL(normalizedURL)){
//         fprintf(stderr , "non-internal seed URL: %s\n", argv[1]);
//         free(normalizedURL);
//         exit ( EXIT_FAILURE);
//     }
//     *seedURL = normalizedURL;
    
//     // validate pageDirectory and check if the directory exists and is writabble  
//     FILE* testfile = fopen(argv[2],"r");
//     if(testfile==NULL){
//         fprintf(stderr, " Wrong Page Directory: %s\n",argv[2] );
//         printf("%s", argv[2]);
//         free(normalizedURL);
//         exit(EXIT_FAILURE);

//     }


//     fclose(testfile);
//     *pageDirectory = strdup(argv[2]);

//     //validating max depth 
//     int depth;
//     if( sscanf(argv[3], "%d", &depth)!= 1 || depth <0 || depth>10 ){
//         fprintf(stderr, "Wrong maximum depth:%s\n", argv[3]);
//         free(normalizedURL);
//         exit(EXIT_FAILURE);
//     }
//     *maxDepth= depth;

