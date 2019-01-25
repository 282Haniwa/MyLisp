#include "defs.h"
#include "fsubr.h"
#include "subr.h"

int main(void) {
    init();
    linecounter = 1;
    if (yyparse() == 0) {
        fprintf(stderr, "\nparser successfully ended\n\n");
    }
    return (EXIT_SUCCESS);
}

void evaluate(Cell *pointer) {
    Cell *result;

    print_lisp_code(pointer);
    printf("\n");
    dump_bound_atom_list();
    // dump_cell_list();
    result = subr_eval(cons(pointer, nil()));
    subr_print(cons(result, nil()));
    printf("\n");
    return;
}
