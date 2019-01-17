#include "base.h"

List *cell_list = NULL;
List *object_list = NULL;
List *global_bound_atom_list = NULL;

Cell *NIL = NULL;
Cell *T = NULL;

void init(void) {
    cell_list = new_list(NULL);
    object_list = new_list(NULL);
    global_bound_atom_list = new_list(NULL);

    list_append(global_bound_atom_list, nil());
    list_append(object_list, nil()->tail);
    list_append(global_bound_atom_list, t());
    list_append(object_list, t()->tail);
}

Cell *atom(char *atomic_symbol, Cell *object_pointer) {
    Cell *pointer;

    if (object_pointer == NULL) {
        pointer = find_bound_atom(atomic_symbol, NULL);
        if (pointer != NULL) {
            return (pointer);
        }
    }

    pointer = (Cell *)malloc(sizeof(Cell));
    pointer->kind = ATOM;
    pointer->head = (Cell *)strdup(atomic_symbol);
    pointer->tail = (Cell *)object_pointer;
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

Cell *object(int object_type, void *value) {
    Object *object_pointer = NULL;

    object_pointer = find_object(value);
    if (object_pointer != NULL) {
        return ((Cell *)object_pointer);
    }

    object_pointer = (Object *)malloc(sizeof(Object));

    if (object_type == OBJ_NUMBER) {
        object_pointer->kind = OBJ_NUMBER;
        object_pointer->value = (void *)strdup(value);
        object_pointer->string = strdup(value);
    }

    if (object_type == OBJ_STRING) {
        object_pointer->kind = OBJ_STRING;
        object_pointer->value = (void *)strdup(value);
        object_pointer->string = strdup(value);
    }

    if (object_type == OBJ_ATOM) {
        object_pointer->kind = OBJ_ATOM;
        object_pointer->value = (void *)value;
        object_pointer->string = (char *)((Cell *)value)->head;
    }

    if (object_type == OBJ_CONS) {
        object_pointer->kind = OBJ_CONS;
        object_pointer->value = (void *)value;
        object_pointer->string = "cons";
    }

    object_pointer->bound = 1;
    list_append(object_list, (Cell *)object_pointer);
    return ((Cell *)object_pointer);
}

Cell *nil(void) {
    Object *object_pointer;
    Cell *cell_pointer;

    if (NIL != NULL) {
        return (NIL);
    }

    object_pointer = (Object *)malloc(sizeof(Object));
    object_pointer->kind = OBJ_NIL;
    object_pointer->bound = 1;
    object_pointer->value = (void *)strdup("nil");
    object_pointer->string = (void *)strdup("nil");
    cell_pointer = (Cell *)malloc(sizeof(Cell));
    cell_pointer->kind = ATOM;
    cell_pointer->head = (Cell *)strdup("nil");
    cell_pointer->tail = (Cell *)object_pointer;
    NIL = cell_pointer;
    return (cell_pointer);
}

Cell *t(void) {
    Object *object_pointer;
    Cell *cell_pointer;

    if (T != NULL) {
        return (T);
    }

    object_pointer = (Object *)malloc(sizeof(Object));
    object_pointer->kind = OBJ_T;
    object_pointer->bound = 1;
    object_pointer->value = (void *)strdup("t");
    object_pointer->string = (void *)strdup("t");
    cell_pointer = (Cell *)malloc(sizeof(Cell));
    cell_pointer->kind = ATOM;
    cell_pointer->head = (Cell *)strdup("t");
    cell_pointer->tail = (Cell *)object_pointer;
    T = cell_pointer;
    return (cell_pointer);
}

double number(Object *object_pointer) {
    double value = strtod((char *)object_pointer->value, NULL);
    return (value);
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

Object *find_object(void *object_value) {
    List *pointer;

    if (global_bound_atom_list == NULL) {
        return (NULL);
    }

    pointer = object_list;
    if (pointer == NULL) {
        return (NULL);
    }
    while (pointer->next != NULL) {
        pointer = pointer->next;
        if (((Object *)pointer->data)->kind == OBJ_ATOM || ((Object *)pointer->data)->kind == OBJ_CONS) {
            if (object_value == ((Object *)pointer->data)->value) {
                return (((Object *)pointer->data));
            }
        } else {
            if (!strcmp((char *)object_value,
                        (char *)((Object *)pointer->data)->value)) {
                return (((Object *)pointer->data));
            }
        }
    }
    return (NULL);
}

Cell *find_bound_atom(char *atomic_symbol, List *environment) {
    List *pointer;

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
            if (!strcmp((char *)atomic_symbol, (char *)((Cell *)pointer->data)->head)) {
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
        if (!strcmp((char *)atomic_symbol, (char *)((Cell *)pointer->data)->head)) {
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

void dump_bound_atom_list(List * environment) {
    List *pointer;

    printf("global bound atom count is : %d\n", list_length(global_bound_atom_list));
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
        printf("lambda local bound atom count is : %d\n", list_length(environment));
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

void dump_object_list(void) {
    List *pointer;

    printf("object count is : %d\n", list_length(object_list));
    printf("object list is  :\n");
    pointer = object_list;
    if (pointer == NULL) {
        return;
    }
    while (pointer->next != NULL) {
        pointer = pointer->next;
        if (((Object *)pointer->data)->kind == OBJ_ATOM) {
            printf("atom(%s)\n", (char *)((Cell *)((Object *)pointer->data)->value)->head);
        } else if (((Object *)pointer->data)->kind == OBJ_CONS) {
            dump_tree((Cell *)((Object *)pointer->data)->value);
        } else {
            printf("object(%s)\n", (char *)((Object *)pointer->data)->string);
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
    if (pointer->kind == CONS) {
        printf("cons(");
        visit(pointer->head, level + 1);
        visit(pointer->tail, level + 1);
        printf(")");
    }
    if (pointer->kind == ATOM) {
        printf("atom(");
        printf("%s", (char *)pointer->head);
        // printf(" %s", (char *)pointer->tail);
        printf(")");
    }
    return;
}

// Cell *evaluate(Cell *pointer) {
//     Lambda *lambda;

//     environment_stack = lisp_list_append(environment_stack, nil());
//     if (pointer->kind == ATOM) {
//         evaluate(pointer->tail);
//     }
//     if (pointer->kind == CONS) {
//         /* code */
//     }
//     // ATOMでもCONSでもない時（OBJECTの時）値を出力してpointerをそのまま返す
//     printf("%s", (char *)((Object *)pointer)->value);
//     return (pointer);
// }
