#include "subr.h"
#include "fsubr.h"

Cell *(*subr_funcp_array[SUBR_ARRAY_SIZE])(Cell *) = {
    subr_atom, subr_car,  subr_cdr,     subr_cons,
    subr_eq,   subr_eval, subr_numberp, subr_print};

char *subr_binding_atom_array[SUBR_ARRAY_SIZE] = {
    "atom", "car", "cdr", "cons", "eq", "eval", "numberp", "print"};

Cell *evaluate_lambda(Cell *lambda, Cell *args) {
    Cell *arg_atom_list, *arg_list, *function, *result;
    List *environment;

    environment = new_list(NULL);
    arg_atom_list = lambda->tail->head;
    arg_list = args;
    function = lambda->tail->tail;
    if (!is_lisp_list(arg_atom_list)) {
        printf("Error: Lambda args should define with list.\n");
        error_flag = TRUE;
    }
    if (!strcmp((char *)lambda->head->head, "lambda")) {
        // 引数の数が合わなければエラーを出力する。
        if (lisp_list_length(arg_atom_list) < lisp_list_length(arg_list)) {
            printf("Error: Too many arguments.\n");
            error_flag = TRUE;
            return (nil());
        } else if (lisp_list_length(arg_atom_list) > lisp_list_length(arg_list)) {
            printf("Error: Too few arguments.\n");
            error_flag = TRUE;
            return (nil());
        }
        while (arg_atom_list != nil()) {
            list_append(environment, atom((char *)arg_atom_list->head->head, subr_eval(cons(arg_list->head, nil()))));
            arg_atom_list = arg_atom_list->tail;
            arg_list = arg_list->tail;
        }
        // 全ての引数を評価し終わってから、environmentをstackにpushする。
        list_insert(environment_stack, environment, 1);
    } else if(!strcmp((char *)lambda->head->head, "nlambda")) {
        // nlambdaは引数の定義を１つにしなければならない。
        if (lisp_list_length(arg_atom_list) > 1) {
            printf("Error: Too many defined arguments for nlambda.\n");
            error_flag = TRUE;
            return (nil());
        }
        list_append(environment, atom((char *)arg_atom_list->head->head, arg_list));
        // 全ての引数を評価し終わってから、environmentをstackにpushする。
        list_insert(environment_stack, environment, 1);
    }
    while (function != nil()) {
        result = subr_eval(cons(function->head, nil()));
        function = function->tail;
    }
    list_pop(environment_stack, 1);
    list_free(environment);
    environment = NULL;
    return (result);
}

Cell *evaluate_subr_if_needed(char *atomic_symbol, Cell *pointer) {
    Cell *result = NULL, *args, *evaluated_args;

    for (int index = 0; index < SUBR_ARRAY_SIZE; index++) {
        if (!strcmp(subr_binding_atom_array[index], atomic_symbol)) {
            args = pointer;
            evaluated_args = nil();
            while (args != nil()) {
                evaluated_args = lisp_list_append(evaluated_args, subr_eval(cons(args->head, nil())));
                args = args->tail;
            }
            result = subr_funcp_array[index](evaluated_args);
        }
    }
    return (result);
}

int is_lambda(Cell *pointer) {
    
    if (pointer->kind != CONS) {
        return (FALSE);
    }
    if (!strcmp((char *)pointer->head->head, "lambda") || !strcmp((char *)pointer->head->head, "nlambda")) {
        return (TRUE);
    }
    return (FALSE);
}

Cell *subr_atom(Cell *pointer) {
    Cell *arg1;

    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    if (arg1->kind == ATOM || arg1->kind == T || arg1->kind == NIL || arg1->kind == NUMBER) {
        return (t());
    }
    return (nil());
}

Cell *subr_car(Cell *pointer) {
    Cell *arg1;

    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    if (arg1->kind != CONS) {
        printf("Error: ");
        print_lisp_code(arg1);
        printf("is not cons.\n");
        error_flag = TRUE;
        return (nil());
    }
    return (arg1->head);
}

Cell *subr_cdr(Cell *pointer) {
    Cell *arg1;

    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    if (arg1->kind != CONS) {
        printf("Error: ");
        print_lisp_code(arg1);
        printf("is not cons.\n");
        error_flag = TRUE;
        return (nil());
    }
    return (arg1->tail);
}

Cell *subr_cons(Cell *pointer) {
    Cell *arg1, *arg2;

    if (lisp_list_length(pointer) < 2) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 2) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    arg2 = pointer->tail->head;
    return (cons(arg1, arg2));
}

