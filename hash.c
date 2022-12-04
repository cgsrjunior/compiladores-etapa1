#include "hash.h"
#include "tokens.h"
#include <stdio.h>

int index = hash_function(key);

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}


Ht_item* create_item(int* token, char* value) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->type = (int*) malloc (strlen(token) + 1);
    item->value = (char*) malloc (strlen(value) + 1);
    
    strcpy(item->type, token);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
// It's supposed to be null
        table->items[i] = NULL;

    return table;
}

void free_item(Ht_item* item) {
    // Frees an item
    free(item->type);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

void ht_insert(HashTable* table, int* token, char* value) {
	// Create the item
	Ht_item* item = create_item(token, value);

	Ht_item* current_item = table->items[index];
	
	if (current_item == NULL) {
	    // Key does not exist.
	    if (table->count == table->size) {
	        // Hash Table Full
	        printf("Insert Error: Hash Table is full\n");
	        return;
	    }
	    
	    // Insert directly
	    table->items[index] = item; 
	    table->count++;
	}

	else {
    		// Scenario 1: We only need to update value
    		if (strcmp(current_item->key, key) == 0) {
        		strcpy(table->items[index]->value, value);
        		return;
    		}
    
    	else {
			// Scenario 2: Collision
		  	// We will handle case this a bit later
          	handle_collision(table, item);
          	return;
    	}
	}
}