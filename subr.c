#include "subr.h"
#include <stdio.h>

Cell *subr_atom(Cell *pointer) { return; }

Cell *subr_car(Cell *pointer) { return; }

Cell *subr_cdr(Cell *pointer) { return; }

Cell *subr_cons(Cell *pointer) { return; }

Cell *subr_eq(Cell *pointer) { return; }

Cell *subr_eval(Cell *pointer) {
    
}

Cell *subr_numberp(Cell *pointer) { return; }

Cell *subr_print(Cell *pointer) { return; }

Cell *(*subr_funcp_array[])(Cell *) = {subr_atom,    subr_car,  subr_cdr,
                                       subr_cons,    subr_eq,   subr_eval,
                                       subr_numberp, subr_print};

char *subr_binding_atom_array[] = {"atom", "car",  "cdr",     "cons",
                                   "eq",   "eval", "numberp", "print"}
