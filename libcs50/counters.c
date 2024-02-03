/*
 * Ranvir Deshmukh 
 * counters.c
 * 01/23/2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "counters.h"

/**************** local types ****************/
typedef struct cnode{
    int key;
    int count;
    struct cnode *next ;
}cnode_t;

/**************** global types ****************/
typedef struct counters{
    struct cnode * head;
} counters_t;

// helper function

static cnode_t *cnode_new(const int key);

/**************** counters_new() ****************/
counters_t* counters_new(void){
    counters_t *ctrs = malloc(sizeof(counters_t));

    if (ctrs == NULL){
        return NULL;
    }
    else{
        ctrs -> head =NULL;
        return ctrs;
    }
}

/**************** counters_add() ****************/
int counters_add(counters_t* ctrs, const int key){
    if (ctrs != NULL && key >= 0 ){
        // finding the key in the counters 
        for (cnode_t* node = ctrs -> head; node != NULL; node= node -> next){
            if ( node -> key == key ){
                node -> count ++;
                return node -> count;
            }
        }
        // if the key isnt found, create a new counter node 

        cnode_t *new = cnode_new (key);
        if ( new != NULL){
            new -> next = ctrs -> head;
            ctrs -> head = new;
            return new -> count;

        }

    }
    return 0;

}

/**************** counters_get() ****************/
int counters_get(counters_t* ctrs, const int key){
    if ( ctrs != NULL && key >= 0){
        for ( cnode_t * node = ctrs ->head ; node != NULL; node= node -> next){
            if ( node -> key == key){
                return node -> count;

            }
        }
    }
    return 0;

}

/**************** counters_set() ****************/

bool counters_set(counters_t* ctrs, const int key, const int count){
    if (ctrs != NULL && key >= 0 && count >= 0) {
        for ( cnode_t * node = ctrs ->head ; node != NULL; node= node -> next){
            if ( node -> key == key){
                node -> count =count;
                return true;

            }
        }
        
    }
    return false;

}

/**************** counters_print() ****************/
void counters_print(counters_t* ctrs, FILE* fp){
    if (fp != NULL){
        if ( ctrs != NULL){
            fputc('{',fp);
            for ( cnode_t * node = ctrs ->head ; node != NULL; node= node -> next){
                fprintf(fp, "%d=%d, ", node->key, node->count);
            } 
            fputc('}',fp);
        }
        else{
            fputs("(null)", fp);
        }
    }


}

/**************** counters_iterate() ****************/
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count)){
    if ( ctrs!= NULL && itemfunc != NULL){
        for ( cnode_t * node = ctrs ->head ; node != NULL; node= node -> next){
            (*itemfunc)(arg, node->key, node->count);

    }


}
}
/**************** counters_delete() ****************/
void counters_delete(counters_t* ctrs){
    if ( ctrs!= NULL){
        for ( cnode_t * node = ctrs ->head ; node != NULL; ){
            cnode_t *next =node ->next;
            free(node);
            node= next;

        }
        free(ctrs);

    }
}

// helper function created to make a new node in the counters data structure. it's just placed at last here to for better organisation as taught in the notes.

static cnode_t * cnode_new(const int key) {
    cnode_t *node = malloc(sizeof(cnode_t));
    if (node == NULL) {
        return NULL;
    } else {
        node->key = key;
        node->count = 1;
        node->next = NULL;
        return node;
    }
}


