#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/list.h"

#ifndef TRUE
#define TRUE 1
#endif //TRUE
#ifndef FALSE
#define FALSE 0
#endif //TRUE

#ifndef BASE_H
#define BASE_H
#define LISP_CODE_LENGTH 128

enum {ATOM, CONS, NIL, T, NUMBER};
// enum {SUBR, FSUBR, EXPR, FEXPR, LAMBDA};

typedef struct cell {
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;

void init(void);
Cell *atom(char *, Cell *);
Cell *cons(Cell *, Cell *);
Cell *nil(void);
Cell *t(void);
Cell *number(char *);
Cell *lisp_list_append(Cell *, Cell *);
int lisp_list_length(Cell *);
int is_lisp_list(Cell *);
Cell *find_bound_atom(char *, List *);
void dump_cell_list(void);
void dump_bound_atom_list(List *);
void dump_object_list(void);
void dump_tree(Cell *);
void visit(Cell *, int);
void print_lisp_code(Cell *);

// gc実装用
// TODO: gcを実装
extern List *cell_list;
// bound_atom識別用
extern List *global_bound_atom_list;
// lambda環境のローカル環境を保持するリストを保持するスタック
// 1オリジンで一方向線形リストを効率よく利用するために数字の若い方がstackのトップになるように利用する。
extern List *environment_stack;

#endif // BASE_H
