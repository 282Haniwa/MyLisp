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

    error_flag = FALSE;
    printf(">>> ");
    print_lisp_code(pointer);
    printf("\n");
    result = subr_eval(cons(pointer, nil()));
    printf("<<< ");
    if (error_flag) {
        subr_print(cons(nil(), nil()));
    } else {
        subr_print(cons(result, nil()));
    }
    printf("\n");
    return;
}
