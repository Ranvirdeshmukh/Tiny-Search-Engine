/**
 * Ranvir Deshmukh 
 * hashtable.c , lab3
 * 01/23/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hashtable.h"
#include "../libcs50/set.h"

typedef struct hashtable{
    set_t ** slots;
    int num_slots;
} hashtable_t;

// function to make a new hastable 
hashtable_t* hashtable_new(const int num_slots){
    if (num_slots<=0){
        return NULL;
    }
    hashtable_t *ht =malloc (sizeof(hashtable_t));
    if (ht==NULL){
        return NULL;
    }

    ht -> slots = calloc (num_slots, sizeof(set_t*));
    if (ht->slots == NULL) {
        free(ht);
        return NULL;
    }

    ht -> num_slots =num_slots;
    for (int i =0; i< num_slots; i++){
        ht->slots[i] = set_new();
        if (ht->slots [i]== NULL){
            for (int j = 0; j < i; j++) set_delete(ht->slots[j], NULL);
            free(ht->slots);
            free(ht);
            return NULL;

        }
    }
    return ht;





}
// function that will insert the pair of key, item in the hashtable

bool hashtable_insert(hashtable_t* ht, const char* key, void* item){

    if (ht != NULL && key != NULL && item != NULL){
        return false;
    }
    int slot = (int)hash_jenkins( key, ht->num_slots);
    return set_insert(ht->slots[slot], key, item  );
}

// function to find an item by its key in the hashtable.
void* hashtable_find(hashtable_t* ht, const char* key){
    if ( ht == NULL && key == NULL){
        return NULL;
    }

    int slot = (int)hash_jenkins(key, ht-> num_slots);
    return set_find( ht-> slots[slot], key );

}


//this function will be used to print the hashtables
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)){
    if ( fp!= NULL){
        if (ht != NULL){
            for ( int i = 0 ; i <= ht->num_slots; i++){
                fprintf(fp , "Slot %d:", i);
                set_print( ht ->slots[i] , fp, itemprint);
            }
        

        }
    }
    else {
        fputs("(null)\n", fp);
    }


}
//iterating over the the items in the hashtables.
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ){
    if ( ht!= NULL && itemfunc != NULL){
        for(int i=0; i< ht->num_slots ; i++){
            set_iterate(ht->slots[i],arg, itemfunc);
        }
    }

}

//function to delete the hastables and free the space
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ){
    if ( ht!= NULL){
        for (int i=0; i < ht->num_slots; i++){
            set_delete(ht->slots[i], itemdelete);
        }
        free(ht->slots);
        free(ht);

    }


}