Cell *subr_eq(Cell *pointer) {
    Cell *arg1, *arg2;

    if (lisp_list_length(pointer) < 2) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 2) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    arg2 = pointer->tail->head;
    if (arg1->kind == ATOM && arg2->kind == ATOM) {
        if (!strcmp((char *)arg1->head, (char *)arg2->head)) {
            return (t());
        }
        return (nil());
    }
    if (arg1->kind == CONS && arg2->kind == CONS) {
        Cell *head_result, *tail_result;
        head_result = subr_eq(cons(arg1->head, cons(arg2->head, nil())));
        tail_result = subr_eq(cons(arg1->tail, cons(arg2->tail, nil())));
        if (head_result == t() && tail_result == t()) {
            return (t());
        }
        return (nil());
    }
    if (arg1->kind == NIL && arg2->kind == NIL) {
        return (t());
    }
    if (arg1->kind == T && arg2->kind == T) {
        return (t());
    }
    if (arg1->kind == NUMBER && arg2->kind == NUMBER) {
        if (!strcmp((char *)arg1->head, (char *)arg2->head)) {
            return (t());
        }
        return (nil());
    }
    return (nil());
}

Cell *subr_eval(Cell *pointer) {
    Cell *arg1;

    if (error_flag) {
        return (nil());
    }
    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    // atomにバインドされているものを返す。
    if (arg1->kind == ATOM) {
        Cell *atom;
        atom = find_bound_atom((char *)arg1->head);
        if (atom == NULL) {
            printf("Error: %s is unbound atom.\n", (char *)arg1->head);
            error_flag = TRUE;
            return (nil());
        }
        return (atom->tail);
    }
    // consがlist構造なら一つ目をlambda、残りを引数として評価する。
    if (arg1->kind == CONS) {
        Cell *lambda, *result = NULL;

        // consがlist構造でなければ評価できないのでエラーを出力する。
        if (!is_lisp_list(arg1)) {
            printf("Error: Dotted pair can't evaluate.\n");
            error_flag = TRUE;
            return (nil());
        }
        // １つ目がatomだった時組込関数なら実行して、そうでないならバインドされているものがlambdaかどうか確認して変数(lambda)に束縛する。
        if (arg1->head->kind == ATOM) {
            // 組込関数であるか確認して、組込関数であれば、関数を実行する。
            result = evaluate_subr_if_needed((char *)arg1->head->head, arg1->tail);
            if (result != NULL) {
                return (result);
            }
            result = evaluate_fsubr_if_needed((char *)arg1->head->head, arg1->tail);
            if (result != NULL) {
                return (result);
            }
            lambda = subr_eval(cons(arg1->head, nil()));
            if (is_lambda(lambda)) {
                return (evaluate_lambda(lambda, arg1->tail));
            } else {
                printf("Error: ");
                print_lisp_code(arg1->head);
                printf(" is not lambda.\n");
                error_flag = TRUE;
                return (nil());
            }
        } else if(arg1->head->kind == CONS) {
            if (is_lambda(arg1->head)) {
                lambda = arg1->head;
                return (evaluate_lambda(lambda, arg1->tail));
            }
            lambda = subr_eval(cons(arg1->head, nil()));
            if (is_lambda(lambda)) {
                return (evaluate_lambda(lambda, arg1->tail));
            } else {
                printf("Error: ");
                print_lisp_code(arg1->head);
                printf(" is not lambda.\n");
                error_flag = TRUE;
                return (nil());
            }
        } else {
            printf("Error: ");
            print_lisp_code(arg1->head);
            printf(" is not function.\n");
            error_flag = TRUE;
            return (nil());
        }
    }
    // ATOMでもCONSでもない時、バインドされているものは値を意味するCellであるのでそのまま返す。
    return (arg1);
}

Cell *subr_numberp(Cell *pointer) {
    Cell *arg1;

    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    if (arg1->kind == NUMBER) {
        return (t());
    }
    return (nil());
}

Cell *subr_print(Cell *pointer) {
    Cell *arg1;

    if (lisp_list_length(pointer) < 1) {
        printf("Error: Too many arguments.\n");
        error_flag = TRUE;
        return (nil());
    } else if (lisp_list_length(pointer) > 1) {
        printf("Error: Too few arguments.\n");
        error_flag = TRUE;
        return (nil());
    }
    arg1 = pointer->head;
    print_lisp_code(arg1);
    printf("\n");
    return (arg1);
}
