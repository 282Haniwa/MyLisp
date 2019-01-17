#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#ifndef TRUE
#define TRUE 0
#endif //TRUE
#ifndef FALSE
#define FALSE 1
#endif //TRUE

extern char *yytext;
extern int linecounter;

int main(void);
int yylex(void);
int yyparse(void);
void yyerror(char*);
void evaluate(Cell *pointer);
