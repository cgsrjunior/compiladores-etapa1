#include <stdio.h>

extern int Running;
extern int Lines;

int getLineNumber();
int is_running();
void printLineNumber();
char* trimQuotation(int type, char* lit);