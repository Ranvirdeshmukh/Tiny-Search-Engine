/**
 * Ranvir Deshmukh 
 * Lab-4 ( The Crawler)
 * Pagedir.c file
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"

// initialising the directory for crawler output
bool pagedir_init(const char* pageDirectory){
    char path[200];
    sprintf(path, "%s/.crawler", pageDirectory);

    FILE *fp = fopen(path, "w");
    if( fp== NULL){
        return false;

    }
    fclose(fp);
    return true;
}

// saving a webpage to a page directory.
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    char filepath[200];
    sprintf(filepath, "%s/%d", pageDirectory, docID);


    FILE *fp =fopen(filepath, "w");
    if (fp != NULL){
        fprintf(fp, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
        fclose(fp);

    }
    /// Additionally, create a ".crawler" file in the directory to mark it as created by the crawler
        char crawlerFilePath[200];
        sprintf(crawlerFilePath, "%s/.crawler", pageDirectory);
        FILE *crawlerFile = fopen(crawlerFilePath, "w");

        if (crawlerFile != NULL) {
        fprintf(crawlerFile, "This directory is used by the crawler.");
        fclose(crawlerFile);
        }
    


    
//not finding the file path properluy.
}

// Validate that a directory is a Crawler-produced directory
bool pagedir_validate(const char* pageDirectory) {
    char path[200];
    sprintf(path, "%s/.crawler", pageDirectory);

    FILE* fp = fopen(path, "r");
    if (fp != NULL) {
        fclose(fp);
        return true;
    }
    return false;
}

// Load a webpage from a file within the pageDirectory
webpage_t* pagedir_load(const char* pageDirectory, const int docID) {
    char filepath[200];
    sprintf(filepath, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(filepath, "r");
    if (fp == NULL) {
        return NULL;
    }

    char* URL = file_readLine(fp);
    int depth;
    fscanf(fp, "%d", &depth);
    char* html = file_readFile(fp);

    webpage_t* page = webpage_new(URL, depth, html);
    fclose(fp);

    return page;
}


