#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/list.h"

#ifndef TRUE
#define TRUE 0
#endif //TRUE
#ifndef FALSE
#define FALSE 1
#endif //TRUE

#ifndef BASE_H
#define BASE_H

enum {CONS, ATOM};
enum {OBJ_NUMBER, OBJ_STRING, OBJ_ATOM, OBJ_CONS, OBJ_NIL, OBJ_T};
enum {SUBR, FSUBR, EXPR, FEXPR, LAMBDA};

typedef struct cell {
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;

typedef struct obj {
	int          kind;
	int          bound;
	void        *value;
	char        *string;
} Object;

typedef struct lambda {
	int          kind;
	int          arg_count;
	Cell        *arg_list;
	void        *function;
	char        *string;
} Lambda;

void init(void);
Cell *atom(char *, Cell *);
Cell *cons(Cell *, Cell *);
Cell *object(int, void *);
Cell *nil(void);
Cell *t(void);
double number(Object *);
Cell *lisp_list_append(Cell *, Cell *);
int lisp_list_length(Cell *);
int is_lisp_list(Cell *);
Object *find_object(void *);
Cell *find_bound_atom(char *, List *);
void dump_cell_list(void);
void dump_bound_atom_list(List *);
void dump_object_list(void);
void dump_tree(Cell *);
void visit(Cell *, int);

extern Cell *NIL;
extern Cell *T;

// gc実装用
// TODO: gcを実装
extern List *cell_list;
extern List *object_list;
// bound_atom識別用
extern List *global_bound_atom_list;
// lambda環境のローカル環境を保持するリストを保持するスタック
extern List *environment_stack;

#endif // BASE_H
