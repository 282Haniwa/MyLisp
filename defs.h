#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

#define TRUE	1
#define FALSE	0
#define ATOM_TABLE_SIZE	2048

extern char *yytext;
extern int linecounter;

int main(void);
int yylex(void);
int yyparse(void);
void yyerror(char*);
Cell *cons(Cell *, Cell *);
// Cell *node(char *, Cell *);
Cell *leaf(char *, char *);
Cell *list(Cell *, Cell *);
void tree(Cell *);
void visit(Cell *, int);
void eval(Cell *);
