#include "base.h"

List *cell_list = NULL;
List *global_bound_atom_list = NULL;

static Cell *ATOM_NIL = NULL;
static Cell *ATOM_T = NULL;

void init(void) {
    cell_list = new_list(NULL);
    global_bound_atom_list = new_list(NULL);
}

Cell *atom(char *atomic_symbol, Cell *bound_pointer) {
    Cell *pointer;

    if (bound_pointer == NULL) {
        pointer = find_bound_atom(atomic_symbol, NULL);
        if (pointer != NULL) {
            return (pointer);
        }
    }

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = ATOM;
    pointer->head = (Cell *)strdup(atomic_symbol);
    pointer->tail = (Cell *)bound_pointer;
    list_append(cell_list, pointer);
    return (pointer);
}

Cell *cons(Cell *car, Cell *cdr) {
    Cell *pointer;

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = CONS;
    pointer->head = car;
    pointer->tail = cdr;
    list_append(cell_list, pointer);
    return (pointer);
}

Cell *nil(void) {
    Cell *pointer;

    if (ATOM_NIL != NULL) {
        return (ATOM_NIL);
    }

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = NIL;
    pointer->head = (Cell *)strdup("nil");
    pointer->tail = (Cell *)strdup("nil");
    ATOM_NIL = pointer;
    return (pointer);
}

Cell *t(void) {
    Cell *pointer;

    if (ATOM_T != NULL) {
        return (ATOM_T);
    }

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = ATOM;
    pointer->head = (Cell *)strdup("t");
    pointer->tail = (Cell *)strdup("t");
    ATOM_T = pointer;
    return (pointer);
}

Cell *number(char *text) {
    double value;
    Cell *pointer = NULL;
    char **endptr = NULL;

    value = strtod((char *)text, endptr);
    if (endptr == NULL) {
        pointer = (Cell *)malloc(sizeof(Cell));
        pointer->kind = ATOM;
        pointer->head = (Cell *)strdup(text);
        pointer->tail = (Cell *)&value;
        list_append(cell_list, pointer);
    }
    return (pointer);
}

Cell *lisp_list_append(Cell *list, Cell *new_element) {
    Cell *pointer;

    if (list == NULL) {
        pointer = (Cell *)malloc(sizeof(Cell *));
        pointer->kind = CONS;
        pointer->head = new_element;
        pointer->tail = nil();
        return (pointer);
    }

    pointer = list;
    if (pointer == nil()) {
        return (cons(new_element, nil()));
    }
    while (pointer->tail != nil()) {
        pointer = pointer->tail;
    }
    pointer->tail = cons(new_element, nil());
    return (list);
}

int lisp_list_length(Cell *list) {
    int counter;
    Cell *pointer;

    pointer = list;
    while (pointer->tail != nil()) {
        pointer = pointer->tail;
        counter++;
    }
    return (counter);
}

int is_lisp_list(Cell *list) {
    Cell *pointer;

    pointer = list;
    while (pointer->kind == ATOM) {
        pointer = pointer->tail;
    }
    if (pointer == nil()) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

Cell *find_bound_atom(char *atomic_symbol, List *environment) {
    List *pointer;


    if (!strcmp(atomic_symbol, "nil")) {
        return (nil());
    }
    if (!strcmp(atomic_symbol, "t")) {
        return (t());
    }

    if (global_bound_atom_list == NULL) {
        return (NULL);
    }

    // 先に関数ローカルの環境から調べる
    if (environment != NULL) {
        pointer = environment;
        if (pointer == NULL) {
            return (NULL);
        }
        while (pointer->next != NULL) {
            pointer = pointer->next;
            if (!strcmp((char *)atomic_symbol,
                        (char *)((Cell *)pointer->data)->head)) {
                return ((Cell *)pointer->data);
            }
        }
    }
    // 関数ローカルで見つからなかった場合はグローバル領域から探す
    pointer = global_bound_atom_list;
    if (pointer == NULL) {
        return (NULL);
    }
    while (pointer->next != NULL) {
        pointer = pointer->next;
        if (!strcmp((char *)atomic_symbol,
                    (char *)((Cell *)pointer->data)->head)) {
            return ((Cell *)pointer->data);
        }
    }
    return (NULL);
}

void dump_cell_list(void) {
    List *pointer;

    printf("cell count is : %d\n", list_length(cell_list));
    printf("cell list is  :\n");
    pointer = cell_list;
    if (pointer == NULL) {
        return;
    }
    while (pointer->next != NULL) {
        pointer = pointer->next;
        dump_tree((Cell *)pointer->data);
        printf("\n");
    }
    printf("--------------------------------\n");
}

void dump_bound_atom_list(List *environment) {
    List *pointer;

    printf("global bound atom count is : %d\n",
           list_length(global_bound_atom_list));
    printf("bound atom list is  :\n");
    pointer = global_bound_atom_list;
    if (pointer == NULL) {
        return;
    }
    while (pointer->next != NULL) {
        pointer = pointer->next;
        dump_tree((Cell *)pointer->data);
    }
    if (environment != NULL) {
        printf("lambda local bound atom count is : %d\n",
               list_length(environment));
        printf("bound atom list is  :\n");
        pointer = environment;
        if (pointer == NULL) {
            return;
        }
        while (pointer->next != NULL) {
            pointer = pointer->next;
            dump_tree((Cell *)pointer->data);
        }
    }
    printf("--------------------------------\n");
}

void dump_tree(Cell *pointer) {
    visit(pointer, 1);
    printf("\n");
}

void visit(Cell *pointer, int level) {
    int count;

    printf("\n");
    for (count = 0; count < level; count++) {
        printf("    ");
    }
    if (pointer->kind == ATOM || pointer->kind == NIL || pointer->kind == T || pointer->kind == NUMBER) {
        printf("atom(");
        printf("%s", (char *)pointer->head);
        printf(" %s", (char *)pointer->tail);
        printf(")");
    }
    if (pointer->kind == CONS) {
        printf("cons(");
        visit(pointer->head, level + 1);
        visit(pointer->tail, level + 1);
        printf(")");
    }
    if (pointer->kind == LAMBDA) {
        visit(pointer->tail, level + 1);
    }
    return;
}

void print_lisp_code(Cell *pointer) {
    int count;

    if (pointer->kind == ATOM || pointer->kind == NIL || pointer->kind == T || pointer->kind == NUMBER) {
        printf("%s", (char *)pointer->head);
    }
    if (pointer->kind == CONS || pointer->kind == LAMBDA) {
        if (is_lisp_list(pointer)) {
            Cell *tmp;
            tmp = pointer;
            printf("(");
            while (tmp->tail != nil()) {
                print_lisp_code(tmp->head);
                printf(" ");
                tmp = tmp->tail;
            }
            print_lisp_code(tmp->head);
            printf(")");
        } else {
            printf("(");
            print_lisp_code(pointer->head);
            printf(" . ");
            print_lisp_code(pointer->tail);
            printf(")");
        }
    }
    return;
}
