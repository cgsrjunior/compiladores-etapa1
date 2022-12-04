%{
#include "tokens.h"


int running_status = 1, lines = 1;
int words = 0, c_letters = 0, numbers = 0, spl_char = 0, total = 0;


%}

ID      [a-z_\-]+
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
"read"          return KW_ENTRADA;
"write"         return KW_ESCREVA;
"return"        return KW_RETORNA;

"<="			return OPERATOR_LE;
">="			return OPERATOR_GE;
"=="			return OPERATOR_EQ;
"!="			return OPERATOR_DIF;

[a-z0-9_]+		{hashInsert(TK_IDENTIFIER, yytext);return TK_IDENTIFIER;}


{INT}       { yylval.symbol = symbol_table_add(st, yytext, symbol_int_literal, line_count);
              return LIT_INTEGER; }
{FLOAT}       { yylval.symbol = symbol_table_add(st, yytext, symbol_float_literal, line_count);
              return LIT_FLOAT; }
{CHAR}      { yylval.symbol = symbol_table_add(st, yytext, symbol_char_literal, line_count); 
              return LIT_CHAR; }
{STRING}    { yylval.symbol = symbol_table_add(st, yytext, symbol_string_literal, line_count);
              return LIT_STRING; }

.           { return TOKEN_ERROR; }



{MULTI_COMMENT_BEGIN}           { BEGIN(COMMENT); }
<COMMENT>"///"                  { BEGIN(INITIAL); }
<COMMENT>"\n"                   { line_count++; }
<COMMENT>.
{MULTI_COMMENT_END}.*





\n {lines++; words++;}
[\t ' '] {words++;}
[a-zA-Z] {c_letters++;}
[0-9] {numbers++;}
. {spl_char++;}
"//".*                                    { /* Comentario de linha unica -> ignora */ }


"///".* { readmulticomment(); }

%%

int main()
{
    yyin = fopen("sample.txt", "r");
    yylex();
    total = c_letters +numbers +spl_char;
    printf("\nFile Contents...\n");
    printf("\n\t%d line", lines);
    printf("\n\t%d words", words);
    printf("\n\t%d chars", c_letters);
    printf("\n\t%d digits", numbers);
    printf("\n\t%d special chars", spl_char);
    printf("\n\t total %d characters", total);
    return 0;
}

int getLineNumber() {
    return lines;
}

int is_running()
{
    return running_status;
}

int yywrap()
{
    running_status = 0;
    yylex_destroy();
    return 1;
}