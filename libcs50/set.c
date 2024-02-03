/** 
 * Ranvir Deshmukh
 * Lab 3, Set.c
 * 
*/
// fixed all the memory leaks.

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

/**************** local types ****************/
// defining a structure for the set
typedef struct snode{
    char* key;
    void* item;
    struct snode *next;
} snode_t;

/**************** global types ****************/
typedef struct set{
    snode_t *head;
} set_t;

//creating a new set and allocating hte 
set_t * set_new(void){
    set_t *set = malloc(sizeof(set_t));
    if ( set == NULL){
        return NULL;
    }
    else {
        set -> head = NULL;
        return set;
    }
    

}
/**
 * This function will insert a new key inside the pair in the set. Intially I will put the check so the program doesn't crash,
 *  taught in the lecture videos.
*/
bool set_insert(set_t* set, const char* key, void* item){
    if (item == NULL || key == NULL || set == NULL || set_find(set, key) != NULL) {
        return false;
    }

    snode_t *n_node = malloc(sizeof(snode_t));
    if (n_node == NULL) {
        return false;
    }

    n_node->key = strdup(key);
    if (n_node->key == NULL) { 
        free(n_node);
        return false;
    }

    n_node->item = item;
    n_node->next = set->head;
    set->head = n_node;

    printf("Inserted key: %s\n", key); 

    return true;
}


// search for an item in the set and return the key if its found.

void* set_find(set_t* set, const char* key){

    if ( key == NULL || set == NULL){
        return NULL;
    }
    // c node stands for the current node.
    snode_t *C_node = set ->head;
    while (C_node != NULL){
        if (strcmp( C_node-> key, key)==0){
            return C_node->item;
        }
        C_node = C_node -> next;
    }
    return NULL;
}

/**
 * this function is used to print the contents of the set_t object
 * the function specifically relies on the itemprint to print each key a
 * 
*/
 
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ){
    if (fp != NULL){
        if (set != NULL){
            for ( snode_t* node = set-> head; node != NULL; node = node ->next){
                if (itemprint != NULL) { 
                    (*itemprint)(fp, node->key, node->item); 
                }
            }
        }
        else {
            fputs ("(null)", fp);
        }
    }

}

//this function will iterate over each item in the set and apply a given function

void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ){

    // checking if the item functions and the set are not null
    if ( set != NULL && itemfunc!= NULL){
        // iterate from the head of the state.
        for ( snode_t*node = set -> head; node != NULL; node = node -> next){
            // calling  the itemfunction for every node in the set.
            (*itemfunc)(arg, node->key, node->item);
        }
    }
}

// the function is used to delete the set and as i have used free to free the allocated memory.

void set_delete(set_t* set, void (*itemdelete)(void* item) ){
    if ( set != NULL){
        for( snode_t *node = set ->head; node != NULL;){
            snode_t *next= node ->next;

            if ( itemdelete != NULL){
                (*itemdelete)(node ->item);
            }
            free( node-> key);
            free( node );
            node = next;


        }
        free ( set);

    }

}





