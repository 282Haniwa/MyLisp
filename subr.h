#include <stdio.h>
#include "base.h"

#ifndef SUBR_H
#define SUBR_H

Cell *subr_atom(Cell *);
Cell *subr_car(Cell *);
Cell *subr_cdr(Cell *);
Cell *subr_cons(Cell *);
Cell *subr_eq(Cell *);
Cell *subr_eval(Cell *);
Cell *subr_numberp(Cell *);
Cell *subr_print(Cell *);

#endif // SUBR_H
