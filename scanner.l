%{
#include "tokens.h"


int running_status = 1, lines = 1;
int words = 0, c_letters = 0, numbers = 0, spl_char = 0, total = 0;


%}

TOKEN_ID      [a-z_\-]+
SPECIAL [-,;:\(\)\[\]\{\}+*/<>=]
CHAR    '[^']'
STRING  \"[^"\n]*\"
INT     [0-9]+
FLOAT   [0-9]*[.][0-9]+$

MULTI_COMMENTARY_BEGIN [///]
MULTI_COMMENTARY_END   [\\\]


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
"return"        return KW_RETORNA;

"<="			return OPERATOR_LE;
">="			return OPERATOR_GE;
"=="			return OPERATOR_EQ;
"!="			return OPERATOR_DIF;


[\n]        {lines++;}
[\t]        {/* Do nothing */ }


{SPECIAL}   {/* Returns only the ASCII character needed */ return yytext[0];}

{INT}       { hashInsert(LIT_INTEGER, yytext);   return LIT_INTEGER; }
{FLOAT}     { hashInsert(LIT_FLOAT, yytext);     return LIT_FLOAT;   }
{CHAR}      { hashInsert(LIT_CHAR, yytext);      return LIT_CHAR;    }
{STRING}    { hashInsert(LIT_STRING, yytext);    return LIT_STRING;  }
{TOKEN_ID}	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}


.           { return TOKEN_ERROR; }

"//".*                                    { /* Comentario de linha unica -> ignora */ }

{MULTI_COMMENT_BEGIN}           { BEGIN(COMMENT); }
<COMMENT>"///"                  { BEGIN(INITIAL); }
<COMMENT>"\n"                   { line_count++; }
<COMMENT>.
{MULTI_COMMENT_END}.*


%%

int main()
{
    yylex();
}

int getLineNumber() {
    return lines;
}

int is_running()
{
    return running_status;
}

/* This function is going to be used to append the id and used to convert the ascii value */
void addto_buf()
{
    cur_tok=strlen(buf);
    strcpy(buf+cur_tok, yytext); /* append to buffer */
} 

int yywrap()
{
    running_status = 0;
    yylex_destroy();
    return 1;
}