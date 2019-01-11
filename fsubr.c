#include "fsubr.h"
#include <stdio.h>

Cell *fsubr_add(Cell *pointer) { return; }
Cell *fsubr_sub(Cell *pointer) { return; }

Cell *fsubr_mul(Cell *pointer) { return; }

Cell *fsubr_div(Cell *pointer) { return; }

Cell *fsubr_mod(Cell *pointer) { return; }

Cell *fsubr_cond(Cell *pointer) { return; }

Cell *fsubr_define(Cell *pointer) { return; }

Cell *fsubr_defun(Cell *pointer) { return; }

Cell *fsubr_lambda(Cell *pointer) { return; }

Cell *fsubr_quote(Cell *pointer) { return; }

Cell *(*subr_funcp_array[])(Cell *) = {fsubr_add,    fsubr_sub,    fsubr_mul,
                                       fsubr_div,    fsubr_mod,    fsubr_cond,
                                       fsubr_define, fsubr_lambda, fsubr_quote};

char *subr_binding_atom_array[] = {"+",    "-",      "*",      "/",    "%",
                                   "cond", "define", "lambda", "quote"}
