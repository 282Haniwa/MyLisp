#include <stdio.h>
#include "base.h"
#include "subr.h"

#ifndef FSUBR_H
#define FSUBR_H
#define FSUBR_ARRAY_SIZE 9

Cell *evaluate_fsubr_if_needed(char *, Cell *);
Cell *get_argument_if_number(Cell *);
Cell *fsubr_add(Cell *);
Cell *fsubr_sub(Cell *);
Cell *fsubr_mul(Cell *);
Cell *fsubr_div(Cell *);
Cell *fsubr_mod(Cell *);
Cell *fsubr_cond(Cell *);
Cell *fsubr_define(Cell *);
Cell *fsubr_defun(Cell *);
Cell *fsubr_quote(Cell *);

extern Cell *(*fsubr_funcp_array[FSUBR_ARRAY_SIZE])(Cell *);
extern char *fsubr_binding_atom_array[FSUBR_ARRAY_SIZE];

#endif // FSUBR_H
