#include "hash.h"
#include "tokens.h"
#include <string.h>

void initMe(void) {
	int i=0;
	for(i=0; i<HASH_CAPACITY; i++){
		HashTable[i] = 0;
	}
}

int hashAddress(char *lit) {
	int address = 1;
	int i;
	
	for (i=0; i<strlen(lit); i++){
		address = (address * lit[i]) % HASH_CAPACITY +1;
	}

	return address-1;
}

hashNode* hashFind(char *lit, int address){
	hashNode *node;
	for(node=HashTable[address]; node; node=node->next)
		if(strcmp(node->lit, lit) == 0)
			return node;

	return 0;
}

hashNode* hashInsert(int type, char *lit){
	hashNode *newNode;
	int address = hashAddress(lit);

	lit = trimQuotation(type, lit);

	if((newNode = hashFind(lit, address))!=0)
		return newNode;	

	newNode = (hashNode *) calloc(1, sizeof(hashNode));
	newNode->type = type;
	newNode->lit = calloc(strlen(yytext)+1, sizeof(char));

	strcpy(newNode->lit, lit);

	newNode->next = HashTable[address];
	HashTable[address] = newNode;

	return newNode;
}

void hashPrint(){
	int i=0;
	hashNode *node;
	
	for(i=0; i<HASH_CAPACITY; i++)
		for(node = HashTable[i]; node!=0; node=node->next)
			printf("Hash_Table_Node[%d]: %s  -> %i \n", i, node->lit, node->type);

}


//Auxiliar function to transform into LITERAL

char* trimQuotation(int type, char* lit){
	char *trimmedLit;

	trimmedLit = calloc(strlen(lit-1), sizeof(char));

	if(type == LIT_CHAR){
		
		strncpy(trimmedLit, &lit[1], 1);
	}else if(type == LIT_STRING){

		trimmedLit = strtok(lit, "\"");
	}else{
		return lit;
	}
	return trimmedLit;
}