
#define CAPACITY 50000 // Size of the Hash Table

typedef struct Ht_item Ht_item;

typedef struct HashTable HashTable;

// Define the Hash Table Item here
struct Ht_item {
    int   type;
    char* value;
    Ht_item* next;
};

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};


// Hash prototype functions here
Ht_item* create_item(int* token, char* value);

HashTable* create_table(int size);

void free_item(Ht_item* item);

void free_table(HashTable* table);

void ht_insert(HashTable* table, int* token, char* value);