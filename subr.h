#include <stdio.h>
#include "base.h"
#include "lib/list.h"

#ifndef SUBR_H
#define SUBR_H
#define SUBR_ARRAY_SIZE 8

Cell *evaluate_lambda(Cell *, Cell *);
Cell *evaluate_subr_if_needed(char *, Cell *);
int is_lambda(Cell *);
Cell *subr_atom(Cell *);
Cell *subr_car(Cell *);
Cell *subr_cdr(Cell *);
Cell *subr_cons(Cell *);
Cell *subr_eq(Cell *);
Cell *subr_eval(Cell *);
Cell *subr_numberp(Cell *);
Cell *subr_print(Cell *);

extern Cell *(*subr_funcp_array[SUBR_ARRAY_SIZE])(Cell *);
extern char *subr_binding_atom_array[SUBR_ARRAY_SIZE];

#endif // SUBR_H
