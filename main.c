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
    dump_tree(pointer);
    dump_bound_atom_list();
    dump_object_list();
    // dump_cell_list();
    // Cell *result = subr_eval(pointer);
    // subr_print(result);
    return;
}
