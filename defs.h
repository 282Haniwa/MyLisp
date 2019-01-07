#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define TRUE	1
#define FALSE	0
#define ATOM_TABLE_SIZE	2048

extern char *yytext;
extern int linecounter;

int main(void);
int yylex(void);
int yyparse(void);
void yyerror(char*);
void tree(Cell *);
void visit(Cell *, int);
void evaluate(Cell *pointer);
