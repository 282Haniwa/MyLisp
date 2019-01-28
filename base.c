#include "base.h"

List *cell_list = NULL;
List *environment_stack = NULL;

static Cell *ATOM_NIL = NULL;
static Cell *ATOM_T = NULL;
int error_flag;

void init(void) {
    error_flag = FALSE;
    cell_list = new_list(NULL);
    environment_stack = new_list(new_list(NULL));
}

Cell *atom(char *atomic_symbol, Cell *bound_pointer) {
    Cell *pointer;

    if (bound_pointer == NULL) {
        pointer = find_bound_atom(atomic_symbol);
        if (pointer != NULL) {
            return (pointer);
        }
    }

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = ATOM;
    pointer->head = (Cell *)strdup(atomic_symbol);
    pointer->tail = (Cell *)bound_pointer;
    // list_append(cell_list, pointer);
    return (pointer);
}

Cell *cons(Cell *car, Cell *cdr) {
    Cell *pointer;

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = CONS;
    pointer->head = car;
    pointer->tail = cdr;
    // list_append(cell_list, pointer);
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
    pointer->kind = T;
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
        pointer->kind = NUMBER;
        pointer->head = (Cell *)strdup(text);
        pointer->tail = (Cell *)strdup(text);
        // list_append(cell_list, pointer);
    }
    return (pointer);
}

double number_cell_to_double(Cell *pointer) {
    double value = 0.0;
    char **endptr = NULL;

    value = strtod((char *)pointer->head, endptr);
    if (endptr == NULL) {
        return (value);
    }
    return (value);
}

Cell *lisp_list_append(Cell *list, Cell *new_element) {
    Cell *pointer;

    if (list == NULL) {
        return (cons(new_element, nil()));
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
    int counter = 0;
    Cell *pointer;

    pointer = list;
    while (pointer != nil()) {
        pointer = pointer->tail;
        counter++;
    }
    return (counter);
}

int is_lisp_list(Cell *list) {
    Cell *pointer;

    if (list == nil()) {
        return (TRUE);
    }
    pointer = list;
    while (pointer->kind == CONS) {
        pointer = pointer->tail;
    }
    if (pointer == nil()) {
        return (TRUE);
    } else {
        return (FALSE);
    }
}

Cell *find_bound_atom(char *atomic_symbol) {
    List *environment, *atom_list;

    if (!strcmp(atomic_symbol, "nil")) {
        return (nil());
    }
    if (!strcmp(atomic_symbol, "t")) {
        return (t());
    }

    // スタックのトップから順に辿って、bindされているatomを探す。
    if (!list_is_empty(environment_stack)) {
        environment = environment_stack;
        while (environment != NULL) {
            atom_list = (List *)environment->data;
            if (!list_is_empty(atom_list)) {
                while (atom_list != NULL) {
                    if (!strcmp((char *)atomic_symbol,
                                (char *)((Cell *)atom_list->data)->head)) {
                        return ((Cell *)atom_list->data);
                    }
                    atom_list = atom_list->next;
                }
            }
            environment = environment->next;
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

void dump_bound_atom_list() {
    List *environment, *atom_list;
    int bound_atom_count = 0;

    environment = environment_stack;

    if (!list_is_empty(environment)) {
        while (environment != NULL) {
            bound_atom_count += list_length(environment->data);
            environment = environment->next;
        }
    }
    printf("bound atom count is : %d\n", bound_atom_count);
    printf("bound atom list is  :\n");
    environment = environment_stack;
    if (!list_is_empty(environment)) {
        while (environment != NULL) {
            atom_list = (List *)environment->data;
            if (!list_is_empty(atom_list)) {
                while (atom_list != NULL) {
                    printf("%s <- ", (char *)((Cell *)atom_list->data)->head);
                    print_lisp_code(((Cell *)atom_list->data)->tail);
                    printf("\n");
                    atom_list = atom_list->next;
                }
            }
            environment = environment->next;
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
    if (pointer->kind == ATOM || pointer->kind == NIL || pointer->kind == T ||
        pointer->kind == NUMBER) {
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
    return;
}

void print_lisp_code(Cell *pointer) {
    int count;

    if (pointer->kind == ATOM || pointer->kind == NIL || pointer->kind == T ||
        pointer->kind == NUMBER) {
        printf("%s", (char *)pointer->head);
    }
    if (pointer->kind == CONS) {
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
