#include "defs.h"
#include "fsubr.h"
#include "subr.h"

int main(void) {
    printf("MyLisp interpreter launched.\n");
    init();
    linecounter = 1;
    if (yyparse() == 0) {
        fprintf(stderr, "\nparser successfully ended\n\n");
    }
    return (EXIT_SUCCESS);
}

void evaluate(Cell *pointer) {
    Cell *result;

    result = subr_eval(cons(pointer, nil()));
    printf("< ");
    subr_print(cons(result, nil()));
    printf("\n");
    dump_bound_atom_list();
    return;
}
