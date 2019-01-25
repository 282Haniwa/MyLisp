#include "fsubr.h"

Cell *(*fsubr_funcp_array[])(Cell *) = {fsubr_add,    fsubr_sub,    fsubr_mul,
                                       fsubr_div,    fsubr_mod,    fsubr_cond,
                                       fsubr_define, fsubr_defun, fsubr_quote};

char *fsubr_binding_atom_array[] = {"+",    "-",      "*",      "/",    "%",
                                   "cond", "define", "defun", "quote"};

Cell *evaluate_fsubr_if_needed(char *atomic_symbol, Cell *pointer) {
    Cell *result = NULL;

    for (int index = 0; index < FSUBR_ARRAY_SIZE; index++) {
        if (!strcmp(fsubr_binding_atom_array[index], atomic_symbol)) {
            result = fsubr_funcp_array[index](pointer);
        }
    }
    return (result);
}

Cell *fsubr_add(Cell *pointer) {
    Cell *args;
    double result;
    char result_string[32];

    args = pointer;
    result = 0.0;
    while (args != nil()) {
        if (args->head->kind == NUMBER) {
            result += number_cell_to_double(args->head);
        } else {
            Cell *tmp = subr_eval(cons(args->head, nil()));
            if (tmp->kind == NUMBER) {
                result += number_cell_to_double(tmp);
            } else if (tmp == nil()) {
                return (nil());
            } else {
                printf("Error: ");
                print_lisp_code(args->head);
                printf(" is not number.\n");
                return (nil());
            }
        }
        args = args->tail;
    }
    sprintf(result_string, "%g", result);
    return (number(strdup(result_string)));
}

Cell *fsubr_sub(Cell *pointer) {
    Cell *args;
    double result;
    char result_string[32];

    args = pointer;
    result = number_cell_to_double(args->head);
    args = args->tail;
    while (args != nil()) {
        if (args->head->kind == NUMBER) {
            result -= number_cell_to_double(args->head);
        } else {
            Cell *tmp = subr_eval(cons(args->head, nil()));
            if (tmp->kind == NUMBER) {
                result -= number_cell_to_double(tmp);
            } else if (tmp == nil()) {
                return (nil());
            } else {
                printf("Error: ");
                print_lisp_code(args->head);
                printf(" is not number.\n");
                return (nil());
            }
        }
        args = args->tail;
    }
    sprintf(result_string, "%g", result);
    return (number(strdup(result_string)));
}

Cell *fsubr_mul(Cell *pointer) {
    Cell *args;
    double result;
    char result_string[32];

    args = pointer;
    result = number_cell_to_double(args->head);
    args = args->tail;
    while (args != nil()) {
        if (args->head->kind == NUMBER) {
            result *= number_cell_to_double(args->head);
        } else {
            Cell *tmp = subr_eval(cons(args->head, nil()));
            if (tmp->kind == NUMBER) {
                result *= number_cell_to_double(tmp);
            } else if (tmp == nil()) {
                return (nil());
            } else {
                printf("Error: ");
                print_lisp_code(args->head);
                printf(" is not number.\n");
                return (nil());
            }
        }
        args = args->tail;
    }
    sprintf(result_string, "%g", result);
    return (number(strdup(result_string)));
}

Cell *fsubr_div(Cell *pointer) {
    Cell *args;
    double result;
    char result_string[32];

    args = pointer;
    result = number_cell_to_double(args->head);
    args = args->tail;
    while (args != nil()) {
        if (args->head->kind == NUMBER) {
            result /= number_cell_to_double(args->head);
        } else {
            Cell *tmp = subr_eval(cons(args->head, nil()));
            if (tmp->kind == NUMBER) {
                result /= number_cell_to_double(tmp);
            } else if (tmp == nil()) {
                return (nil());
            } else {
                printf("Error: ");
                print_lisp_code(args->head);
                printf(" is not number.\n");
                return (nil());
            }
        }
        args = args->tail;
    }
    sprintf(result_string, "%g", result);
    return (number(strdup(result_string)));
}

// 実装を保留
Cell *fsubr_mod(Cell *pointer) { return (pointer); }

Cell *fsubr_cond(Cell *pointer) {
    Cell *args, *condition, *function, *result;

    args = pointer;
    while (args != nil()) {
        condition = args->head->head;
        function = args->head->tail;
        if (subr_eval(cons(condition, nil())) == t()) {
            while (function != nil()) {
                result = subr_eval(cons(function->head, nil()));
                function = function->tail;
            }
            return (result);
        }
        args = args->tail;
    }

    return (nil());
}

Cell *fsubr_define(Cell *pointer) {
    Cell *atom_cell, *bound_item;
    List *environment;

    atom_cell = pointer->head;
    if (atom_cell->kind != ATOM) {
        printf("Error: ");
        print_lisp_code(atom_cell);
        printf(" is not good atom. It can't bind anything.\n");
        return (nil());
    }
    bound_item = pointer->tail->head;
    environment = list_get(environment_stack, 1);
    if (!list_is_empty(environment)) {
        List *tmp;
        tmp = environment;
        while (tmp != NULL) {
            if (!strcmp((char *)((Cell *)tmp->data)->head, (char *)atom_cell->head)) {
                ((Cell *)tmp->data)->tail = subr_eval(cons(bound_item, nil()));
                return (tmp->data);
            }
            tmp = tmp->next;
        }
    }
    atom_cell = atom((char *)atom_cell->head, subr_eval(cons(bound_item, nil())));
    list_append(environment, atom_cell);
    return (atom_cell);
}

Cell *fsubr_defun(Cell *pointer) { return (pointer); }

Cell *fsubr_quote(Cell *pointer) {
    return (pointer->head);
}
