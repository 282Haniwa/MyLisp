#include <stdio.h>
#include "base.h"

#ifndef FSUBR_H
#define FSUBR_H

Cell *fsubr_add(Cell *);
Cell *fsubr_sub(Cell *);
Cell *fsubr_mul(Cell *);
Cell *fsubr_div(Cell *);
Cell *fsubr_mod(Cell *);
Cell *fsubr_cond(Cell *);
Cell *fsubr_define(Cell *);
Cell *fsubr_defun(Cell *);
Cell *fsubr_lambda(Cell *);
Cell *fsubr_quote(Cell *);

#endif // FSUBR_H
