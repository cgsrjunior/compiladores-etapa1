#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "tokens.h"
#include "func.h"

extern int yylex();
extern char *yytext;
extern FILE *yyin;

//int getLineNumber();
//int is_running();
//void printLineNumber();

int main(int argc, char** argv){
	int tok = 0;
	
	initMe();

	if(argc < 2){
		printf("Comando invalido. Tente: ./etapa1 input.txt \n");
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		printf("Erro ao abrir o arquivo de entrada!");
		exit(1);
	}
	int line = 0;
	while(isRunning()){
		tok = yylex();
		if(line != getLineNumber()){
			line = getLineNumber();
			printLineNumber();
		}
		switch(tok){
		
			case KW_INTE: 		printf("KW_INT "); break;
			case KW_REAL: 		printf("KW_FLOAT "); break;
			case KW_SE: 		printf("KW_IF "); break;
			case KW_ENTAUM: 	printf("KW_THEN "); break;
			case KW_SENAUM: 	printf("KW_ELSE "); break;
			case OPERATOR_LE: 	printf("OPERATOR_LE "); break;
			case OPERATOR_GE: 	printf("OPERATOR_GE "); break;
			case OPERATOR_EQ: 	printf("OPERATOR_EQ "); break;
			case OPERATOR_DIF: 	printf("OPERATOR_DIF "); break;
			case KW_ENTRADA:	printf("KW_ENTRADA "); break;			
			case KW_ESCREVA: 	printf("KW_ESCREVA "); break;
			case KW_RETORNE: 	printf("KW_RETURN "); break;
			case TK_IDENTIFIER:	printf("TK_IDENTIFIER "); break;
			case LIT_INTEIRO:	printf("LIT_INTEGER "); break;
			case LIT_FLOAT:		printf("LIT_FLOAT "); break;
			case LIT_CHAR:		printf("LIT_CHAR "); break;
			case LIT_STRING:	printf("LIT_STRING "); break;
			case TOKEN_ERROR:	printf("TOKEN_ERROR "); break;
			default: 			printf("%s ", yytext); break;

		}
		
	}
	hashPrint();
}