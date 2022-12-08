#include <stdio.h>

extern int Running;
extern int Lines;

int getLineNumber();
int isRunning();
void printLineNumber();
char* trimQuotation(int type, char* lit);