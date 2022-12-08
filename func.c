#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "func.h"

int getLineNumber(){
	return Lines;
}

int isRunning()
{
    return Running;
}

void printLineNumber(){	
	printf("\nLinha %d :", getLineNumber());
}

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