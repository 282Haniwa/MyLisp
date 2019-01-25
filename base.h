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
double number_cell_to_double(Cell *);
Cell *lisp_list_append(Cell *, Cell *);
int lisp_list_length(Cell *);
int is_lisp_list(Cell *);
Cell *find_bound_atom(char *);
void dump_cell_list(void);
void dump_bound_atom_list();
void dump_object_list(void);
void dump_tree(Cell *);
void visit(Cell *, int);
void print_lisp_code(Cell *);

// error検知用のflag
extern int error_flag;
// gc実装用
// TODO: gcを実装
extern List *cell_list;
// bound_atom識別用
// lambdaごとにスコープを持ち、静的スコープとしてatomにバインドされたものをを扱うための環境のスタック
// 1オリジンで一方向の線形リストを効率よく利用するために数字の若い方がstackのトップになるように利用する
extern List *environment_stack;

#endif // BASE_H
