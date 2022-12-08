%{
#include "tokens.h"
#include "hash.h"
#include "func.h"


int Running = 1;
int Lines = 1;


int getLineNumber();
int isRunning();
void printLineNumber();


%}

TOKEN_ID      [a-z0-9_]+
SPECIAL [-,;:\(\)\[\]\{\}+*/<>=]
CHAR    '[^']'
STRING  \"[^"\n]*\"
INT     [0-9]+
FLOAT   [0-9]*[.][0-9]+$


%option nounput
%option noinput
%x COMMENT


%%
"char"          return KW_CARA;
"int"           return KW_INTE;
"float"         return KW_REAL;

"if"            return KW_SE;
"then"          return KW_ENTAUM;
"else"          return KW_SENAUM;
"while"         return KW_ENQUANTO;
"input"         return KW_ENTRADA;
"write"         return KW_ESCREVA;
"return"        return KW_RETORNE;

"<="			return OPERATOR_LE;
">="			return OPERATOR_GE;
"=="			return OPERATOR_EQ;
"!="			return OPERATOR_DIF;


[\n]        {Lines++;}
[\t]        {/* Do nothing */ }


{SPECIAL}   {/* Returns only the ASCII character needed */ return yytext[0];}

{INT}       { hashInsert(LIT_INTEIRO, yytext);   return LIT_INTEIRO; }
{FLOAT}     { hashInsert(LIT_FLOAT, yytext);     return LIT_FLOAT;   }
{CHAR}      { hashInsert(LIT_CHAR, yytext);      return LIT_CHAR;    }
{STRING}    { hashInsert(LIT_STRING, yytext);    return LIT_STRING;  }
{TOKEN_ID}	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}


.           { return TOKEN_ERROR; }

"///"                            { BEGIN(COMMENT); }
<COMMENT>"\n"                    { Lines++; }
<COMMENT>.
<COMMENT>"\\\\\\"                { BEGIN(INITIAL); }

"//".*                          { /* Do nothing */ }


%%


/*
 This function is going to be used to append the id and used to convert the ascii value
void addto_buf()
{
    cur_tok=strlen(buf);
    strcpy(buf+cur_tok, yytext); 
}
It didn`t work
 */

int yywrap()
{
    Running = 0;
    return 1;
}